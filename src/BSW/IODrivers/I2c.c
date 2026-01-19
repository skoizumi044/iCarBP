/**
 * @file I2c.c
 * @brief I2C通信機能を提供する
 */

#include <Std_Types.h>
#include <SystemServices/Mcu.h>

#include "I2c.h"


#define RIIC_CH     RIIC0
#define RIIC_MSTP   MSTP(RIIC0)


/* 通信速度設定 */
/* PCLKB@60MHz 400kbps */
#define CKS_VALUE   (2u)
#define ICBRH_VALUE (0xE8u)
#define ICBRL_VALUE (0xF3u)

/* 通信設定 */
#define IMCR2_VALUE (0x07u)
#define IMCR3_VALUE (0x00u)

#define ICFER_VALUE (0x73u)
#define ICIER_VALUE (0x00u)

/* スレーブアドレス設定 */
#define ICSER_VALUE (0x00u)

#define SARU0_VALUE (0x00u)
#define SARL0_VALUE (0x00u)

#define SARU1_VALUE (0x00u)
#define SARL1_VALUE (0x00u)

#define SARU2_VALUE (0x00u)
#define SARL2_VALUE (0x00u)

#define I2c_BusWaitTime (240)


#define ICSR2_CLR_MASK  (0x80)


static void I2c_Wait20us(void);


/**
 * @brief I2cドライバを初期化する
 */
void I2c_Init(uint8_t ui8t_ch)
{
    /* レジスタプロテクト解除 */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY | Mcu_PRCR_PRC1));
    
    /* モジュールスタンバイ解除 */
    Mcu_SFR_Write(RIIC_MSTP, FALSE);
    
    /* レジスタプロテクト */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY));
    
    /* I2Cリソース停止 */
    Mcu_SFR_Write(RIIC_CH.ICCR1.BIT.ICE, FALSE);
    
    /* RIICリセット */
    Mcu_SFR_Write(RIIC_CH.ICCR1.BIT.IICRST, TRUE);
    
    /* 端子有効化 */
    Mcu_SFR_Write(RIIC_CH.ICCR1.BIT.ICE, TRUE);
    
    /* スレーブアドレス設定 */
    Mcu_SFR_WriteVerify(RIIC_CH.ICSER.BYTE, ICSER_VALUE);
    
    Mcu_SFR_Write(RIIC_CH.SARU0.BYTE, SARU0_VALUE);
    Mcu_SFR_Write(RIIC_CH.SARL0.BYTE, SARL0_VALUE);
    Mcu_SFR_Write(RIIC_CH.SARU1.BYTE, SARU1_VALUE);
    Mcu_SFR_Write(RIIC_CH.SARL1.BYTE, SARL1_VALUE);
    Mcu_SFR_Write(RIIC_CH.SARU2.BYTE, SARU2_VALUE);
    Mcu_SFR_Write(RIIC_CH.SARL2.BYTE, SARL2_VALUE);
    
    /* 通信速度設定 */
    Mcu_SFR_Write(RIIC_CH.ICMR1.BIT.CKS, CKS_VALUE);
    Mcu_SFR_Write(RIIC_CH.ICBRH.BYTE, ICBRH_VALUE);
    Mcu_SFR_Write(RIIC_CH.ICBRL.BYTE, ICBRL_VALUE);
    
    /* 通信設定 */
    Mcu_SFR_Write(RIIC_CH.ICMR2.BYTE, IMCR2_VALUE);
    Mcu_SFR_Write(RIIC_CH.ICMR3.BYTE, IMCR3_VALUE);
    
    Mcu_SFR_Write(RIIC_CH.ICFER.BYTE, ICFER_VALUE);
    
    /* 割り込み設定 */
    Mcu_SFR_Write(RIIC_CH.ICIER.BYTE, ICIER_VALUE);
    
    
    /* RIICリセット */
    Mcu_SFR_Write(RIIC_CH.ICCR1.BIT.IICRST, FALSE);
}


/**
 * @brief バスがBusyかを返す
 * @param ui8t_ch 使用するI2Cチャンネル
 * @ret TRUE=Busy, FALSE=Busyでない
 */
boolean I2c_BusIsBusy(uint8_t ui8t_ch)
{
    return (Mcu_SFR_Read(RIIC_CH.ICCR2.BIT.BBSY));
}


/**
 * @brief ドライバ用の20us待機
 * @note ICLK=120MHz想定
 */
