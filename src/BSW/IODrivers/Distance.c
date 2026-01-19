/**
 * @file Distance.c
 * @brief 超音波センサによる距離測定
 */

#include <Std_Types.h>
#include <SystemServices/Mcu.h>


#include "Distance.h"
#include "Dio.h"


#define Distance_State_STOPPED      (0x00)
#define Distance_State_READY        (0x01)
#define Distance_State_SAMPLLING    (0x02)
#define Distance_State_WAIT         (0x03)

#define Distance_WaitTime           (5)
#define Distance_WaitTime10us       (120)
#define Distance_NoDetect_Thresh    (5)

static uint8_t Distance_State = Distance_State_STOPPED;
static boolean Distance_IsValid;
static uint8_t Distance_TaskCounter;
static uint8_t Distance_NoDetectCnt;

uint32_t Distance_Value;

static void Distance_Wait10us(void);

/**
 * @brief 測距ドライバを初期化する
 */
void Distance_Init(void)
{
    Distance_State = Distance_State_WAIT;
    Distance_TaskCounter = IDX_0;
    Distance_NoDetectCnt = VAL_0;
    
    Distance_Value = Distance_INFINITY;
    Distance_IsValid = FALSE;
    
    /* Trigger=Lo */
    Dio_WriteChannel(P14, LO);
    
     /* レジスタプロテクト解除 */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY | Mcu_PRCR_PRC1));
    
    /* モジュールスタンバイ解除 */
    /* TPU0～TPU6, TPUAは共通のレジスタためTPU0を指定 */
    Mcu_SFR_Write(MSTP(TPU0), FALSE);
    
    /* レジスタプロテクト */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY));
    
    /* タイマ停止 */
    Mcu_SFR_WriteBit(&TPUA.TSTR.BYTE, 3, FALSE);
    
    /* TPU初期設定 */
    Mcu_SFR_Write(TPU3.TCR.BYTE, 0x33u);
    Mcu_SFR_Write(TPU3.TMDR.BYTE, 0x40u);
    Mcu_SFR_Write(TPU3.TIORH.BYTE, 0x98u);
    Mcu_SFR_Write(TPU3.TIORL.BYTE, 0x00u);
    Mcu_SFR_Write(TPU3.TIER.BYTE, 0x40u);
    Mcu_SFR_Write(TPU3.NFCR.BYTE, 0x00u);
    
    /* TSRダミーリード・クリア */
    Mcu_SFR_Read(TPU3.TSR.BYTE);
    Mcu_SFR_Write(TPU3.TSR.BYTE, 0x00);
    
    /* カウンタ初期化 */
    Mcu_SFR_Write(TPU3.TCNT, 0x0000);
    Mcu_SFR_Write(TPU3.TGRA, 0x0000);
    Mcu_SFR_Write(TPU3.TGRB, 0x0000);
    Mcu_SFR_Write(TPU3.TGRC, 0x0000);
    Mcu_SFR_Write(TPU3.TGRD, 0x0000);
    
    /* タイマ開始 */
    Mcu_SFR_WriteBit(&TPUA.TSTR.BYTE, 3, TRUE);
}


/**
 * @brief ドライバ用の10us待機
 * @note ICLK=120MHz想定
 */
static void Distance_Wait10us(void)
{
    /* 最適化による処理時間のブレを少なくす為 */
    /* ループカウンタを意図的に32bit signedレジスタ変数に割り付け */
    register int32_t si32t_cnt;

    /* @120MHz 2400 NOP */
    /* 3240 = 8NOPs + 2LOOP Instractions (DEC, JMP) */
    si32t_cnt = Distance_WaitTime10us;
    while (si32t_cnt-- > IDX_0) {
#if Mcu_Clk_Cfg_ILCK_FREQ_KHZ == (120000)
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
#else
#error "LcdDrv_Wait27us() Invalid Mcu_Clk_Cfg_ILCK_FREQ_KHZ. Please configure."
#endif
    }
}


/**
 * @brief 距離サンプリング定期処理
 */
void Distance_Periodic(void)
{
    uint32_t ui32t_tgrb;
    
    switch (Distance_State) {
    case Distance_State_STOPPED:
        /* 何もしない */
        break;
    case Distance_State_READY:
        Distance_TaskCounter = IDX_0;
        Distance_State = Distance_State_SAMPLLING;
        
        /* タイマステータスをクリア */
        Mcu_SFR_Write(TPU3.TSR.BIT.TGFA, FALSE);
        Mcu_SFR_Write(TPU3.TSR.BIT.TGFB, FALSE);
        
        /* Trigger=Hi */
        Dio_WriteChannel(P14, HI);

        /* 10us待機 */
        Distance_Wait10us();

        /* 最後にTrigger=Lo */
        Dio_WriteChannel(P14, LO);
        
        break;
    case Distance_State_SAMPLLING:
        /* 20ms待機 */
        Distance_TaskCounter++;
        if (Distance_TaskCounter >= IDX_2) {
            Distance_TaskCounter = IDX_0;
            
            /* 立ち上がりエッジと立下りエッジ検出済み */
            if ((Mcu_SFR_Read(TPU3.TSR.BIT.TGFA) == TRUE) && (Mcu_SFR_Read(TPU3.TSR.BIT.TGFB) == TRUE)) {
                
                /* タイマ値を取得 */
                ui32t_tgrb = Mcu_SFR_Read(TPU3.TGRB);
                
                /* タイマ値を判定 */
                /* PCLKB = 60MHz */
                /* 音の速度=340[m/s] = 340000[mm/s] */
                /* 1[mm]進むのにかかる時間 = 1/340000 = 2.94118 * 10^-6[s/mm] */
                /* 往復なので2倍 = 5.88235 * 10^-6[s/mm] */
                /* タイマ1カウントの時間[s] = (1/(60/16/2) * 10^-6) = 0.533333 * 10^-6 */
                /* 5.88235 / 0.53333 = 11.029475 */
                /* 小数点以下を有効桁とするため1000倍して計算 */
                Distance_Value = ((ui32t_tgrb) * 1000) / 11029;
                
                /* 最大値ガード */
                if (Distance_Value > Distance_INFINITY)
                {
                    Distance_Value = Distance_INFINITY;
                }
                
                /* 未検出カウンタを初期化 */
                Distance_NoDetectCnt = VAL_0;

            /* 距離 = MAX */
            } else {
                /* 距離がMAXの場合は一定時間前回値保持 */
                if (Distance_NoDetectCnt < Distance_NoDetect_Thresh) {
                    Distance_NoDetectCnt++;

                /* 一定時間距離MAXのままであれば距離をMAXに設定 */
                } else {
                    /* 距離 = MAX */
                    Distance_Value = Distance_INFINITY;
                }
            }
            
            /* 有効値を格納 */
            Distance_IsValid = TRUE;
            
            /* WAIT状態へ遷移 */
            Distance_State = Distance_State_WAIT;
        }
        break;
    case Distance_State_WAIT:
        /* 待機時間分待機 */
        Distance_TaskCounter++;
        if (Distance_TaskCounter >= Distance_WaitTime) {
            Distance_TaskCounter = IDX_0;
            
            /* READY状態に遷移 */
            Distance_State = Distance_State_READY;
        }
        break;
    default:
        Distance_State = Distance_State_STOPPED;
        break;
    }
}


/**
 * @brief 距離を取得する
 * @return 距離[mm]
 */
uint32_t Distance_GetValue(void)
{
    return (Distance_Value);
}


/**
 * @brief 距離取得状態を取得する
 */
boolean Distance_GetIsValid(void)
{
    return (Distance_IsValid);
}
