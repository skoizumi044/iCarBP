/**
 * @file Buzzer.h
 * @brief ブザードライバ
 */

#ifndef __Buzzer_H
#define __Buzzer_H


#ifdef __cplusplus
extern "C" {
#endif


void Buzzer_Init(void);
void Buzzer_Start(uint32_t ui32t_freq, uint32_t ui32t_timems);
void Buzzer_Stop(void);


#ifdef __cplusplus
}
#endif


#endif
