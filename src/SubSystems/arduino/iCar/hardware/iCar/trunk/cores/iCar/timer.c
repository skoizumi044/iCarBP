/**
 * @file timer.c
 * @brief timer api
 */

#include <Arduino.h>
#include <BSW/SystemServices/Mcu.h>
#include <BSW/SystemServices/SchM.h>


/**
 * @brief プログラム起動からのミリ秒を返す
 * @return プログラム起動からのミリ秒
 */
uint32_t millis(void)
{
    return (SchM_Get1msCounter());
}


/**
 * @brief プログラム起動からのマイクロ秒を返す
 * @return プログラム起動からのマイクロ秒
 */
uint32_t micros(void)
{
    return (SchM_GetSystemCounter());
}


/**
 * @brief 指定したミリ秒待機する
 * @param ms 待機時間(ミリ秒)
 */
void delay(uint32_t ms)
{
    uint32_t ui32t_now;
    
    ui32t_now = micros();
    
    while (0 < ms)
    {
        while ((0 < ms) && (1000 <= (micros() - ui32t_now)))
        {
            ui32t_now += 1000;
            ms--;
        }
    }
}


/**
 * @brief 指定したマイクロ秒待機する
 * @param us 待機時間(マイクロ秒)
 */
void delayMicroseconds(uint32_t us)
{
    Mcu_WaitUS(us);
}
