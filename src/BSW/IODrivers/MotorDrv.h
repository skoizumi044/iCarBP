/**
 * @file MotorDrv.h
 * @brief モータを駆動する
 */

#ifndef __MotorDrv_H
#define __MotorDrv_H


#ifdef __cplusplus
extern "C" {
#endif


#define MotorDrv_Speed_Stop     (0)
#define MotorDrv_Speed_Max      (1000)
#define MotorDrv_Speed_Brake    (-32768)

void MotorDrv_Init(void);
void MotorDrv_Periodic(void);
void MotorDrv_SetMotorDuty(uint16_t ui16t_lfwd, uint16_t ui16t_lrvs, uint16_t ui16t_rfwd, uint16_t ui16t_rrvs);
void MotorDrv_SetMotorSpeed(int16_t i16t_left, int16_t i16t_right);
void MotorDrv_GetMotorSpeed(int16_t *i16tp_left, int16_t *i16tp_right);


#ifdef __cplusplus
}
#endif


#endif
