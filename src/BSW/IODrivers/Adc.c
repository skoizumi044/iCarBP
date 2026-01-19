/**
 * @file Adc.c
 * @brief A/D変換機能を提供する
 */

#include <Std_Types.h>
#include <SystemServices/Mcu.h>

#define __Adc_C
#include "Adc.h"


/* AD逐次変換A/D 逐次変換時間設定プロテクトレジスタ設定値 */
#define Adc_ADSAMPR_DISENGAGE       (0x03u)
#define Adc_ADSAMPR_ENGAGE          (0x00u)

/* AD変換結果バッファ */
uint16_t Adc_AD0_Buf[Adc_AD0_NumCH];
uint16_t Adc_AD1_Buf[Adc_AD1_NumCH];

/**
 * @brief ADドライバを初期化する
 */
void Adc_Init(void)
{
    /* レジスタプロテクト解除 */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY | Mcu_PRCR_PRC1));
    
    /* モジュールスタンバイ解除 */
    Mcu_SFR_Write(MSTP(S12AD), FALSE);
    Mcu_SFR_Write(MSTP(S12AD1), FALSE);
    
    /* レジスタプロテクト */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY));
    
    /*---------------------------------------------------*/
    /* 初期化 (S12AD)                                    */
    /*---------------------------------------------------*/
    /* AD逐次変換時間設定 */
    /* プロテクト解除 */
    Mcu_SFR_Write(S12AD.ADSAMPR.BYTE, Adc_ADSAMPR_DISENGAGE);
    
    Mcu_SFR_Write(S12AD.ADSAM.WORD, Adc_AD0_ADSAM_VALUE);
    
    /* プロテクト */
    Mcu_SFR_Write(S12AD.ADSAMPR.BYTE, Adc_ADSAMPR_ENGAGE);
    
    
    Mcu_SFR_Write(S12AD.ADCSR.WORD, Adc_AD0_ADCSR_VALUE);
    Mcu_SFR_Write(S12AD.ADCER.WORD, Adc_AD0_ADCER_VALUE);
    Mcu_SFR_Write(S12AD.ADADC.BYTE, Adc_AD0_ADADC_VALUE);
    
    Mcu_SFR_Write(S12AD.ADSTRGR.WORD, Adc_AD0_ADSTRGR_VALUE);
    Mcu_SFR_Write(S12AD.ADGCTRGR.BYTE, Adc_AD0_ADGCTRGR_VALUE);
    
    Mcu_SFR_Write(S12AD.ADSHCR.WORD, Adc_AD0_ADSHCR_VALUE);
    Mcu_SFR_Write(S12AD.ADSHMSR.BYTE, Adc_AD0_ADSHMSR_VALUE);
    
    Mcu_SFR_Write(S12AD.ADDISCR.BYTE, Adc_AD0_ADDISCR_VALUE);
    Mcu_SFR_Write(S12AD.ADGSPCR.WORD, Adc_AD0_ADGSPCR_VALUE);
    Mcu_SFR_Write(S12AD.ADCMPCR.WORD, Adc_AD0_ADCMPCR_VALUE);
    
    /* A/D変換値加算 / 平均機能 */
    Mcu_SFR_Write(S12AD.ADADS0.WORD, Adc_AD0_ADADS0_VALUE);
    
    /* チャネル選択 */
    /* スキャングループA */
    Mcu_SFR_Write(S12AD.ADANSA0.WORD, Adc_AD0_ADANSA0_VALUE);
    
    /* スキャングループB */
    Mcu_SFR_Write(S12AD.ADANSB0.WORD, Adc_AD0_ADANSB0_VALUE);
    
    /* スキャングループC */
    Mcu_SFR_Write(S12AD.ADANSC0.WORD, Adc_AD0_ADANSC0_VALUE);
    
    /* サンプリングステート */
    Mcu_SFR_Write(S12AD.ADSSTR0, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD.ADSSTR1, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD.ADSSTR2, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD.ADSSTR3, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD.ADSSTR4, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD.ADSSTR5, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD.ADSSTR6, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD.ADSSTR7, Adc_ADSSTR_VALUE);
    
    
    /*---------------------------------------------------*/
    /* 初期化 (S12AD1)                                   */
    /*---------------------------------------------------*/
    /* AD逐次変換時間設定 */
    /* プロテクト解除 */
    Mcu_SFR_Write(S12AD1.ADSAMPR.BYTE, Adc_ADSAMPR_DISENGAGE);
    
    Mcu_SFR_Write(S12AD1.ADSAM.WORD, Adc_AD1_ADSAM_VALUE);
    
    /* プロテクト */
    Mcu_SFR_Write(S12AD1.ADSAMPR.BYTE, Adc_ADSAMPR_ENGAGE);
    
    Mcu_SFR_Write(S12AD1.ADCSR.WORD, Adc_AD1_ADCSR_VALUE);
    Mcu_SFR_Write(S12AD1.ADCER.WORD, Adc_AD1_ADCER_VALUE);
    Mcu_SFR_Write(S12AD1.ADADC.BYTE, Adc_AD1_ADADC_VALUE);
    Mcu_SFR_Write(S12AD1.ADEXICR.WORD, Adc_AD1_ADEXICR_VALUE);
    Mcu_SFR_Write(S12AD1.ADGCEXCR.BYTE, Adc_AD1_ADGCEXCR_VALUE);
    
    Mcu_SFR_Write(S12AD1.ADSTRGR.WORD, Adc_AD1_ADSTRGR_VALUE);
    Mcu_SFR_Write(S12AD1.ADGCTRGR.BYTE, Adc_AD1_ADGCTRGR_VALUE);
    
    Mcu_SFR_Write(S12AD1.ADDISCR.BYTE, Adc_AD1_ADDISCR_VALUE);
    Mcu_SFR_Write(S12AD1.ADGSPCR.WORD, Adc_AD1_ADGSPCR_VALUE);
    Mcu_SFR_Write(S12AD1.ADCMPCR.WORD, Adc_AD1_ADCMPCR_VALUE);

    
    /* A/D変換値加算 / 平均機能 */
    Mcu_SFR_Write(S12AD1.ADADS0.WORD, Adc_AD1_ADADS0_VALUE);
    Mcu_SFR_Write(S12AD1.ADADS1.WORD, Adc_AD1_ADADS1_VALUE);
    
    /* チャネル選択 */
    /* スキャングループA */
    Mcu_SFR_Write(S12AD1.ADANSA0.WORD, Adc_AD1_ADANSA0_VALUE);
    Mcu_SFR_Write(S12AD1.ADANSA1.WORD, Adc_AD1_ADANSA1_VALUE);
    
    /* スキャングループB */
    Mcu_SFR_Write(S12AD1.ADANSB0.WORD, Adc_AD1_ADANSB0_VALUE);
    Mcu_SFR_Write(S12AD1.ADANSB1.WORD, Adc_AD1_ADANSB1_VALUE);
    
    /* スキャングループC */
    Mcu_SFR_Write(S12AD1.ADANSC0.WORD, Adc_AD1_ADANSC0_VALUE);
    Mcu_SFR_Write(S12AD1.ADANSC1.WORD, Adc_AD1_ADANSC1_VALUE);
    
    /* サンプリングステート */
    Mcu_SFR_Write(S12AD1.ADSSTRL, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTRT, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTRO, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR0, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR1, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR2, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR3, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR4, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR5, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR6, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR7, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR8, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR9, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR10, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR11, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR12, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR13, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR14, Adc_ADSSTR_VALUE);
    Mcu_SFR_Write(S12AD1.ADSSTR15, Adc_ADSSTR_VALUE);
}


