/**
 * @file Mtu3Drv.h
 * @brief Mtu3リソースの設定を行う
 */

#ifndef __Mtu3Drv_H
#define __Mtu3Drv_H


#ifdef __cplusplus
extern "C" {
#endif


#define Mtu3Drv_CH0        (0)
#define Mtu3Drv_CH1        (1)
#define Mtu3Drv_CH2        (2)
#define Mtu3Drv_CH3        (3)
#define Mtu3Drv_CH4        (4)
#define Mtu3Drv_CH5        (5)
#define Mtu3Drv_CH6        (6)
#define Mtu3Drv_CH7        (7)
#define Mtu3Drv_CH8        (8)


void Mtu3Drv_Init(void);
void Mtu3Drv_PWM2_Init(uint8_t ui8t_ch, uint16_t ui16t_carrier, uint16_t ui16t_duty1, uint16_t ui16t_duty2, uint16_t ui16t_duty3);
void Mtu3Drv_PWM2_SetDuty(uint8_t ui8t_ch, uint16_t ui16t_duty1, uint16_t ui16t_duty2, uint16_t ui16t_duty3);
void Mtu3Drv_CompPWM_Init(uint8_t ui8t_ch, uint16_t ui16t_carrier, uint16_t ui16t_deadtime, uint16_t ui16t_duty1, uint16_t ui16t_duty2, uint16_t ui16t_duty3);
void Mtu3Drv_CompPWM_Start(boolean bt_mtu3_start, boolean bt_mtu6_start);
void Mtu3Drv_CompPWM_SetDuty(uint8_t ui8t_ch, uint16_t ui16t_duty1, uint16_t ui16t_duty2, uint16_t ui16t_duty3);
void Mtu3Drv_CompPWM_GetDuty(uint8_t ui8t_ch, uint16_t *ui16tp_duty1, uint16_t *ui16tp_duty2, uint16_t *ui16tp_duty3);


#ifdef __cplusplus
}
#endif


#endif