static void I2c_Wait20us(void)
{
    /* 最適化による処理時間のブレを少なくす為 */
    /* ループカウンタを意図的に32bit signedレジスタ変数に割り付け */
    register int32_t si32t_cnt;
    
    /* @120MHz 2400 NOP */
    /* 3240 = 8NOPs + 2LOOP Instractions (DEC, JMP) */
    si32t_cnt = I2c_BusWaitTime;
    while (si32t_cnt-- > IDX_0) {
#if Mcu_Clk_Cfg_ILCK_FREQ_KHZ == (120000)
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
#else
#error "I2c_Wait20us() Invalid Mcu_Clk_Cfg_ILCK_FREQ_KHZ. Please configure."
#endif
    }
}


/**
 * @brief スタートビットの送信
 * @param ui8t_ch 使用するI2Cチャンネル
 */
boolean I2c_SendStart(uint8_t ui8t_ch)
{
    uint8_t ui8t_cnt;
    
    /* 最大100usBusy待ち */
    for (ui8t_cnt = IDX_0; ui8t_cnt < IDX_5; ui8t_cnt++) {
        /* バスがBusyかチェック */
        if (I2c_BusIsBusy(ui8t_ch) == FALSE) {
            break;
        }
        
        I2c_Wait20us();
    }
    /* バスがBusyかチェック */
    if (I2c_BusIsBusy(ui8t_ch) == TRUE) {
        return (FALSE);
    }
    
    /* Clear Flags */
    Mcu_SFR_Write(RIIC_CH.ICSR2.BYTE, (Mcu_SFR_Read(RIIC_CH.ICSR2.BYTE) & ICSR2_CLR_MASK));
    
    /* スタートビットを送信 */
    Mcu_SFR_Write(RIIC_CH.ICCR2.BIT.ST, TRUE);
    
    return (TRUE);
}


/**
 * @brief ストップビットの送信
 * @param ui8t_ch 使用するI2Cチャンネル
 */
boolean I2c_SendStop(uint8_t ui8t_ch)
{
    boolean bRet;

    /* 戻り値を設定 */
    bRet = TRUE;

    /* ストップコンディション検出フラグをクリア */
    Mcu_SFR_Write(RIIC_CH.ICSR2.BIT.STOP, FALSE);
    
    /* ストップビットを送信 */
    Mcu_SFR_Write(RIIC_CH.ICCR2.BIT.SP, TRUE);
    
    /* 通信完了待ち */
    Mcu_SFR_Write(RIIC_CH.ICSR2.BIT.TMOF, FALSE);
    while (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.STOP) == FALSE) {
        /* タイムアウト検知 */
        if (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.TMOF) == TRUE) {
            bRet = FALSE;
            break;
        }
    }
    
    /* Nackフラグクリア */
    Mcu_SFR_Write(RIIC_CH.ICSR2.BIT.NACKF, FALSE);

    /* ストップコンディション検出フラグをクリア */
    Mcu_SFR_Write(RIIC_CH.ICSR2.BIT.STOP, FALSE);
    
    return (bRet);
}


/**
 * @brief Ackの送信
 * @param ui8t_ch 使用するI2Cチャンネル
 */
void I2c_SendAck(uint8_t ui8t_ch)
{
    Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.ACKWP, TRUE);
    Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.ACKBT, FALSE);
    Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.ACKWP, FALSE);
}

/**
 * @brief Nackの送信
 * @param ui8t_ch 使用するI2Cチャンネル
 */
void I2c_SendNAck(uint8_t ui8t_ch)
{
    Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.ACKWP, TRUE);
    Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.ACKBT, TRUE);
    Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.ACKWP, FALSE);
}


/**
 * @brief Ackの受信
 * @param ui8t_ch 使用するI2Cチャンネル
 */
boolean I2c_RecvAck(uint8_t ui8t_ch)
{
    boolean bt_ret;
    
    bt_ret = TRUE;
    if (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.NACKF) == TRUE) {
        bt_ret = FALSE;
    }
    
    return (bt_ret);
}


/**
 * @brief I2cから受信待ちする
 * @param ui8t_ch 使用するI2Cチャンネル
 */
boolean I2c_WaitForRxComp(uint8_t ui8t_ch)
{
    while (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.RDRF) == FALSE) {
        /* タイムアウト検知 */
        if (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.TMOF) == TRUE) {
            return (FALSE);
        }
    }
    
    return (TRUE);
}


/**
 * @brief I2cに書き込み (RAW)
 * @param ui8t_ch 使用するI2Cチャンネル
 * @param ui8tp_data 送信データを格納したバッファ
 * @param ui16t_size 送信データサイズ
 * @note 本関数は送信データをセット完了で送信完了となる。
 *       バスへの出力完了はI2c_WaitForWriteFinish()をコールすること
 * @note ui16t_sizeに0を指定した場合の動作は未定義
 */
