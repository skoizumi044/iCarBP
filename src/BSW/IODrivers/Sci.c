/**
 * @file Sci.c
 * @brief Sci通信機能を提供する
 * @author KSEII T.Terazawa
 * @copyright 2020 Kernel Software Engineering
 */

#include <Std_Types.h>
#include <SystemServices/Mcu.h>


#include "Sci.h"
#include "Sci_Cfg.h"


#if (SCI_CFG_TXBUFSIZE != 0) || (SCI_CFG_RXBUFSIZE != 0)
#include <LIB/Fifo1B.h>
#endif


/* Create Fifo Buffer */
#if SCI_CFG_TXBUFSIZE != 0
static uint8_t Sci_TxRingBuf[SCI_CFG_TXBUFSIZE];
static Fifo1B_Info Sci_TxFifoInfo;
static const Fifo1B Sci_TxFifo = {
    &Sci_TxFifoInfo,
    sizeof(Sci_TxRingBuf),
    &Sci_TxRingBuf[IDX_0],
};

static uint8_t Sci_IsTxIng;
#endif


#if SCI_CFG_RXBUFSIZE != 0
static uint8_t Sci_RxRingBuf[SCI_CFG_RXBUFSIZE];
static Fifo1B_Info Sci_RxFifoInfo;
static const Fifo1B Sci_RxFifo = {
    &Sci_RxFifoInfo,
    sizeof(Sci_RxRingBuf),
    &Sci_RxRingBuf[IDX_0],
};
#endif


/**
 * 変数宣言
 */
uint8_t Sci_ErrorCode;


/**
 * @brief Sciドライバを初期化する
 */
void Sci_Init(uint32_t ui32t_baud)
{
    Sci_ErrorCode = 0;

    /* FIFOを初期化 */
#if SCI_CFG_TXBUFSIZE != 0
    Fifo1B_Init(&Sci_TxFifo);
    Sci_IsTxIng = FALSE;
#endif

#if SCI_CFG_RXBUFSIZE != 0
    Fifo1B_Init(&Sci_RxFifo);
#endif


    /* レジスタプロテクト解除 */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY | Mcu_PRCR_PRC1));
    
    /* モジュールスタンバイ解除 */
    Mcu_SFR_Write(SCI_MSTP, FALSE);
    
    /* レジスタプロテクト */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY));
    
#if SCI_CFG_TXBUFSIZE != 0
    /* 割り込みレベルを設定(TXI) */
    Mcu_SFR_Write(SCI_IPR_TXI, 11);
    Mcu_SFR_Write(SCI_IEN_TXI, TRUE);
#endif

#if SCI_CFG_RXBUFSIZE != 0
    /* 割り込みレベルを設定(RXI/ERI) */
    Mcu_SFR_Write(SCI_IPR_RXI, 11);
    Mcu_SFR_Write(SCI_IEN_RXI, TRUE);

    /* ERI割り込み許可 */
    /* GROUP割り込みのためレベルはMcu_GroupInt.cで設定 */
    Mcu_SFR_Write(SCI_IEN_ERI, TRUE);
#endif
    
    Mcu_SFR_Write(SCI_REG.SCR.BYTE, 0x00);
    
    Mcu_SFR_Write(SCI_REG.SMR.BYTE, SCI_CFG_SMR);
    Sci_SetBaud(ui32t_baud);
    
#if (SCI_CFG_TXBUFSIZE != 0) && (SCI_CFG_RXBUFSIZE != 0)
    Mcu_SFR_Write(SCI_REG.SCR.BYTE, 0xF0);

#elif SCI_CFG_TXBUFSIZE != 0
    Mcu_SFR_Write(SCI_REG.SCR.BYTE, 0xB0);

#elif SCI_CFG_RXBUFSIZE != 0
    Mcu_SFR_Write(SCI_REG.SCR.BYTE, 0x70);

#else
    Mcu_SFR_Write(SCI_REG.SCR.BYTE, 0x30);

#endif
}


/**
 * @brief SciドライバをDeInitする
 */
