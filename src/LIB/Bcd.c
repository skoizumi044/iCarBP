/**
 * @file Bcd.c
 * @brief BCD変換機能を提供する
 */


#include <Std_Types.h>
#include "Bcd.h"


/**
 * @brief 数値をBCD変換する
 * @param ui32t_num 数値 指定可能範囲(0～99999999)
 * @return BCDコード化した数値
 * @note 指定可能範囲外の値を指定した場合、99999999にホールドされる
 */
uint32_t BCD_UI32_to_BCD(uint32_t ui32t_num)
{
    uint32_t ui32t_bcd;
    uint32_t ui32t_digit;
    uint32_t ui32t_div;
    uint32_t ui32t_idx;
    
    /* 上限ガード */
    if (ui32t_num > BCD_MAX) {
        ui32t_num = BCD_MAX;
    }
    
    /* 初期化 */
    ui32t_bcd = VAL_0;
    ui32t_div = BCD_10M;
    
    for (ui32t_idx = IDX_0; ui32t_idx < IDX_8; ui32t_idx++) {
        /* BCDコードを左シフト */
        ui32t_bcd = ui32t_bcd << IDX_4;
        
        /* 桁を取り出す */
        ui32t_digit = ui32t_num / ui32t_div;
        
        /* 取り出した桁をBCDコードに加算 */
        ui32t_bcd |= ui32t_digit;
        
        /* 入力値から減算 */
        ui32t_num -= ui32t_digit * ui32t_div;
        
        /* 次の桁に移動 */
        ui32t_div /= BCD_DIV10;
    }
    
    return (ui32t_bcd);
}
