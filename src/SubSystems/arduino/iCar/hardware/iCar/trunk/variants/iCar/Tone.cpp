/**
 * @file Tone.cpp
 * @brief Tone Generator for RX
 * @author KSEII T.Terazawa
 * @copyright 2020 Kernel Software Engineering
 */


#include <Arduino.h>
#include <BSW/IODrivers/Buzzer.h>


/**
 * @brief 指定した周波数の矩形波を生成
 * @param pin pin番号
 * @param frequency 周波数[Hz]
 * @param duration 出力時間 (0=無限) [Opt]
 */
void tone(uint8_t pin, unsigned int frequency, unsigned long duration)
{
    if (pin == PIN_BUZZER)
    {
        Buzzer_Start(frequency, duration);
    }
}


/**
 * @brief toneで開始された矩形波の生成を停止
 * @param pin pin番号
 */
void noTone(uint8_t pin)
{
    if (pin == PIN_BUZZER)
    {
        Buzzer_Stop();
    }
}
