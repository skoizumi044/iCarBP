/**
 * @file Mcu_Ofs.c
 * @brief OFS definition
 * @note 本モジュールの設定値を変更した場合は動作保証外となります。
 * @note ハードウェアマニュアルを読み、設定内容を理解した上で変更してください。
 * @note 設定値によっては、プログラムを書き込み出来なり、元の設定に戻せなくなる可能性があります。
 *
 */

#include "Mcu.h"


#define OFS_REG   __attribute__ ((section (".ofs1"))) /* 0xFE7F5D00 */ /* MDE, OFS0, OFS1 */
#define OFS_TMINF __attribute__ ((section (".ofs2"))) /* 0xFE7F5D10 */
#define OFS_SPCC  __attribute__ ((section (".ofs3"))) /* 0xFE7F5D40 */
#define OFS_TMEF  __attribute__ ((section (".ofs4"))) /* 0xFE7F5D48 */
#define OFS_OSIS  __attribute__ ((section (".ofs5"))) /* 0xFE7F5D50 */
#define OFS_FAW   __attribute__ ((section (".ofs6"))) /* 0xFE7F5D64 */
#define OFS_RCP   __attribute__ ((section (".ofs7"))) /* 0xFE7F5D70 */

// MDE register (Single Chip Mode)
#ifdef __RX_BIG_ENDIAN__
    const uint32_t __MDEreg OFS_REG = 0xfffffff8;    // big
#else
    const uint32_t __MDEreg OFS_REG = 0xffffffff;    // little
#endif

// OFS0 register
const uint32_t __OFS0reg OFS_REG = 0xffffffff;

// OFS1 register
const uint32_t __OFS1reg OFS_REG = 0xffffffff;

// TMINF register
const uint32_t __TMINFreg OFS_TMINF = 0xffffffff;

// SPCC register
const uint32_t __SPCCreg OFS_SPCC = 0xffffffff;

// TMEF register
const uint32_t __TMEFreg OFS_TMEF = 0xffffffff;

// OSIS register (ID codes)
const uint32_t __OSISreg[4] OFS_OSIS = {
        0xffffffff,
        0xffffffff,
        0xffffffff,
        0xffffffff,
};

// FAW register
const uint32_t __FAWreg OFS_FAW = 0xffffffff;

// RCP register
const uint32_t __RCPreg OFS_RCP = 0xffffffff;
