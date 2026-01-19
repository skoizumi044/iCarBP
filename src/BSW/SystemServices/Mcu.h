/**
 * @file Mcu.h
 * @brief MCUの初期化を行う
 * @author KSEII T.Terazawa
 * @copyright 2020 Kernel Software Engineering
 */

#ifndef __Mcu_H
#define __Mcu_H


#include <Std_Types.h>
#include <iodefine.h>


#include "Mcu_Clk.h"
#include "Mcu_GroupInt.h"


#ifdef __cplusplus
extern "C" {
#endif


/** @def MCUのI/Oレジスタに書き込みする
 *  reg レジスタ名
 *  value 書き込み値
 */
#define Mcu_SFR_Write(reg, value)   ((reg) = (value))


/** @def MCUのI/Oレジスタに書き込みおよびベリファイを行う
 *  reg レジスタ名
 *  value 書き込み値
 */
#define Mcu_SFR_WriteVerify(reg, value) \
    do { \
        Mcu_SFR_Write((reg), (value)); \
    } while (Mcu_SFR_Read(reg) != (value));


/**
 * @fn MCUのI/Oレジスタに1bit書き込みを行う
 * ui8tp_reg レジスタ名 (1Byteポインタ)
 * ui32t_bit 書き込みビット
 * ui32t_value 書き込み値 (0 or 1)
 */
void Mcu_SFR_WriteBit(volatile uint8_t *ui8tp_reg, uint32_t ui32t_bit, uint32_t ui32t_value);


/** @def MCUのI/Oレジスタから読み込みする
 *  reg レジスタ名
 */
#define Mcu_SFR_Read(reg)           (reg)


#define Mcu_NOP()                   asm volatile ("NOP")
#define Mcu_NOP_5()                 Mcu_NOP(); Mcu_NOP(); Mcu_NOP(); Mcu_NOP(); Mcu_NOP()
#define Mcu_NOP_10()                Mcu_NOP_5(); Mcu_NOP_5()

#define Mcu_Set_Ilm(il)             asm volatile ("MVTIPL %0" :: "i"(il))
#define Mcu_DI_Imm()                asm volatile ("CLRPSW I")
#define Mcu_EI_Imm()                asm volatile ("SETPSW I")
#define Mcu_BRK()                   asm volatile ("BRK")


#define Mcu_PSW_I                   (0x00010000)

#define Mcu_DI()                                                \
    do {                                                        \
        uint32_t ui32t_Mcu_PSWCurrent;                          \
                                                                \
        ui32t_Mcu_PSWCurrent = Mcu_GetPSW();                    \
        Mcu_DI_Imm()


#define Mcu_EI()                                                \
        if ((ui32t_Mcu_PSWCurrent & Mcu_PSW_I) == Mcu_PSW_I) {  \
            Mcu_EI_Imm();                                       \
        }                                                       \
    } while (0)


void PowerON_Reset(void);
void __attribute__((interrupt)) Mcu_UnhandledException(void);

uint32_t Mcu_GetPSW(void);
void Mcu_WaitUS(uint32_t ui32t_us);
uint32_t Mcu_InterlockedExchange(volatile uint32_t *ptarget, uint32_t value);


#define Mcu_PRCR_KEY        (0xA500u)
#define Mcu_PRCR_PRC0       (0x0001u)
#define Mcu_PRCR_PRC1       (0x0002u)
#define Mcu_PRCR_PRC2       (0x0004u)
#define Mcu_PRCR_PRC3       (0x0008u)


#ifdef __cplusplus
}
#endif


#endif