boolean I2c_WriteRaw(uint8_t ui8t_ch, const uint8_t *ui8tp_data, uint16_t ui16t_size)
{
    uint16_t ui16t_idx;
    
    /* 指定バイト数送信する */
    for (ui16t_idx = IDX_0; ui16t_idx < ui16t_size; ui16t_idx++) {
        /* 送信可能となるまで待つ */
        do {
            /* Ackを確認 */
            if (I2c_RecvAck(ui8t_ch) == FALSE) {
                return (FALSE);
            }
            
            /* タイムアウト検知 */
            if (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.TMOF) == TRUE) {
                return (FALSE);
            }
        } while (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.TDRE) == FALSE);
        
        /* データを送信 */
        Mcu_SFR_Write(RIIC_CH.ICDRT, ui8tp_data[ui16t_idx]);
    }
    
    return (TRUE);
}


/**
 * @brief I2cから読み込み (RAW)
 * @param ui8t_ch 使用するI2Cチャンネル
 * @param ui8tp_data 受信データを格納するバッファ
 * @param ui16t_size 受信データサイズ
 * @note ui16t_sizeに0を指定した場合の動作は未定義
 */
boolean I2c_ReadRaw(uint8_t ui8t_ch, uint8_t *ui8tp_data, uint16_t ui16t_size)
{
    boolean bt_ret;
    uint16_t ui16t_cnt;
    uint8_t ui8t_dmybuf;
    
    
    bt_ret = TRUE;
    ui16t_cnt = IDX_0;

    /* 3バイト以上受信の場合残り2Byteまで受信 */
    if (ui16t_size >= IDX_3) {
        /* ダミーリード */
        ui8t_dmybuf = Mcu_SFR_Read(RIIC_CH.ICDRR);
        
        for (; ui16t_cnt < (ui16t_size - IDX_3); ui16t_cnt++) {
            /* データ受信待ち */
            I2c_WaitForRxComp(ui8t_ch);
            
            /* データを受信する */
            ui8tp_data[ui16t_cnt] = Mcu_SFR_Read(RIIC_CH.ICDRR);
        }

        /* データ受信待ち */
        I2c_WaitForRxComp(ui8t_ch);

        /* WAIT設定 */
        Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.WAIT, TRUE);

        /* データを受信する */
        ui8tp_data[ui16t_cnt] = Mcu_SFR_Read(RIIC_CH.ICDRR);
        ui16t_cnt++;
        
        /* データ受信待ち */
        I2c_WaitForRxComp(ui8t_ch);

    /* 2Byte受信の場合 */
    } else if (ui16t_size == IDX_2) {
        /* WAIT設定 */
        Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.WAIT, TRUE);

        /* ダミーリード */
        ui8t_dmybuf = Mcu_SFR_Read(RIIC_CH.ICDRR);

        /* データ受信待ち */
        I2c_WaitForRxComp(ui8t_ch);

    /* 1Byte受信の場合 */
    } else {
        /* WAIT設定 */
        Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.WAIT, TRUE);
    }
    

    /* NACKを設定 */
    I2c_SendNAck(ui8t_ch);

    /* データn-1を受信 */
    if (ui16t_size >= IDX_2) {
        /* データNを受信する */
        ui8tp_data[ui16t_cnt] = Mcu_SFR_Read(RIIC_CH.ICDRR);
        ui16t_cnt++;
        
    } else {
        /* ダミーリード */
        ui8t_dmybuf = Mcu_SFR_Read(RIIC_CH.ICDRR);
    }
    
    
    /* データ受信待ち */
    I2c_WaitForRxComp(ui8t_ch);
    
    /* STOPビットを予約 */
    /* ストップコンディション検出フラグをクリア */
    Mcu_SFR_Write(RIIC_CH.ICSR2.BIT.STOP, FALSE);
    
    /* ストップビットを送信 */
    Mcu_SFR_Write(RIIC_CH.ICCR2.BIT.SP, TRUE);
    
    /* データnを受信する */
    ui8tp_data[ui16t_cnt] = Mcu_SFR_Read(RIIC_CH.ICDRR);
    
    Mcu_SFR_Write(RIIC_CH.ICMR3.BIT.WAIT, FALSE);
    
    /* 通信完了待ち */
    while (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.STOP) == FALSE) {
        /* タイムアウト検知 */
        if (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.TMOF) == TRUE) {
            bt_ret = FALSE;
            break;
        }
    }
    
    /* Nackフラグクリア */
    Mcu_SFR_Write(RIIC_CH.ICSR2.BIT.NACKF, FALSE);
    
    /* ストップコンディション検出フラグをクリア */
    Mcu_SFR_Write(RIIC_CH.ICSR2.BIT.STOP, FALSE);

    return (bt_ret);
}


