/**
 * @file SchM_Cfg.c
 * @brief タスクの設定ファイル
 */

#ifndef __SchM_Cfg_H
#define __SchM_Cfg_H

#include "SchM.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    TASK_1MS,
    TASK_10MS,

    TASK_NUM
} SchM_TaskType;

typedef struct {
    uint32_t FirstTime;
    uint32_t SecondTime;
    uint32_t TaskTime;
    uint32_t PeakTime;
} SchM_Task_Config;

void SchM_Cfg_Init(void);
void SchM_Cfg_Task_Idle(void);
void SchM_Cfg_Task_Periodic10ms(void);
void SchM_Cfg_Task_Int1ms(void);


#define SchM_Periodic10ms_Invoke_IDLE   (0)
#define SchM_Periodic10ms_Invoke_INT    (1)
#define SchM_Periodic_InvokeMethod  (SchM_Periodic10ms_Invoke_INT)


#ifdef __cplusplus
}
#endif


#endif