void Sci_DeInit(void)
{
    uint8_t ui8t_ssr;
    
    /* 送信完了まで待つ */
    Sci_WaitForSendEnd();
    
    /* レジスタを初期化 */
    ui8t_ssr = Mcu_SFR_Read(SCI_REG.SSR.BYTE);
    Mcu_SFR_Write(SCI_REG.SCR.BYTE, 0x00);
    Mcu_SFR_Write(SCI_REG.SMR.BYTE, 0x00);
    Mcu_SFR_Write(SCI_REG.BRR, 0xFF);
    Mcu_SFR_Write(SCI_REG.SSR.BYTE, 0x84);
}


/**
 * @brief ボーレートを設定
 * @param ui32t_baud ボーレート
 */
void Sci_SetBaud(uint32_t ui32t_baud)
{
    uint16_t ui16t_brr;
    
    if (ui32t_baud < 9600)
    {
        ui32t_baud = 9600;
    }
    
    ui16t_brr = ((Mcu_Clk_Cfg_PCLKB_FREQ_KHZ * 1000) / ((64 / 2) * ui32t_baud)) - 1;
    Mcu_SFR_Write(SCI_REG.BRR, ui16t_brr);
}


/**
 * @brief 1Byteシリアル送信する
 * @param ui8t_sendData 送信データ
 */
void Sci_Send1B(uint8_t ui8t_sendData)
{
    /* 前回データ送信完了まで待機 */
    while (Mcu_SFR_Read(SCI_REG.SSR.BIT.TDRE) != TRUE) {}

    Mcu_SFR_Write(SCI_REG.TDR, ui8t_sendData);
}


/**
 * @brief Sci送信完了まで待つ
 */
void Sci_WaitForSendEnd(void)
{
    /* 前回データ送信完了まで待機 */
    while (Mcu_SFR_Read(SCI_REG.SSR.BIT.TEND) != TRUE) {}
}


/**
 * @brief 1Byteシリアル受信する
 * @return 受信データ
 */
uint8_t Sci_Recv1B(void)
{
    uint8_t ui8t_ssr;
    uint8_t ui8t_recvData;
    boolean bot_isRecv;
    
    
    bot_isRecv = FALSE;
    
    /* 受信完了までループ */
    do {
        /* 受信完了の場合 */
        if (Mcu_SFR_Read(SCI_REG.SSR.BIT.RDRF) == TRUE) {
            /* 受信完了の場合 */
            /* 受信データ取得 */
            ui8t_recvData = Mcu_SFR_Read(SCI_REG.RDR);
            
            bot_isRecv = TRUE;
        }

        /* 受信エラービットをクリア */
        ui8t_ssr = Mcu_SFR_Read(SCI_REG.SSR.BYTE);
        Sci_ErrorCode = ui8t_ssr & 0x38;
        Mcu_SFR_Write(SCI_REG.SSR.BYTE, ui8t_ssr & (~0x38));
    } while (bot_isRecv == FALSE);
    
    return (ui8t_recvData);
}


/**
 * @brief 1Byteシリアル受信する(非同期)
 * @param ui8t_recvData 受信バッファへのポインタ
 * @return 受信状態(TRUE=受信完了, FALSE=受信未完了)
 */
boolean Sci_Recv1BAsync(uint8_t *ui8t_recvData)
{
    uint8_t ui8t_ssr;
    boolean bot_isRecv;
    
    /* Using FIFO */
#if SCI_CFG_RXBUFSIZE != 0
    bot_isRecv = Fifo1B_Read(&Sci_RxFifo, ui8t_recvData);

#else
    bot_isRecv = FALSE;
    
    /* 受信完了の場合 */
    if (Mcu_SFR_Read(SCI_REG.SSR.BIT.RDRF) == TRUE) {
        /* 受信完了の場合 */
        /* 受信データ取得 */
        *ui8t_recvData = Mcu_SFR_Read(SCI_REG.RDR);
        
        bot_isRecv = TRUE;
    }

    /* 受信エラービットをクリア */
    ui8t_ssr = Mcu_SFR_Read(SCI_REG.SSR.BYTE);
    Sci_ErrorCode = ui8t_ssr & 0x38;
    Mcu_SFR_Write(SCI_REG.SSR.BYTE, ui8t_ssr & (~0x38));
#endif
    
    return (bot_isRecv);
}


