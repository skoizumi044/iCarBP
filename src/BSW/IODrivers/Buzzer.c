/**
 * @file Buzzer.c
 * @brief ブザードライバ
 */

#include <Std_Types.h>
#include <SystemServices/Mcu.h>


#include "Buzzer.h"


/* 使用リソースの設定 */
#define TPU_CH              1
#define TPU_REG             TPU1
#define TPU_MSTP            MSTP(TPU1)

#define TPU_INT_SLIAR_VALUE (21)
#define TPU_INT_SLIAR       ICU.SLIBXR128.BYTE
#define TPU_INT_IPR         IPR(PERIB, INTB128)
#define TPU_INT_IEN         IEN(PERIB, INTB128)
#define TPU_INT_IR          IR(PERIB, INTB128)

#define FREQ_MIN            (8)             /**< 設定可能最小周波数 */
#define FREQ_MAX            (16000)         /**< 設定可能最大周波数 */


uint32_t Buzzer_IsPlay = FALSE;
uint32_t Buzzer_Cycle;
uint16_t Buzzer_TGR;


/**
 * @brief 初期化
 */
void Buzzer_Init(void)
{
    /* レジスタプロテクト解除 */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY | Mcu_PRCR_PRC1));

    /* モジュールスタンバイ解除 */
    Mcu_SFR_Write(TPU_MSTP, FALSE);

    /* レジスタプロテクト */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY));

    /* タイマ停止 */
    Mcu_SFR_WriteBit(&TPUA.TSTR.BYTE, TPU_CH, 0);

    /* TPU初期設定 */
    Mcu_SFR_Write(TPU_REG.TCR.BYTE, 0x43u);
    Mcu_SFR_Write(TPU_REG.TMDR.BYTE, 0x00u);

#if (TPU_CH == 0) || (TPU_CH == 3)
    Mcu_SFR_Write(TPU_REG.TIORH.BYTE, 0x30u);
    Mcu_SFR_Write(TPU_REG.TIORL.BYTE, 0x00u);
#else
    Mcu_SFR_Write(TPU_REG.TIOR.BYTE, 0x30u);
#endif

    Mcu_SFR_Write(TPU_REG.TIER.BYTE, 0x02u);
    Mcu_SFR_Write(TPU_REG.NFCR.BYTE, 0x00u);

    /* TSRダミーリード・クリア */
    Mcu_SFR_Read(TPU_REG.TSR.BYTE);
    Mcu_SFR_Write(TPU_REG.TSR.BYTE, 0x00);

    /* カウンタ初期化 */
    Mcu_SFR_Write(TPU_REG.TCNT, 0);
    Mcu_SFR_Write(TPU_REG.TGRA, 0);
    Mcu_SFR_Write(TPU_REG.TGRB, 0);

#if (TPU_CH == 0) || (TPU_CH == 3)
    Mcu_SFR_Write(TPU_REG.TGRC, 0);
    Mcu_SFR_Write(TPU_REG.TGRD, 0);
#endif

    /* 割り込み設定 */
    Mcu_SFR_Write(TPU_INT_SLIAR, TPU_INT_SLIAR_VALUE);
    Mcu_SFR_Write(TPU_INT_IPR, 9);
    Mcu_SFR_Write(TPU_INT_IR, FALSE);
    Mcu_SFR_Write(TPU_INT_IEN, TRUE);
    Buzzer_TGR = 0;
    Buzzer_Cycle = 0;
}


/**
 * @brief ブザー出力を開始する
 * @param ui32t_freq 周波数[Hz]
 * @param ui32t_timems 吹鳴時間[ms]
 * @note 周波数に0または設定可能範囲外を設定した場合停止する
 */
void Buzzer_Start(uint32_t ui32t_freq, uint32_t ui32t_timems)
{
    uint32_t ui32t_cycle;
    
    /* 範囲外または周波数0Hzを設定した場合停止する */
    if (ui32t_freq == VAL_0 || ui32t_freq < FREQ_MIN || FREQ_MAX < ui32t_freq) {
        Buzzer_Stop();
        return;
    }
    
    
    /* サイクル設定 */
    if (ui32t_timems != 0)
    {
        ui32t_cycle = (ui32t_freq * 2 * ui32t_timems) / 1000;
        if (ui32t_cycle <= 0)
        {
            ui32t_cycle = 1;
        }
    }
    else
    {
        ui32t_cycle = 0;
    }

    
    /* ブザー割り込み禁止 */
    Mcu_SFR_Write(TPU_INT_IEN, FALSE);
    
    /* タイマ設定 */
    /* (PCLKB /ui32t_freq * 2) の四捨五入 - 1 */
    Buzzer_TGR = (((Mcu_Clk_Cfg_PCLKB_FREQ_KHZ * 1000 / 64) + ((ui32t_freq * 2) / 2)) / (ui32t_freq * 2)) - 1;

    
    Buzzer_Cycle = ui32t_cycle;
    
    /* 停止中の場合 */
    if (Buzzer_IsPlay == FALSE)
    {
        /* TGRレジスタ書き込み */
        Mcu_SFR_Write(TPU_REG.TGRB, Buzzer_TGR);

        /* タイマ開始 */
        Mcu_SFR_WriteBit(&TPUA.TSTR.BYTE, TPU_CH, 1);
    }
    /* 再生中の場合 */
    else
    {
        /* TGRレジスタには割込みで書き込み */
    }

    Buzzer_IsPlay = TRUE;
    
    /* ブザー割り込み許可 */
    Mcu_SFR_Write(TPU_INT_IEN, TRUE);
}


/**
 * @brief ブザー出力を停止する
 */
void Buzzer_Stop(void)
{
    /* ブザー割り込み禁止 */
    Mcu_SFR_Write(TPU_INT_IEN, FALSE);
    
    Buzzer_IsPlay = FALSE;

    /* タイマ停止 */
    Mcu_SFR_WriteBit(&TPUA.TSTR.BYTE, TPU_CH, 0);

    /* 出力レベル初期化 */
#if (TPU_CH == 0) || (TPU_CH == 3)
    Mcu_SFR_Write(TPU_REG.TIORH.BYTE, 0x30u);
    Mcu_SFR_Write(TPU_REG.TIORL.BYTE, 0x00u);
#else
    Mcu_SFR_Write(TPU_REG.TIOR.BYTE, 0x30u);
#endif

    /* ブザー割り込み許可 */
    Mcu_SFR_Write(TPU_INT_IEN, TRUE);
}


/**
 * @brief TPU1 TGRB割り込み
 */
void __attribute__((interrupt)) Buzzer_TPU_INT(void)
{
    /* 要因クリア */
    Mcu_SFR_Write(TPU_INT_IR, FALSE);

    /* Update Duty */
    Mcu_SFR_Write(TPU_REG.TGRB, Buzzer_TGR);
    
    /* Cycle Set? */
    if (Buzzer_Cycle > 0)
    {
        /* Dec Cycle */
        Buzzer_Cycle--;
        
        /* Completed ? */
        if (Buzzer_Cycle <= 0)
        {
            /* Stop Buzzer */
            Buzzer_Stop();
        }
    }
}
