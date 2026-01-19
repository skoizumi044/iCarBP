/**
 * @file SchM.h
 * @brief タスクのスケジューリングを行う
 */

#ifndef __SchM_H
#define __SchM_H

#include "SchM_Cfg.h"


#ifdef __cplusplus
extern "C" {
#endif


void SchM_Init(void);
void SchM_Start(void);

uint32_t SchM_GetSystemCounter(void);

extern volatile uint32_t SchM_Timer1ms;
#define SchM_Get1msCounter()    ((const uint32_t)SchM_Timer1ms)


#ifdef __cplusplus
}
#endif


#endif
