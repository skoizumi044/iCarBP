/**
 * @file Fifo1B.c
 * @brief 1Byte FIFOを提供する
 */


#include <Std_Types.h>
#include "Fifo1B.h"


/**
 * @brief FIFOを初期化
 * @param pFifo Fifo構造体
 */
void Fifo1B_Init(const Fifo1B *pFifo)
{
    Fifo1B_Clear(pFifo);
}


/**
 * @brief FIFOを初期化する
 * @param pFifo Fifo構造体
 */
void Fifo1B_Clear(const Fifo1B *pFifo)
{
    Fifo1B_Info *info;
    info = pFifo->info;

    info->rdIdx = IDX_0;
    info->wrIdx = IDX_0;
    info->ovfFlag = FALSE;
}


/**
 * @brief FIFOにデータを書き込む
 * @param pFifo Fifo構造体
 * @param data 書き込みデータを格納しているバッファへのポインタ
 * @return TRUE: 成功, FALSE: 失敗
 * @note 本関数内の変数操作順序は割込み干渉を考慮して実装しているため、変更時は検討を要す
 */
boolean Fifo1B_Write(const Fifo1B *pFifo, const uint8_t *data)
{
    uint16_t rdIdx;
    uint16_t wrIdx;
    Fifo1B_Info *info;
    
    info = pFifo->info;
    
    rdIdx = info->rdIdx;
    wrIdx = info->wrIdx;
    
    /* 書き込みインデックスを進める */
    wrIdx = (wrIdx + IDX_1) & (pFifo->size - IDX_1);
    
    /* バッファフル */
    if (rdIdx == wrIdx) {
        /* オーバーフロー発生のためエラー処理 */
        info->ovfFlag = TRUE;
        return (FALSE);
    }
    
    /* データを書き込み */
    pFifo->buffer[wrIdx] = *data;
    /* インデックスを書き込み */
    info->wrIdx = wrIdx;
    
    return (TRUE);
}


/**
 * @brief FIFOにデータを書き込む
 * @param pFifo Fifo構造体
 * @param data 書き込みデータを格納しているバッファへのポインタ
 * @param size データサイズ
 * @return セットできたサイズ
 * @note 本関数内の変数操作順序は割込み干渉を考慮して実装しているため、変更時は検討を要す
 */
uint16_t Fifo1B_WriteMulti(const Fifo1B *pFifo, const uint8_t *data, uint16_t size)
{
    uint16_t rdIdx;
    uint16_t wrIdx;
    uint16_t idx;
    Fifo1B_Info *info;

    info = pFifo->info;

    rdIdx = info->rdIdx;
    wrIdx = info->wrIdx;

    for (idx = IDX_0; idx < size; idx++) {
        /* 書き込みインデックスを進める */
        wrIdx = (wrIdx + IDX_1) & (pFifo->size - IDX_1);
        
        /* バッファフル */
        if (rdIdx == wrIdx)
        {
            /* オーバーフロー発生のためエラー処理 */
            info->ovfFlag = TRUE;
            break;
        }
        
        /* データを書き込み */
        pFifo->buffer[wrIdx] = *data++;
        /* インデックスを書き込み */
        info->wrIdx = wrIdx;
    }


    return (idx);
}


/**
 * @brief FIFOからデータを読み込む
 * @param pFifo Fifo構造体
 * @param data 読み出しデータを格納するバッファへのポインタ
 * @return TRUE: 成功, FALSE: 失敗
 * @note 本関数内の変数操作順序は割込み干渉を考慮して実装しているため、変更時は検討を要す
 */
boolean Fifo1B_Read(const Fifo1B *pFifo, uint8_t *data)
{
    uint16_t rdIdx;
    uint16_t wrIdx;
    Fifo1B_Info *info;
    
    info = pFifo->info;
    
    wrIdx = info->wrIdx;
    rdIdx = info->rdIdx;
    
    
    /* データがない */
    if (rdIdx == wrIdx) {
        return (FALSE);
    }
    
    /* 読み出しインデックスを進める */
    rdIdx = (rdIdx + IDX_1) & (pFifo->size - IDX_1);

    /* データを読み出す */
    *data = pFifo->buffer[rdIdx];
    
    /* インデックスを書き込み */
    info->rdIdx = rdIdx;
    
    return (TRUE);
}


/**
 * @brief FIFOからデータを読み込む
 * @param pFifo Fifo構造体
 * @param data 読み出しデータを格納するバッファへのポインタ
 * @param size データサイズ
 * @return 読み出せたサイズ
 * @note 本関数内の変数操作順序は割込み干渉を考慮して実装しているため、変更時は検討を要す
 */
uint16_t Fifo1B_ReadMulti(const Fifo1B *pFifo, uint8_t *data, uint16_t size)
{
    uint16_t rdIdx;
    uint16_t wrIdx;
    uint16_t used;
    uint16_t idx;
    Fifo1B_Info *info;

    info = pFifo->info;

    wrIdx = info->wrIdx;
    rdIdx = info->rdIdx;


    /* データがない */
    if (rdIdx == wrIdx) {
        return (IDX_0);
    }

    /* バッファ使用数を取得 */
    used = (wrIdx - rdIdx) & (pFifo->size - IDX_1);

    /* 現在存在するデータ数でガードする */
    if (used < size) {
        size = used;
    }

    for (idx = IDX_0; idx < size; idx++) {
        /* インデックスを進める */
        rdIdx = (rdIdx + IDX_1) & (pFifo->size - IDX_1);
        /* データを読み出し */
        *data++ = pFifo->buffer[rdIdx];
        /* インデックスを書き込み */
        info->rdIdx = rdIdx;
    }

    return (idx);
}


/**
 * @brief バッファ空き容量を取得する
 * @param pFifo Fifo構造体
 * @return バッファの空き容量
 */
uint16_t Fifo1B_GetRemain(const Fifo1B *pFifo)
{
    uint16_t rdIdx;
    uint16_t wrIdx;
    Fifo1B_Info *info;
    
    info = pFifo->info;
    
    rdIdx = info->rdIdx;
    wrIdx = info->wrIdx;
    
    
    return ((pFifo->size - IDX_1) - ((wrIdx - rdIdx) & (pFifo->size - IDX_1)));
}


/**
 * @brief バッファの使用容量を取得する
 * @param pFifo Fifo構造体
 * @return バッファの使用容量
 */
uint16_t Fifo1B_GetUsed(const Fifo1B *pFifo)
{
    uint16_t rdIdx;
    uint16_t wrIdx;
    Fifo1B_Info *info;
    
    info = pFifo->info;
    
    rdIdx = info->rdIdx;
    wrIdx = info->wrIdx;
    
    return ((wrIdx - rdIdx) & (pFifo->size - IDX_1));
}


/**
 * @brief FIFOがオーバーフローしたかを返す
 * @param pFifo Fifo構造体
 * @return TRUE: オーバーフロー発生, FALSE: オーバーフロー未発生
 */
boolean Fifo1B_IsOverflow(const Fifo1B *pFifo)
{
    return (pFifo->info->ovfFlag);
}
