/**
 * @file Sci_Cfg.h
 * @brief Sci通信機能を提供する
 * @author KSEII T.Terazawa
 * @copyright 2020 Kernel Software Engineering
 */

#ifndef __Sci_Cfg_H
#define __Sci_Cfg_H


#ifdef __cplusplus
extern "C" {
#endif


#define __SCI_CH (1)                /**< SCIチャンネル設定 */


/** SCIチャンネル番号定義
 */
#if __SCI_CH == 0
    #define SCI_REG         SCI0
    #define SCI_MSTP        MSTP(SCI0)
    #define SCI_IPR_RXI     IPR(SCI0, RXI0)
    #define SCI_IPR_TXI     IPR(SCI0, TXI0)
    #define SCI_IEN_RXI     IEN(SCI0, RXI0)
    #define SCI_IEN_TXI     IEN(SCI0, TXI0)
    #define SCI_IEN_ERI     EN(SCI0, ERI0)
#elif __SCI_CH == 1
    #define SCI_REG         SCI1
    #define SCI_MSTP        MSTP(SCI1)
    #define SCI_IPR_RXI     IPR(SCI1, RXI1)
    #define SCI_IPR_TXI     IPR(SCI1, TXI1)
    #define SCI_IEN_RXI     IEN(SCI1, RXI1)
    #define SCI_IEN_TXI     IEN(SCI1, TXI1)
    #define SCI_IEN_ERI     EN(SCI1, ERI1)
#else
    #error "Incompatible __SCI_CH"
#endif


/**
 * 定数定義
 */
#define SCI_SYNCMODE_SSYNC (0)
#define SCI_SYNCMODE_CLOCK (1)
#define SCI_CHLEN_8 (0)
#define SCI_CHLEN_7 (1)
#define SCI_PE_DISABLE (0)
#define SCI_PE_ENABLE  (1)
#define SCI_PARITY_EVEN (0)
#define SCI_PARITY_ODD  (1)
#define SCI_STOPBIT_1 (0)
#define SCI_STOPBIT_2 (1)


/** 同期方法
 *  SCI_SYNCMODE_SSYNC: 調歩同期 (UART)
 *  SCI_SYNCMODE_CLOCK: クロック同期 (SPI)
 */
#define SCI_SYNCMODE (SCI_SYNCMODE_SSYNC)


/** キャラクタレングス
 *  SCI_CHLEN_8: 8bit
 *  SCI_CHLEN_7: 7bit
 *  ※クロック同期の場合常に8bitとなる
 */
#define SCI_CHLEN (SCI_CHLEN_8)


/** パリティ有無
 *  SCI_PE_DISABLE: 無効
 *  SCI_PE_ENABLE : 有効
 */
#define SCI_PE (SCI_PE_DISABLE)


/** パリティモード
 *  SCI_PARITY_ODD : 奇数パリティ
 *  SCI_PARITY_EVEN: 偶数パリティ
 *  ※パリティ無効の場合無効
 */
#define SCI_PARITY (SCI_PARITY_ODD)


/** ストップビットレングス
 *  SCI_STOPBIT_1: 1bit
 *  SCI_STOPBIT_2: 2bit
 *  ※クロック同期式の場合無効
 */
#define SCI_STOPBIT (SCI_STOPBIT_1)


/** クロックセレクト設定
 *  ※マイコンマニュアル参照
 */
#define SCI_CKS (0)


#define SCI_CFG_SMR ((SCI_SYNCMODE << 7) | (SCI_CHLEN << 6) | (SCI_PE << 5) | (SCI_PARITY << 4) | (SCI_STOPBIT << 3) | SCI_CKS)

/* FIFO Size 2^nで指定 */
#define SCI_CFG_TXBUFSIZE   (256)
/* FIFO Size 2^nで指定 */
#define SCI_CFG_RXBUFSIZE   (256)


#ifdef __cplusplus
}
#endif


#endif
