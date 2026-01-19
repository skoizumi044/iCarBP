/**
 * @file Fifo1B.h
 * @brief 1Byte FIFOを提供する
 */

#ifndef __Fifo1B_H
#define __Fifo1B_H


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    volatile uint16_t rdIdx;            /**<読み出しインデックス */
    volatile uint16_t wrIdx;            /**<書き込みインデックス */
    boolean ovfFlag;                    /**<オーバーフローフラグ */
} Fifo1B_Info;

typedef struct {
    Fifo1B_Info *info;                  /**< 状態保持用RAM Fifo1B_Info変数へのポインタ */
    uint16_t size;                      /**< バッファのサイズ (2^nで指定する必要がある) */
    volatile uint8_t *buffer;           /**< バッファへのポインタ */
} Fifo1B;


void Fifo1B_Init(const Fifo1B *pFifo);
void Fifo1B_Clear(const Fifo1B *pInfo);
boolean Fifo1B_Write(const Fifo1B *pFifo, const uint8_t *data);
uint16_t Fifo1B_WriteMulti(const Fifo1B *pFifo, const uint8_t *data, uint16_t size);
boolean Fifo1B_Read(const Fifo1B *pFifo, uint8_t *data);
uint16_t Fifo1B_ReadMulti(const Fifo1B *pFifo, uint8_t *data, uint16_t size);
uint16_t Fifo1B_GetRemain(const Fifo1B *pFifo);
uint16_t Fifo1B_GetUsed(const Fifo1B *pFifo);

boolean Fifo1B_IsOverflow(const Fifo1B *pFifo);


#ifdef __cplusplus
}
#endif


#endif
