/**
 * @file MotorDrv.c
 * @brief モータを駆動する
 */
#include <Std_Types.h>
#include <SystemServices/Mcu.h>

#include "MotorDrv.h"
#include "Mtu3Drv.h"

#define MotorDrv_Carrier_Freq   (3000)
#define MotorDrv_DeadTime       (0)
#define MotorDrv_InvertDeadTime (50 / 10)


int16_t MotorDrv_LSpeed;
int16_t MotorDrv_RSpeed;

uint16_t MotorDrv_LFTimer;
uint16_t MotorDrv_LRTimer;
uint16_t MotorDrv_RFTimer;
uint16_t MotorDrv_RRTimer;


static void MotorDrv_CalDuty(int16_t i16t_speed, uint16_t ui16_carrier, uint16_t *ui16tp_fwd, uint16_t *ui16tp_rvs);
static int16_t MotorDrv_CalReq(int16_t reqRaw, uint16_t *timerF, uint16_t *timerR);



/**
 * @brief モータを初期化する
 * @note Mtu3Drv_Init()の後に呼び出しすること
 */
void MotorDrv_Init(void)
{
    MotorDrv_LSpeed = VAL_0;
    MotorDrv_RSpeed = VAL_0;
    MotorDrv_LFTimer = VAL_0;
    MotorDrv_LRTimer = VAL_0;
    MotorDrv_RFTimer = VAL_0;
    MotorDrv_RRTimer = VAL_0;
    
    /* リソースを初期化する */
    Mtu3Drv_CompPWM_Init(Mtu3Drv_CH3, MotorDrv_Carrier_Freq, MotorDrv_DeadTime, MotorDrv_Carrier_Freq, MotorDrv_Carrier_Freq, MotorDrv_Carrier_Freq);
    Mtu3Drv_CompPWM_Init(Mtu3Drv_CH6, MotorDrv_Carrier_Freq, MotorDrv_DeadTime, MotorDrv_Carrier_Freq, MotorDrv_Carrier_Freq, MotorDrv_Carrier_Freq);
    Mtu3Drv_CompPWM_Start(TRUE, TRUE);
}


/**
 * @brief 定期処理
 */
void MotorDrv_Periodic(void)
{
    uint16_t ui16t_lfwd;
    uint16_t ui16t_lrvs;
    uint16_t ui16t_rfwd;
    uint16_t ui16t_rrvs;
    
    int16_t i16t_left = MotorDrv_CalReq(MotorDrv_LSpeed, &MotorDrv_LFTimer, &MotorDrv_LRTimer);
    int16_t i16t_right = MotorDrv_CalReq(MotorDrv_RSpeed, &MotorDrv_RFTimer, &MotorDrv_RRTimer);


    /* Dutyを算出 */
    MotorDrv_CalDuty(i16t_left, MotorDrv_Carrier_Freq, &ui16t_lfwd, &ui16t_lrvs);
    MotorDrv_CalDuty(i16t_right, MotorDrv_Carrier_Freq, &ui16t_rfwd, &ui16t_rrvs);
    
    /* Dutyを設定 */
    MotorDrv_SetMotorDuty(ui16t_lfwd, ui16t_lrvs, ui16t_rfwd, ui16t_rrvs);
}


/**
 * @brief 指令値計算
 *
 */
static int16_t MotorDrv_CalReq(int16_t reqRaw, uint16_t *timerF, uint16_t *timerR)
{
    *timerF = (*timerF <= VAL_0) ? (VAL_0) : (*timerF - 1);
    *timerR = (*timerR <= VAL_0) ? (VAL_0) : (*timerR - 1);

    /* STOP */
    if (reqRaw == MotorDrv_Speed_Stop) {
        return reqRaw;
    
    /* BRAKE */
    } else if (reqRaw == MotorDrv_Speed_Brake) {
        return reqRaw;
    
    /* 前進 */
    } else if (reqRaw > MotorDrv_Speed_Stop) {
        if (*timerF > VAL_0) {
            return MotorDrv_Speed_Brake;
        } else {
            *timerR = MotorDrv_InvertDeadTime;
            return reqRaw;
        }
        
    /* 後退 */
    } else {
        if (*timerR > VAL_0) {
            return MotorDrv_Speed_Brake;
        } else {
            *timerF = MotorDrv_InvertDeadTime;
            return reqRaw;
        }
    }
}


