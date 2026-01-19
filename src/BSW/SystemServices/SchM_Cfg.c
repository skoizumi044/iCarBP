/**
 * @file SchM_Cfg.c
 * @brief タスクの設定ファイル
 */
#include <Std_Types.h>
#include <stdio.h>

#include "SchM.h"


#include <BSW/IODrivers/Adc.h>
#include <BSW/IODrivers/I2c.h>
#include <BSW/IODrivers/Mtu3Drv.h>
#include <BSW/IODrivers/MotorDrv.h>
#include <BSW/IODrivers/Buzzer.h>
#include <BSW/IODrivers/Distance.h>
#include <BSW/IODrivers/FCLedDrv.h>
#include <BSW/IODrivers/Sci.h>
#include <BSW/IODrivers/LcdDrv.h>

#include <BSW/IODrivers/IODrv.h>


extern void CallGate_init(void);
extern void CallGate_idle(void);
extern void CallGate_10ms(void);
extern void CallGate_int1ms(void);


/**
 * @brief 初期化
 * 初期化処理を記述
 */
void SchM_Cfg_Init(void)
{
    setbuf(stdout, NULL);       /* No buffering */

    Adc_Init();
    Buzzer_Init();

    Mtu3Drv_Init();
    MotorDrv_Init();

    Distance_Init();
    
    Sci_Init(57600);
    I2c_Init(0);
    LcdDrv_Init();
    FCLedDrv_Init();
    
    CallGate_init();
}


/**
 * @brief IDLEタスク
 * 他のタスクを実行していない時に実行する制御を定義
 */
void SchM_Cfg_Task_Idle(void)
{
    CallGate_idle();
}


/**
 * @brief 定期10msタスク
 * 10ms毎に実行する制御を定義
 */
void SchM_Cfg_Task_Periodic10ms(void)
{
    Distance_Periodic();
    MotorDrv_Periodic();
    
    IODrv_Periodic();
    
    CallGate_10ms();
    
    LcdDrv_PeriodicTask();

}


/**
 * @brief 割込み1msタスク
 * 1ms毎に実行する制御を定義
 * 本関数は割込みで呼び出しされる
 */
void SchM_Cfg_Task_Int1ms(void)
{
    Adc_StartConversion();
    IODrv_1msInt();

    CallGate_int1ms();
}
