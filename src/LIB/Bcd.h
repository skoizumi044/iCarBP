/**
 * @file Bcd.h
 * @brief BCD変換機能を提供する
 */

#ifndef __Bcd_H
#define __Bcd_H


#ifdef __cplusplus
extern "C" {
#endif


#define BCD_MAX     (99999999uL)
#define BCD_10M     (10000000uL)
#define BCD_DIV10   (10uL)
#define BCD_DIGIT   (0xFu)

uint32_t BCD_UI32_to_BCD(uint32_t ui32t_num);


#ifdef __cplusplus
}
#endif


#endif
