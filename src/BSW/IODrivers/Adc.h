/**
 * @file Adc.h
 * @brief A/D変換機能を提供する
 */

#ifndef __Adc_H
#define __Adc_H


#include "Adc_Cfg.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @def A/D変換無効時の戻り値
 */
#define Adc_INVALID_VALUE           (0xFFFFu)

void Adc_Init(void);
void Adc_StartConversion(void);

uint16_t Adc_Read(uint8_t ui8t_unit, uint8_t ui8t_ch);


#ifdef __cplusplus
}
#endif


#endif