/**
 * @brief AD変換を実行する
 */
void Adc_StartConversion(void)
{
    volatile uint16_t *addrReg;
    uint8_t ui8t_ch;
    
    /* AD0変換開始 */
    Mcu_SFR_Write(S12AD.ADCSR.BIT.ADST, TRUE);
    
    /* AD1変換開始 */
    Mcu_SFR_Write(S12AD1.ADCSR.BIT.ADST, TRUE);
    
    /* AD0変換待ち */
    while (Mcu_SFR_Read(S12AD.ADCSR.BIT.ADST) == TRUE) {}

    /* AD1変換待ち */
    while (Mcu_SFR_Read(S12AD1.ADCSR.BIT.ADST) == TRUE) {}

    /* AD0読み出し */
    addrReg = &S12AD.ADDR0;
    for (ui8t_ch = IDX_0; ui8t_ch < Adc_AD0_NumCH; ui8t_ch++) {
        Adc_AD0_Buf[ui8t_ch] = Mcu_SFR_Read(addrReg[ui8t_ch]);
    }
    
    /* AD0読み出し */
    addrReg = &S12AD1.ADDR0;
    for (ui8t_ch = IDX_0; ui8t_ch < Adc_AD1_NumCH; ui8t_ch++) {
        Adc_AD1_Buf[ui8t_ch] = Mcu_SFR_Read(addrReg[ui8t_ch]);
    }
}


/**
 * @brief AD変換結果を読み出す
 * @param ui8t_unit A/D変換ユニット 0 or 1
 * @param ui8t_ch A/D変換Ch
 * @return A/D変換結果
 * @note 不正なユニット、Chを指定した場合、Adc_INVALID_VALUEを返す
 */
uint16_t Adc_Read(uint8_t ui8t_unit, uint8_t ui8t_ch)
{
    uint16_t ui16t_ret;
    
    /* 戻り値を仮設定 */
    ui16t_ret = Adc_INVALID_VALUE;
    
    switch (ui8t_unit) {
    case IDX_0:
        if (ui8t_ch < Adc_AD0_NumCH) {
            ui16t_ret = Adc_AD0_Buf[ui8t_ch];
        }
        break;
    case IDX_1:
        if (ui8t_ch < Adc_AD1_NumCH) {
            ui16t_ret = Adc_AD1_Buf[ui8t_ch];
        }
        break;
    default:
        break;
    }
    
    return (ui16t_ret);
}
