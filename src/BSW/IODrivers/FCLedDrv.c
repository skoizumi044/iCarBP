/**
 * @file FCLedDrv.c
 * @brief Full Color LED駆動制御を行う
 */
#include <Std_Types.h>
#include <SystemServices/Mcu.h>

#include "Mtu3Drv.h"
#include "FCLedDrv.h"

#define MTU0_Carrier_Freq       (15625)
#define LedDrv_MAX_DUTY         (100)


uint8_t LedDrv_Duty_FCLed_R;
uint8_t LedDrv_Duty_FCLed_G;
uint8_t LedDrv_Duty_FCLed_B;


/**
 * @brief LEDを初期化する
 * @note Mtu3Drv_Init()の後に呼び出しすること
 */
void FCLedDrv_Init(void)
{
    LedDrv_Duty_FCLed_R = VAL_0;
    LedDrv_Duty_FCLed_G = VAL_0;
    LedDrv_Duty_FCLed_B = VAL_0;
    
    Mtu3Drv_PWM2_Init(Mtu3Drv_CH0, MTU0_Carrier_Freq, MTU0_Carrier_Freq, MTU0_Carrier_Freq, MTU0_Carrier_Freq);
}


/**
 * @brief LEDを初期化する
 * @note Mtu3Drv_Init()の後に呼び出しすること
 */
void FCLedDrv_DeInit(void)
{
}


/**
 * @brief フルカラーLEDを設定
 * @param ui8t_r 赤色の明るさ
 * @param ui8t_g 緑色の明るさ
 * @param ui8t_b 青色の明るさ
 */
void FCLedDrv_SetColorLed(uint8_t ui8t_r, uint8_t ui8t_g, uint8_t ui8t_b)
{
    uint16_t ui16t_duty_r;
    uint16_t ui16t_duty_g;
    uint16_t ui16t_duty_b;
    
    /* 上限ガード・100%設定 */
    if (ui8t_r > LedDrv_MAX_DUTY) {
        ui8t_r = LedDrv_MAX_DUTY;
    }
    
    if (ui8t_g > LedDrv_MAX_DUTY) {
        ui8t_g = LedDrv_MAX_DUTY;
    }
    
    if (ui8t_b > LedDrv_MAX_DUTY) {
        ui8t_b = LedDrv_MAX_DUTY;
    }
    
    
    /* 設定値を変数に記憶 */
    LedDrv_Duty_FCLed_R = ui8t_r;
    LedDrv_Duty_FCLed_G = ui8t_g;
    LedDrv_Duty_FCLed_B = ui8t_b;
    
    ui16t_duty_r = MTU0_Carrier_Freq - (((uint32_t)ui8t_r * (uint32_t)(MTU0_Carrier_Freq)) / (uint32_t)LedDrv_MAX_DUTY);
    ui16t_duty_g = MTU0_Carrier_Freq - (((uint32_t)ui8t_g * (uint32_t)(MTU0_Carrier_Freq)) / (uint32_t)LedDrv_MAX_DUTY);
    ui16t_duty_b = MTU0_Carrier_Freq - (((uint32_t)ui8t_b * (uint32_t)(MTU0_Carrier_Freq)) / (uint32_t)LedDrv_MAX_DUTY);
    
    Mtu3Drv_PWM2_SetDuty(Mtu3Drv_CH0, ui16t_duty_r, ui16t_duty_b, ui16t_duty_g);
}


/**
 * @brief フルカラーLED輝度を取得
 * @param ui8tp_r 赤色の明るさ
 * @param ui8tp_g 緑色の明るさ
 * @param ui8tp_b 青色の明るさ
 */
void FCLedDrv_GetColorLed(uint8_t *ui8tp_r, uint8_t *ui8tp_g, uint8_t *ui8tp_b)
{
    *ui8tp_r = LedDrv_Duty_FCLed_R;
    *ui8tp_g = LedDrv_Duty_FCLed_G;
    *ui8tp_b = LedDrv_Duty_FCLed_B;
}
