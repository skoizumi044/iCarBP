/**
 * @file SchM.c
 * @brief タスクのスケジューリングを行う
 */

#include <Std_Types.h>
#include "Mcu.h"
#include "SchM.h"

#define SchM_Task_Cnt_Init  (0u)
#define SchM_Task_Cnt_10    (10)
#define SchM_Timer_Init     (0uL)

volatile uint32_t SchM_Timer1ms;
volatile uint8_t SchM_Task_Periodic10ms_Cnt;
volatile boolean SchM_Task_Periodic10ms_InvokeFlag;

#define SchM_DiffSystemCounter(now, old)    ( (now) >= (old) ? ((now) - (old)) : ((now) - (old)) )

static SchM_Task_Config SchM_TaskMeasuremntTable[TASK_NUM];

static void SchM_Cfg_SetSWInt(void);
static void SchM_Task_Idle(void);
static void SchM_Task_Perodic10ms(void);
static void SchM_Cfg_StartTimer(void);

uint32_t SchM_GetSystemCounter(void);
void SchM_TaskMeasuremntStart(SchM_TaskType task);
void SchM_TaskMeasuremntEnd(SchM_TaskType task);


void SchM_Init(void)
{
    SchM_Timer1ms = SchM_Timer_Init;

    SchM_Task_Periodic10ms_Cnt = SchM_Task_Cnt_Init;
    SchM_Task_Periodic10ms_InvokeFlag = FALSE;

    SchM_Cfg_Init();
    SchM_Cfg_StartTimer();

#if SchM_Periodic_InvokeMethod == SchM_Periodic10ms_Invoke_INT
    SchM_Cfg_SetSWInt();
#endif
}


void SchM_Start(void) {
    while (1) {
        SchM_Task_Idle();
    }
}


#if SchM_Periodic_InvokeMethod == SchM_Periodic10ms_Invoke_INT
static void SchM_Cfg_SetSWInt(void)
{
    /* 割り込みレベルを設定 */
    Mcu_SFR_Write(IPR(ICU, SWINT), 1);
    /* 割り込み許可 */
    Mcu_SFR_Write(IEN(ICU, SWINT), TRUE);
}
#endif


static void SchM_Task_Idle(void)
{
#if SchM_Periodic_InvokeMethod == SchM_Periodic10ms_Invoke_IDLE
    if (SchM_Task_Periodic10ms_InvokeFlag == TRUE) {
        SchM_Task_Periodic10ms_InvokeFlag = FALSE;
        
        SchM_Task_Perodic10ms();
    }
#endif

    SchM_Cfg_Task_Idle();
}

#define CONV_PCLKB8_MS(n) ((n) * 8 / (Mcu_Clk_Cfg_PCLKB_FREQ_KHZ / 1000))

static void SchM_Task_Perodic10ms(void)
{
    SchM_TaskMeasuremntStart(TASK_10MS);
    SchM_Cfg_Task_Periodic10ms();
    SchM_TaskMeasuremntEnd(TASK_10MS);
}


void __attribute__((interrupt)) SchM_Task_Int1ms(void)
{
    /* 1msタイマを加算 */
    SchM_Timer1ms++;

    Mcu_EI_Imm();
    
    SchM_TaskMeasuremntStart(TASK_1MS);

    SchM_Task_Periodic10ms_Cnt++;
    if (SchM_Task_Periodic10ms_Cnt >= SchM_Task_Cnt_10) {
        SchM_Task_Periodic10ms_Cnt = SchM_Task_Cnt_Init;
        SchM_Task_Periodic10ms_InvokeFlag = TRUE;

#if SchM_Periodic_InvokeMethod == SchM_Periodic10ms_Invoke_INT
        /* SW割り込みを起動 */
        Mcu_SFR_Write(ICU.SWINTR.BYTE, TRUE);
#endif
    }

    SchM_Cfg_Task_Int1ms();
    SchM_TaskMeasuremntEnd(TASK_1MS);
}


