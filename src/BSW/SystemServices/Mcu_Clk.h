/**
 * @file Mcu_Clk.h
 * @brief MCUクロックの初期化を行う
 * @author KSEII T.Terazawa
 * @copyright 2020 Kernel Software Engineering
 */

#ifndef __Mcu_Clk_H
#define __Mcu_Clk_H


#include "Mcu_Clk_Cfg.h"


#ifdef __cplusplus
extern "C" {
#endif


void Mcu_Clk_Init(void);
void Mcu_Clk_Wait150us_LOCO(void);


#ifdef __cplusplus
}
#endif


#endif
