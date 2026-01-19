/**
 * @file LcdDrv.h
 * @brief LCD表示機能を提供する
 */

#ifndef __LcdDrv_H
#define __LcdDrv_H


#ifdef __cplusplus
extern "C" {
#endif


#define LcdDrv_X_MAX                (16u)
#define LcdDrv_Y_MAX                (2u)


void LcdDrv_Init(void);
void LcdDrv_DeInit(void);

boolean LcdDrv_IsActive(void);
boolean LcdDrv_IsFail(void);
boolean LcdDrv_WriteData(const uint8_t *ui8tp_data, uint16_t ui16t_length);
boolean LcdDrv_WriteCommand(uint8_t ui8t_cmd);
void LcdDrv_PeriodicTask(void);


void LcdDrv_clear(void);
void LcdDrv_home(void);
void LcdDrv_setCursor(uint8_t ui8t_y, uint8_t ui8t_x);
void LcdDrv_putchar(char ct_text);
void LcdDrv_print(const char *szt_text);

void LcdDrv_setNum(uint32_t ui32t_num, uint8_t ui8t_numdigit);
void LcdDrv_setNumNoZeroSup(uint32_t ui32t_num, uint8_t ui8t_numdigit);
void LcdDrv_setHex(uint32_t ui32t_num, uint8_t ui8t_numdigit);
void LcdDrv_setBin(uint32_t ui32t_num, uint8_t ui8t_numdigit);
boolean LcdDrv_update(void);


#ifdef __cplusplus
}
#endif


#endif
