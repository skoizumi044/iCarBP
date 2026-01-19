/**
 * @file port.c
 * @brief port api
 */

#include <Arduino.h>

#include <BSW/IODrivers/Dio.h>
#include <BSW/IODrivers/Adc.h>
#include <BSW/IODrivers/Distance.h>
#include <BSW/IODrivers/MotorDrv.h>
#include <BSW/IODrivers/FCLedDrv.h>
#include <BSW/IODrivers/Buzzer.h>
#include <BSW/IODrivers/IODrv.h>


static void SetFLed(uint32_t arg, int value);
static void SetMotor(uint32_t arg, int value);


/**
 * @brief Pinのモードを設定する
 * @param pin pin番号
 * @param mode モード (OUTPUT/INPUT/INPUT_PULLUP)
 * @note 本関数は互換性確保のために定義されており、呼び出しても効果はない
 */
void pinMode(uint8_t pin, uint8_t mode)
{
}


/**
 * @brief Pinにデジタル出力値を設定する
 * @param pin pin番号
 * @param val 出力値 (HIGH / LOW)
 */
void digitalWrite(uint8_t pin, uint8_t val)
{
    switch (pin)
    {
    case PIN_LED1:
        Dio_WriteChannel(PB6, val);
        break;
    case PIN_LED2:
        Dio_WriteChannel(PB7, val);
        break;
    case PIN_LED3:
        Dio_WriteChannel(PB4, !val);
        break;
    case PIN_LED4:
        Dio_WriteChannel(PB5, !val);
        break;
    case PIN_LED5:
        Dio_WriteChannel(PA6, !val);
        break;
    case PIN_LED6:
        Dio_WriteChannel(PA7, !val);
        break;
    default:
        break;
    }
}


/**
 * @brief Pinの現在のデジタル入力値を取得する
 * @param pin pin番号
 * @return 現在のPinの入力値 (HIGH / LOW)
 */
int digitalRead(uint8_t pin)
{
    switch (pin)
    {
    case PIN_BTN1:
        return (!Dio_ReadChannel(PB2));
    case PIN_BTN2:
        return (!Dio_ReadChannel(PB1));
    default:
        break;
    }
    
    return (LOW);
}


/**
 * @brief Pinの現在のアナログ入力値を取得する
 * @param pin pin番号
 * @return 現在のアナログ入力値
 */
int analogRead(uint8_t pin)
{
    switch (pin)
    {
    case PIN_VOLUME:
        return (IODrv_Volume_Get());
    case PIN_DISTANCE:
        return (Distance_GetValue());
    case PIN_BRIGHTNESS:
        return (IODrv_Ill_GetBrightness());
    case PIN_LINE_L:
        return (Adc_Read(0, 2));
    case PIN_LINE_R:
        return (Adc_Read(0, 1));
    case PIN_TOGGLE:
        return (IODrv_Toggle_Get());
    default:
        break;
    }
    
    return (0);
}


/**
 * @brief アナログ基準電圧を設定する
 * @param mode アナログ基準電圧 (DEFAULT/INTERNAL/EXTERNAL)
 * @note 本関数は互換性確保のために定義されており、呼び出しても効果はない
 */
void analogReference(uint8_t mode)
{
}


/**
 * @brief Pinにアナログ出力値を設定する
 * @param pin pin番号
 * @param val 出力値
 */
void analogWrite(uint8_t pin, int val)
{
    switch (pin)
    {
    case PIN_MOTOR_L:
        SetMotor(0, val);
        break;
    case PIN_MOTOR_R:
        SetMotor(1, val);
        break;
    case PIN_BUZZER:
        Buzzer_Start(val, 0);
        break;
    case PIN_FLED_R:
        SetFLed(0, val);
        break;
    case PIN_FLED_G:
        SetFLed(1, val);
        break;
    case PIN_FLED_B:
        SetFLed(2, val);
        break;
    default:
        break;
    }
}


/**
 * @brief Set Full Colour Led
 * @param arg 0x00 r, 0x01 g, 0x02 b
 * @param value 0-100
 */
static void SetFLed(uint32_t arg, int value)
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
    /* Get Curren Duty */
    FCLedDrv_GetColorLed(&r, &g, &b);
    
    /* Update Duty */
    if (arg == 0) {
        r = value;
    }
    else if (arg == 1) {
        g = value;
    }
    else if (arg == 2) {
        b = value;
    }
    else
    {
        /* nothing to do */
    }
    
    /* Set Duty */
    FCLedDrv_SetColorLed(r, g, b);
}


/**
 * @brief Set Motor
 * @param arg 0x00 l, 0x01 r
 * @param value 0-100
 */
static void SetMotor(uint32_t arg, int value)
{
    int16_t l;
    int16_t r;
    
    /* Get Current Duty */
    MotorDrv_GetMotorSpeed(&l, &r);
    
    if (-100 <= value && value <= 100)
    {
        /* Limit 90% */
        value = value * 90 / 10;
    }
    else
    {
        value = MotorDrv_Speed_Brake;
    }

    /* Update Duty */
    if (arg == 0)
    {
        l = value;
    }
    else if (arg == 1)
    {
        r = value;
    }
    else
    {
        /* nothing to do */
    }
    
    
    /* Set Duty */
    MotorDrv_SetMotorSpeed(l, r);
}
