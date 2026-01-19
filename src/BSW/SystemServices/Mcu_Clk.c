/**
 * @file Mcu_Clk.c
 * @brief MCUクロックの初期化を行う
 * @author KSEII T.Terazawa
 * @copyright 2020 Kernel Software Engineering
 */

#include "Mcu.h"
#include "Mcu_Clk.h"


/**
 * @brief クロックを初期化する
 */
void Mcu_Clk_Init(void)
{
    /* レジスタプロテクト解除 */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY | Mcu_PRCR_PRC1 | Mcu_PRCR_PRC0));

    /*--------------------------------------------*/
    /* メインクロック開始処理                     */
    /*--------------------------------------------*/
#if Mcu_Clk_Cfg_MAINOSC_ENABLE == TRUE
    /* メインクロックドライブ能力切替 */
    Mcu_SFR_Write(SYSTEM.MOFCR.BYTE, Mcu_Clk_Cfg_MOFCR_VALUE);
    
    /* メインクロック発振安定待ち時間を設定 */
    Mcu_SFR_Write(SYSTEM.MOSCWTCR.BYTE, Mcu_Clk_Cfg_MOSCWTCR_VALUE);
    
    /* メインクロック動作開始 */
    Mcu_SFR_WriteVerify(SYSTEM.MOSCCR.BYTE, FALSE);
    
    /* メインクロック発振安定待ち */
    while (Mcu_SFR_Read(SYSTEM.OSCOVFSR.BIT.MOOVF) != TRUE) {}
#endif
    
    /*--------------------------------------------*/
    /* サブクロック開始処理                       */
    /*--------------------------------------------*/
#if Mcu_Clk_Cfg_SUBOSC_ENABLE == TRUE
    /* サブクロック発振安定待ち時間を設定 */
    Mcu_SFR_Write(SYSTEM.SOSCWTCR.BYTE, Mcu_Clk_Cfg_SOSCWTCR_VALUE);
    
    /* サブクロック動作開始 */
    Mcu_SFR_WriteVerify(SYSTEM.SOSCCR.BYTE, FALSE);
    
    /* サブクロック発振安定待ち */
    while (Mcu_SFR_Read(SYSTEM.OSCOVFSR.BIT.SOOVF) != TRUE) {}
#endif
    
    /*--------------------------------------------*/
    /* HOCO開始処理                               */
    /*--------------------------------------------*/
#if Mcu_Clk_Cfg_HOCO_ENABLE == TRUE
    /* ↓Sleep→Wakeup時に必要 */
    /* HOCOの電源ON */
    /*Mcu_SFR_WriteVerify(SYSTEM.HOCOPCR.BYTE, FALSE);*/
    /* 電源投入待ちのために150us以上 Wait */
    /*Mcu_Clk_Wait150us_LOCO();*/
    
    /* HOCO開始 */
    Mcu_SFR_Write(SYSTEM.HOCOCR2.BYTE, Mcu_Clk_Cfg_HOCOCR2_VALUE);
    Mcu_SFR_WriteVerify(SYSTEM.HOCOCR.BYTE, FALSE);

    /* HOCO発振安定待ち */
    while (Mcu_SFR_Read(SYSTEM.OSCOVFSR.BIT.HCOVF) != TRUE) {}
#endif
    
    /*--------------------------------------------*/
    /* PLL開始処理                                */
    /*--------------------------------------------*/
#if Mcu_Clk_Cfg_PLL_ENABLE == TRUE
    /* 逓倍設定 */
    Mcu_SFR_Write(SYSTEM.PLLCR.WORD, Mcu_Clk_Cfg_PLLCR_VALUE);
    
    /* PLL開始 */
    Mcu_SFR_WriteVerify(SYSTEM.PLLCR2.BYTE, FALSE);
    
    /* PLL発振安定待ち */
    while (Mcu_SFR_Read(SYSTEM.OSCOVFSR.BIT.PLOVF) != TRUE) {}
#endif

    /* BCLK端子出力選択 */
    Mcu_SFR_WriteVerify(SYSTEM.BCKCR.BYTE, Mcu_Clk_Cfg_BCKCR_VALUE);
    
    /* ROM WaitTimeを設定 */
    Mcu_SFR_WriteVerify(SYSTEM.ROMWT.BYTE, Mcu_Clk_Cfg_ROMWT_VALUE);
    
    /* システムクロック選択 */
    Mcu_SFR_WriteVerify(SYSTEM.SCKCR.LONG, Mcu_Clk_Cfg_SCKCR_VALUE);
    Mcu_SFR_WriteVerify(SYSTEM.SCKCR2.WORD, Mcu_Clk_Cfg_SCKCR2_VALUE);
    Mcu_SFR_WriteVerify(SYSTEM.SCKCR3.WORD, Mcu_Clk_Cfg_SCKCR3_VALUE);
    
    /* レジスタプロテクト */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY));
}


/**
 * @brief LOCOクロック動作で150us待機
 * 動作前提：動作中のクロックがLOCOであること
 */
void Mcu_Clk_Wait150us_LOCO(void)
{
    /* fLOCO max=264kHz 3.7878=39.6CLKのため、NOP40 */
    /* 関数オーバーヘッド分はマージンとして確保 */
    Mcu_NOP_10();
    Mcu_NOP_10();
    Mcu_NOP_10();
    Mcu_NOP_10();
}