void __attribute__((interrupt)) SchM_Task_Periodic10msINT(void)
{
#if SchM_Periodic_InvokeMethod == SchM_Periodic10ms_Invoke_INT
    /* 多重割込み許可 */
    Mcu_EI_Imm();
    
    if (SchM_Task_Periodic10ms_InvokeFlag == TRUE) {
        SchM_Task_Periodic10ms_InvokeFlag = FALSE;

        SchM_Task_Perodic10ms();
    }
#endif
}


/* CMTW0設定 */
/* タイマプリスケーラ, ICU, OCU, クリア要因 */
/* タイマの積算値 @PCLKB=60MHz */
#define CMWCR0_VALUE (0x0008u)
#define CMWIOR0_VALUE (0x8000u)
#define CMWCOR0_VALUE (7499u)
#define CMWCNT0_INIT (0u)


static void SchM_Cfg_StartTimer(void)
{
    /* レジスタプロテクト解除 */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY | Mcu_PRCR_PRC1));
    
    /* モジュールスタンバイ解除 */
    Mcu_SFR_Write(MSTP(CMTW0), FALSE);
    
    /* レジスタプロテクト */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY));
    
    /* 割り込みレベルを設定 */
    Mcu_SFR_Write(IPR(CMTW0, CMWI0), 8);
    /* 割り込み許可 */
    Mcu_SFR_Write(IEN(CMTW0, CMWI0), TRUE);
    
    /* タイマ初期化 */
    /* 初期化の前にあらかじめタイマを停止 */
    Mcu_SFR_Write(CMTW0.CMWSTR.BIT.STR, FALSE);
    
    /* リソース初期化 */
    /* 1ms at PCLKB=60MHz */
    Mcu_SFR_Write(CMTW0.CMWCR.WORD, CMWCR0_VALUE);
    Mcu_SFR_Write(CMTW0.CMWIOR.WORD, CMWIOR0_VALUE);
    Mcu_SFR_Write(CMTW0.CMWCOR, CMWCOR0_VALUE);
    Mcu_SFR_Write(CMTW0.CMWCNT, CMWCNT0_INIT);

    /* タイマ開始 */
    Mcu_SFR_Write(CMTW0.CMWSTR.BIT.STR, TRUE);
}


uint32_t SchM_GetSystemCounter(void)
{
    uint32_t ui32t_cnt;

    Mcu_DI();

    /* タイマカウンタを取得 */
    ui32t_cnt = Mcu_SFR_Read(CMTW0.CMWCNT);

    /* 割り込み要因ありなら */
    if (Mcu_SFR_Read(IR(CMTW0, CMWI0)) == TRUE)
    {
        /* コンペアマッチコンスタントレジスタ値とする */
        ui32t_cnt = CMWCOR0_VALUE + 1;
    }

    ui32t_cnt = (1000 * ui32t_cnt) / (CMWCOR0_VALUE + 1);
    ui32t_cnt += SchM_Get1msCounter() * 1000;

    Mcu_EI();

    return (ui32t_cnt);
}


void SchM_TaskMeasuremntStart(SchM_TaskType task)
{
    if( task <= TASK_NUM ) {
        SchM_TaskMeasuremntTable[task].FirstTime = SchM_GetSystemCounter();
    }
}


void SchM_TaskMeasuremntEnd(SchM_TaskType task)
{
    if( task <= TASK_NUM ) {
        SchM_TaskMeasuremntTable[task].SecondTime = SchM_GetSystemCounter();
        SchM_TaskMeasuremntTable[task].TaskTime = SchM_DiffSystemCounter(SchM_TaskMeasuremntTable[task].SecondTime, SchM_TaskMeasuremntTable[task].FirstTime);
        if (SchM_TaskMeasuremntTable[task].TaskTime > SchM_TaskMeasuremntTable[task].PeakTime)
        {
            SchM_TaskMeasuremntTable[task].PeakTime = SchM_TaskMeasuremntTable[task].TaskTime;
        }
    }
}