/**
 * @brief モータ駆動Dutyを設定する
 * @param ui16t_lfwd・・・L Motor forward duty
 * @param ui16t_lrvs・・・L Motor reverse duty
 * @param ui16t_lfwd・・・R Motor forward duty
 * @param ui16t_lrvs・・・R Motor reverse duty
 */
void MotorDrv_SetMotorDuty(uint16_t ui16t_lfwd, uint16_t ui16t_lrvs, uint16_t ui16t_rfwd, uint16_t ui16t_rrvs)
{
    uint16_t ui16t_mtu7a_duty;
    uint16_t ui16t_mtu7b_duty;
    
    /* Mtu7A, 7BのDutyを取得 */
    Mtu3Drv_CompPWM_GetDuty(Mtu3Drv_CH6, NULL, &ui16t_mtu7a_duty, &ui16t_mtu7b_duty);
    
    /* Dutyを更新 */
    Mtu3Drv_CompPWM_SetDuty(Mtu3Drv_CH3, ui16t_lrvs, ui16t_lfwd, ui16t_rfwd);
    Mtu3Drv_CompPWM_SetDuty(Mtu3Drv_CH6, ui16t_rrvs, ui16t_mtu7a_duty, ui16t_mtu7b_duty);
}


/**
 * @brief モータ速度からDutyを算出する
 */
static void MotorDrv_CalDuty(int16_t i16t_speed, uint16_t ui16_carrier, uint16_t *ui16tp_fwd, uint16_t *ui16tp_rvs)
{
    uint16_t ui16t_fwd;
    uint16_t ui16t_rvs;
    
    /* 範囲外のスピードを指定 */
    if ((i16t_speed < -MotorDrv_Speed_Max) || (MotorDrv_Speed_Max < i16t_speed)) {
        i16t_speed = MotorDrv_Speed_Brake;
    }
    
    /* STOP */
    if (i16t_speed == MotorDrv_Speed_Stop) {
        ui16t_fwd = ui16_carrier;
        ui16t_rvs = ui16_carrier;
        
    /* BRAKE */
    } else if (i16t_speed == MotorDrv_Speed_Brake) {
        ui16t_fwd = VAL_0;
        ui16t_rvs = VAL_0;
        
    /* 前進 */
    } else if (i16t_speed > MotorDrv_Speed_Stop) {
        ui16t_fwd = ui16_carrier - ((i16t_speed * ui16_carrier) / MotorDrv_Speed_Max);
        ui16t_rvs = ui16_carrier;
        
    /* 後退 */
    } else {
        /* 符号を反転 */
        i16t_speed = -i16t_speed;
        
        ui16t_fwd = ui16_carrier;
        ui16t_rvs = ui16_carrier - ((i16t_speed * ui16_carrier) / MotorDrv_Speed_Max);
    }
    
    
    *ui16tp_fwd = ui16t_fwd;
    *ui16tp_rvs = ui16t_rvs;
}


/**
 * @brief モータ速度を設定する
 * @param i16t_left・・・L Motor Speed
 * @param i16t_right・・・R Motor Speed
 */
void MotorDrv_SetMotorSpeed(int16_t i16t_left, int16_t i16t_right)
{
    Mcu_DI();
    
    /* 設定値を変数に記憶 */
    MotorDrv_LSpeed = i16t_left;
    MotorDrv_RSpeed = i16t_right;

    Mcu_EI();
}


/**
 * @brief モータ速度を取得する
 * @param i16tp_left・・・L Motor Speed buffer pointer
 * @param i16tp_right・・・R Motor Speed buffer pointer
 */
void MotorDrv_GetMotorSpeed(int16_t *i16tp_left, int16_t *i16tp_right)
{
    *i16tp_left = MotorDrv_LSpeed;
    *i16tp_right = MotorDrv_RSpeed;
}
