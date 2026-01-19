/**
 * @file Adc_Cfg.c
 * @brief A/D変換に関する設定
 */

#ifndef __Adc_Cfg_H
#define __Adc_Cfg_H


#ifdef __cplusplus
extern "C" {
#endif


#define Adc_AD0_NumCH               (8)
#define Adc_AD1_NumCH               (21)


#ifdef __Adc_C

/*---------------------------------------------------*/
/* Ch共通                                            */
/*---------------------------------------------------*/
/* サンプリング時間設定 */
#define Adc_ADSSTR_VALUE            (0x0Bu)


/*---------------------------------------------------*/
/* S12AD                                             */
/*---------------------------------------------------*/
/* 逐次変換時間 */
#define Adc_AD0_ADSAM_VALUE         (0x0000u)

/* 変換設定 */
#define Adc_AD0_ADCSR_VALUE         (0x0000u)
#define Adc_AD0_ADCER_VALUE         (0x0000u)
#define Adc_AD0_ADADC_VALUE         (0x00u)

/* トリガ設定 */
#define Adc_AD0_ADSTRGR_VALUE       (0x3F3Fu)
#define Adc_AD0_ADGCTRGR_VALUE      (0x3Fu)
#define Adc_AD0_ADSHCR_VALUE        (0x0018u)

/* サンプル&ホールド設定 */
#define Adc_AD0_ADSHMSR_VALUE       (0x00u)

/* 断線検出設定 */
#define Adc_AD0_ADDISCR_VALUE       (0x00u)

/* A/Dコンペア設定 */
#define Adc_AD0_ADCMPCR_VALUE       (0x0000u)

/* A/D変換値加算 / 平均機能設定 */
#define Adc_AD0_ADADS0_VALUE        (0x0000u)

/* A/D変換グループ */
#define Adc_AD0_ADGSPCR_VALUE       (0x0000u)

#define Adc_AD0_ADANSA0_VALUE       (0x0066u)
#define Adc_AD0_ADANSB0_VALUE       (0x0000u)
#define Adc_AD0_ADANSC0_VALUE       (0x0000u)


/*---------------------------------------------------*/
/* S12AD1                                            */
/*---------------------------------------------------*/
/* 逐次変換時間 */
#define Adc_AD1_ADSAM_VALUE         (0x0020u)

/* 変換設定 */
#define Adc_AD1_ADCSR_VALUE         (0x0000u)
#define Adc_AD1_ADCER_VALUE         (0x0000u)
#define Adc_AD1_ADADC_VALUE         (0x00u)

/* 拡張入力設定 */
#define Adc_AD1_ADEXICR_VALUE       (0x0000u)
#define Adc_AD1_ADGCEXCR_VALUE      (0x00u)

/* トリガ設定 */
#define Adc_AD1_ADSTRGR_VALUE       (0x3F3Fu)
#define Adc_AD1_ADGCTRGR_VALUE      (0x3Fu)

/* 断線検出設定 */
#define Adc_AD1_ADDISCR_VALUE       (0x00u)

/* A/Dコンペア設定 */
#define Adc_AD1_ADCMPCR_VALUE       (0x0000u)

/* A/D変換値加算 / 平均機能設定 */
#define Adc_AD1_ADADS0_VALUE        (0x0000u)
#define Adc_AD1_ADADS1_VALUE        (0x0000u)

/* A/D変換グループ */
#define Adc_AD1_ADGSPCR_VALUE       (0x0000u)

#define Adc_AD1_ADANSA0_VALUE       (0x0230u)
#define Adc_AD1_ADANSA1_VALUE       (0x0000u)
#define Adc_AD1_ADANSB0_VALUE       (0x0000u)
#define Adc_AD1_ADANSB1_VALUE       (0x0000u)
#define Adc_AD1_ADANSC0_VALUE       (0x0000u)
#define Adc_AD1_ADANSC1_VALUE       (0x0000u)

#endif


#ifdef __cplusplus
}
#endif


#endif
