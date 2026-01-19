/**
 * @file Sci.h
 * @brief Sci通信機能を提供する
 * @author KSEII T.Terazawa
 * @copyright 2020 Kernel Software Engineering
 */

#ifndef __Sci_H
#define __Sci_H


#ifdef __cplusplus
extern "C" {
#endif


/**
 * 関数宣言
 */
void Sci_Init(uint32_t ui32t_baud);
void Sci_DeInit(void);
void Sci_SetBaud(uint32_t ui32t_baud);
void Sci_Send1B(uint8_t ui8t_sendData);
void Sci_WaitForSendEnd(void);
uint8_t Sci_Recv1B(void);
uint16_t Sci_GetRecvBytes(void);
uint16_t Sci_GetSendBufferRemain(void);
boolean Sci_Recv1BAsync(uint8_t *ui8t_recvData);
boolean Sci_Send1BAsync(uint8_t ui8t_sendData);


#ifdef __cplusplus
}
#endif


#endif