/**
 * @brief 受信バイト数を取得する
 * @return 受信バッファに格納されているバイト数
 */
uint16_t Sci_GetRecvBytes(void)
{
    return (Fifo1B_GetUsed(&Sci_RxFifo));
}


/**
 * @brief 送信バッファの空きを取得する
 * @return 送信バッファの残り空きバイト数
 */
uint16_t Sci_GetSendBufferRemain(void)
{
    return (Fifo1B_GetRemain(&Sci_TxFifo));
}


/**
 * @brief 1Byteシリアル送信する(非同期)
 * @param ui8t_sendData 送信データ
 * @return 送信状態(TRUE=送信成功, FALSE=送信未完了)
 */
boolean Sci_Send1BAsync(uint8_t ui8t_sendData)
{
    boolean bot_isSend;


    /* Using FIFO */
#if SCI_CFG_TXBUFSIZE != 0
    bot_isSend = Fifo1B_Write(&Sci_TxFifo, &ui8t_sendData);
    /* First Tx? */
    if (Sci_IsTxIng == FALSE)
    {
        Sci_IsTxIng = TRUE;
        bot_isSend = Fifo1B_Read(&Sci_TxFifo, &ui8t_sendData);
        Mcu_SFR_Write(SCI_REG.TDR, ui8t_sendData);
    }

#else
    bot_isSend = FALSE;

    /* 送信バッファエンプティの場合 */
    if (Mcu_SFR_Read(SCI_REG.SSR.BIT.TDRE) == TRUE) {
        /* 送信バッファエンプティの場合 */
        /* 送信データ設定 */
        Mcu_SFR_Write(SCI_REG.TDR, ui8t_sendData);
        
        bot_isSend = TRUE;
    }
#endif

    return (bot_isSend);
}


/**
 * @brief 受信完了割り込み
 * @note 本関数は割り込みで呼び出しされる
 */
void __attribute__((interrupt)) Sci_RXIHandler(void)
{
    uint8_t ui8t_recvData;
    
    /* 受信完了の場合 */
    ui8t_recvData = Mcu_SFR_Read(SCI_REG.RDR);
    Fifo1B_Write(&Sci_RxFifo, &ui8t_recvData);
}


/**
 * @brief 受信エラー割り込み
 * @note 本関数は割り込みで呼び出しされる
 */
void Sci_ERIHandler(void)
{
    uint8_t ui8t_ssr;
    uint8_t ui8t_recvData;
    
    /* 受信完了の場合 */
    if (Mcu_SFR_Read(SCI_REG.SSR.BIT.RDRF) == TRUE) {
        /* 受信完了の場合 */
        /* ダミーリード */
        ui8t_recvData = Mcu_SFR_Read(SCI_REG.RDR);
    }
    
    /* 受信エラービットをクリア */
    ui8t_ssr = Mcu_SFR_Read(SCI_REG.SSR.BYTE);
    Sci_ErrorCode = ui8t_ssr & 0x38;
    Mcu_SFR_Write(SCI_REG.SSR.BYTE, ui8t_ssr & (~0x38));
}


/**
 * @brief 送信完了割り込み
 * @note 本関数は割り込みで呼び出しされる
 */
void __attribute__((interrupt)) Sci_TXIHandler(void)
{
    uint8_t ui8t_sendData;
    boolean bot_isSend;
    
    bot_isSend = Fifo1B_Read(&Sci_TxFifo, &ui8t_sendData);
    /* TxData Exists? */
    if (bot_isSend == TRUE)
    {
        Mcu_SFR_Write(SCI_REG.TDR, ui8t_sendData);
    }
    else
    {
        Sci_IsTxIng = FALSE;
    }
}
