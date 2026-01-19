/**
 * @file FCLedDrv.h
 * @brief Full Color LED駆動制御を行う
 */

#ifndef __FCLedDrv_H
#define __FCLedDrv_H


#ifdef __cplusplus
extern "C" {
#endif


void FCLedDrv_Init(void);
void FCLedDrv_DeInit(void);
void FCLedDrv_SetColorLed(uint8_t ui8t_r, uint8_t ui8t_g, uint8_t ui8t_b);
void FCLedDrv_GetColorLed(uint8_t *ui8tp_r, uint8_t *ui8tp_g, uint8_t *ui8tp_b);


#ifdef __cplusplus
}
#endif


#endif
