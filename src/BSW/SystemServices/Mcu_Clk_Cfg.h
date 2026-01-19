/**
 * @file Mcu_Clk_Cfg.h
 * @brief Clockの設定を行う
 */
#ifndef __Mcu_Clk_Cfg_H
#define __Mcu_Clk_Cfg_H


#ifdef __cplusplus
extern "C" {
#endif


#define Mcu_Clk_Cfg_MAINOSC_ENABLE (TRUE)
#define Mcu_Clk_Cfg_HOCO_ENABLE (FALSE)
#define Mcu_Clk_Cfg_SUBOSC_ENABLE (FALSE)
#define Mcu_Clk_Cfg_PLL_ENABLE (TRUE)

#define Mcu_Clk_Cfg_SCKCR_VALUE (0x21461233uL)
#define Mcu_Clk_Cfg_SCKCR2_VALUE (0x0041u)
#define Mcu_Clk_Cfg_SCKCR3_VALUE (0x0400u)
#define Mcu_Clk_Cfg_ROMWT_VALUE (0x02u)
#define Mcu_Clk_Cfg_PLLCR_VALUE (0x1700u)
#define Mcu_Clk_Cfg_BCKCR_VALUE (1u)
#define Mcu_Clk_Cfg_HOCOCR2_VALUE (0x00u)

#define Mcu_Clk_Cfg_MOSCWTCR_VALUE (83u)
#define Mcu_Clk_Cfg_SOSCWTCR_VALUE (33u)
#define Mcu_Clk_Cfg_MOFCR_VALUE (0x10u)

#define Mcu_Clk_Cfg_LOCO_FREQ_KHZ (240)
#define Mcu_Clk_Cfg_HOCO_FREQ_KHZ (0)
#define Mcu_Clk_Cfg_MAINOSC_FREQ_KHZ (20000)
#define Mcu_Clk_Cfg_SUBOSC_FREQ_KHZ (0)
#define Mcu_Clk_Cfg_FLCK_FREQ_KHZ (60000)
#define Mcu_Clk_Cfg_ILCK_FREQ_KHZ (120000)
#define Mcu_Clk_Cfg_BLCK_FREQ_KHZ (3750)
#define Mcu_Clk_Cfg_PCLKA_FREQ_KHZ (120000)
#define Mcu_Clk_Cfg_PCLKB_FREQ_KHZ (60000)
#define Mcu_Clk_Cfg_PCLKC_FREQ_KHZ (30000)
#define Mcu_Clk_Cfg_PCLKD_FREQ_KHZ (30000)


#ifdef __cplusplus
}
#endif


#endif
