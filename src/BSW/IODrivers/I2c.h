/**
 * @file I2c.h
 * @brief I2C通信機能を提供する
 */

#ifndef __I2c_H
#define __I2c_H


#ifdef __cplusplus
extern "C" {
#endif


void I2c_Init(uint8_t ui8t_ch);
boolean I2c_BusIsBusy(uint8_t ui8t_ch);
boolean I2c_SendStart(uint8_t ui8t_ch);
boolean I2c_SendStop(uint8_t ui8t_ch);
void I2c_SendAck(uint8_t ui8t_ch);
void I2c_SendNAck(uint8_t ui8t_ch);
boolean I2c_RecvAck(uint8_t ui8t_ch);
boolean I2c_ReadRaw(uint8_t ui8t_ch, uint8_t *ui8tp_data, uint16_t ui16t_size);
boolean I2c_WaitForRxComp(uint8_t ui8t_ch);
boolean I2c_WriteRaw(uint8_t ui8t_ch, const uint8_t *ui8tp_data, uint16_t ui16t_size);
boolean I2c_WriteIsFinish(uint8_t ui8t_ch, boolean *btp_success);
boolean I2c_Read(uint8_t ui8t_ch, uint8_t ui8t_addr, uint8_t *ui8tp_data, uint16_t ui16t_size);
boolean I2c_Write(uint8_t ui8t_ch, uint8_t ui8t_addr, const uint8_t *ui8tp_data, uint16_t ui16t_size);


#ifdef __cplusplus
}
#endif


#endif
