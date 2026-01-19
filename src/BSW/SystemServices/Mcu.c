/**
 * @file Mcu.c
 * @brief MCUの初期化を行う
 */

#include "Mcu.h"


#include <IODrivers/Port.h>
#include "SchM.h"


/**
 * @brief リセット起動時の初期化処理1
 * @note 本関数はRAM初期化前に実行される
 */
void HardwareSetup(void)
{
    /* ポートを初期化 */
    Port_Init();
    
    /* クロックを初期化 */
    Mcu_Clk_Init();
}


/**
 * @brief メイン関数
 */
void main(void)
{
    /* 割り込みレベルを設定 */
    Mcu_GroupInt_Init();
    
    /* スケジューラを初期化 */
    SchM_Init();
    
    Mcu_EI_Imm();
    SchM_Start();
}


/**
 * @brief 指定マイクロ秒以上待機する
 * @param ui32t_us 待機時間[us] (最大1000[us])
 * @note 本関数はCPUがPLL周波数で高速動作している前提で有効
 * @note 指定した時間以上待機すること以外は保証していない為、
 *       正確な待ち時間を確保する場合は別途処理の実装が必要。
 */
void Mcu_WaitUS(uint32_t ui32t_us)
{
    register uint32_t ui32t_loop = ui32t_us;

    while (ui32t_loop-- != 0)
    {
#if Mcu_Clk_Cfg_ILCK_FREQ_KHZ == (120000)
        /* 120NOP - 4 (SUB, BRANCH) */
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_10();
        Mcu_NOP_5();
        Mcu_NOP();
#else
#error "Mcu_WaitUS() Invalid Mcu_Clk_Cfg_ILCK_FREQ_KHZ. Please configure."
#endif
    }
}


/**
 * @brief 未定義・不正割込み・例外発生時の処理
 */
 void __attribute__((interrupt)) Mcu_UnhandledException(void)
{
    /* 無限ループ */
    while (1) {}
}