/**
 * @brief I2cバス出力完了
 * @param ui8t_ch 使用するI2Cチャンネル
 * @return 出力完了=TRUE
 */
boolean I2c_WriteIsFinish(uint8_t ui8t_ch, boolean *btp_success)
{
    /* NACK検知 */
    if (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.NACKF) == TRUE) {
        *btp_success = FALSE;
        return (TRUE);
    }

    /* タイムアウト検知 */
    if (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.TMOF) == TRUE) {
        *btp_success = FALSE;
        return (TRUE);
    }
    
    return (Mcu_SFR_Read(RIIC_CH.ICSR2.BIT.TEND));
}


/**
 * @brief I2cから読み出し
 * @param ui8t_ch 使用するI2Cチャンネル
 * @param ui8t_addr 8bitデバイスアドレス
 * @param ui8tp_data 受信データを格納するバッファ
 * @param ui16t_size 受信データサイズ
 * @note ui16t_sizeは0指定不可
 */
boolean I2c_Read(uint8_t ui8t_ch, uint8_t ui8t_addr, uint8_t *ui8tp_data, uint16_t ui16t_size)
{
    boolean bt_ret;
    uint8_t ui8t_dmybuf;
    
    /* 戻り値 = 成功 */
    bt_ret = TRUE;
    
    /* 0Byte読み出しは不可 */
    if (ui16t_size == IDX_0) {
        return (FALSE);
    }
    
    /* スタートビット送信 */
    if (I2c_SendStart(ui8t_ch) == FALSE) {
        return (FALSE);
    }
    
    /* アドレスを送信する */
    /* アドレスにRビットを設定 */
    ui8t_addr = (ui8t_addr << IDX_1) | IDX_1;
    if (I2c_WriteRaw(ui8t_ch, &ui8t_addr, sizeof(ui8t_addr)) == TRUE) {
        /* アドレス送信完了を待つ */
        I2c_WaitForRxComp(ui8t_ch);
        
        /* Ackを確認 */
        if (I2c_RecvAck(ui8t_ch) == TRUE) {
            /* データを受信 */
            bt_ret = I2c_ReadRaw(ui8t_ch, ui8tp_data, ui16t_size);
            
        /* Nackの場合 */
        } else {
            bt_ret = FALSE;
            
            /* ストップビット送信 */
            I2c_SendStop(ui8t_ch);
            
            /* ダミーリード */
            ui8t_dmybuf = Mcu_SFR_Read(RIIC_CH.ICDRR);
        }
    
    /* Writeに失敗 */
    } else {
        bt_ret = FALSE;
        
        /* ストップビット送信 */
        I2c_SendStop(ui8t_ch);
    }
    
    return (bt_ret);
}


/**
 * @brief I2cに書き込み
 * @param ui8t_ch 使用するI2Cチャンネル
 * @param ui8t_addr 8bitデバイスアドレス
 * @param ui8tp_data 送信データを格納したバッファ
 * @param ui16t_size 送信データサイズ
 * @note ui16t_sizeは0指定不可
 */
boolean I2c_Write(uint8_t ui8t_ch, uint8_t ui8t_addr, const uint8_t *ui8tp_data, uint16_t ui16t_size)
{
    boolean bt_ret;
    
    /* 0Byte書き込みは不可 */
    if (ui16t_size == IDX_0) {
        return (FALSE);
    }
    
    /* スタートビット送信 */
    if (I2c_SendStart(ui8t_ch) == FALSE) {
        return (FALSE);
    }
    
    bt_ret = FALSE;
    
    /* アドレスを送信する */
    ui8t_addr = ui8t_addr << IDX_1;
    if (I2c_WriteRaw(ui8t_ch, &ui8t_addr, sizeof(ui8t_addr)) == TRUE) {
        /* データを送信する */
        if (I2c_WriteRaw(ui8t_ch, ui8tp_data, ui16t_size) == TRUE) {
            bt_ret = TRUE;
            
            /* 送信完了するまで待つ */
            while (I2c_WriteIsFinish(ui8t_ch, &bt_ret) == FALSE) {}
        }
    }
    
    /* ストップビット送信 */
    if (I2c_SendStop(ui8t_ch) == FALSE) {
        return (FALSE);
    }
    
    return (bt_ret);
}
