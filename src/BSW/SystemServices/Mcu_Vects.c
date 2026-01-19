/**
 * @file Mcu_Vects.c
 * @brief Vector table definition
 */

#include "Mcu.h"


/* Externs */
extern void Mcu_GroupInt_BE0Handler(void);
extern void Mcu_GroupInt_BL0Handler(void);
extern void Mcu_GroupInt_BL1Handler(void);
extern void Mcu_GroupInt_BL2Handler(void);
extern void Mcu_GroupInt_AL0Handler(void);
extern void Mcu_GroupInt_AL1Handler(void);


extern void SchM_Task_Int1ms(void);
extern void SchM_Task_Periodic10msINT(void);
extern void Sci_RXIHandler(void);
extern void Sci_TXIHandler(void);
extern void Mtu3_MTU0_TGRA(void);
extern void Mtu3_MTU0_TGRB(void);
extern void Mtu3_MTU0_TGRD(void);
extern void Buzzer_TPU_INT(void);


/* Sector define */
#define EXVECT_SECT     __attribute__ ((section (".exvectors")))
#define FVECT_SECT      __attribute__ ((section (".fvectors")))
#define RVECT_SECT      __attribute__ ((section (".rvectors")))


const void *const Mcu_ExceptVectors[] EXVECT_SECT =
{
    /* 0xffffff80: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffff84: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffff88: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffff8C: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffff90: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffff94: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffff98: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffff9C: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffA0: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffA4: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffA8: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffAC: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffB0: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffB4: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffB8: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffBC: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffC0: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffC4: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffC8: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffCC: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffd0: Exception(Supervisor Instruction) */
    &Mcu_UnhandledException,
    /* 0xffffffd4: Exception(Access Instruction) */
    &Mcu_UnhandledException,
    /* 0xffffffd8: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffdc: Exception(Undefined Instruction) */
    &Mcu_UnhandledException,
    /* 0xffffffe0: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffe4: Exception(Floating Point) */
    &Mcu_UnhandledException,
    /* 0xffffffe8: Reserved */
    &Mcu_UnhandledException,
    /* 0xffffffec: Reserved */
    &Mcu_UnhandledException,
    /* 0xfffffff0: Reserved */
    &Mcu_UnhandledException,
    /* 0xfffffff4: Reserved */
    &Mcu_UnhandledException,
    /* 0xfffffff8: NMI */
    &Mcu_UnhandledException,
};


const void *const Mcu_HardwareVectors[] FVECT_SECT =
{
    /* 0xfffffffc: RESET */
    /* Power On Reset PC */
    &PowerON_Reset
};


const void *const Mcu_RelocatableVectors[] RVECT_SECT =
{
    /* 0x0000: Reserved */
    &Mcu_UnhandledException,
    /* 0x0004: Reserved */
    &Mcu_UnhandledException,
    /* 0x0008: Reserved */
    &Mcu_UnhandledException,
    /* 0x000C: Reserved */
    &Mcu_UnhandledException,
    /* 0x0010: Reserved */
    &Mcu_UnhandledException,
    /* 0x0014: Reserved */
    &Mcu_UnhandledException,
    /* 0x0018: Reserved */
    &Mcu_UnhandledException,
    /* 0x001C: Reserved */
    &Mcu_UnhandledException,
    /* 0x0020: Reserved */
    &Mcu_UnhandledException,
    /* 0x0024: Reserved */
    &Mcu_UnhandledException,
    /* 0x0028: Reserved */
    &Mcu_UnhandledException,
    /* 0x002C: Reserved */
    &Mcu_UnhandledException,
    /* 0x0030: Reserved */
    &Mcu_UnhandledException,
    /* 0x0034: Reserved */
    &Mcu_UnhandledException,
    /* 0x0038: Reserved */
    &Mcu_UnhandledException,
    /* 0x003C: Reserved */
    &Mcu_UnhandledException,
    /* 0x0040: BSC_BUSERR */
    &Mcu_UnhandledException,
    /* 0x0044: Reserved */
    &Mcu_UnhandledException,
    /* 0x0048: RAM_RAMERR */
    &Mcu_UnhandledException,
    /* 0x004C: Reserved */
    &Mcu_UnhandledException,
    /* 0x0050: Reserved */
    &Mcu_UnhandledException,
    /* 0x0054: FCU_FIFERR */
    &Mcu_UnhandledException,
    /* 0x0058: Reserved */
    &Mcu_UnhandledException,
    /* 0x005C: FCU_FRDYI */
    &Mcu_UnhandledException,
    /* 0x0060: Reserved */
    &Mcu_UnhandledException,
    /* 0x0064: Reserved */
    &Mcu_UnhandledException,
    /* 0x0068: ICU_SWINT2 */
    &Mcu_UnhandledException,
    /* 0x006C: ICU_SWINT */
    &SchM_Task_Periodic10msINT,
    /* 0x0070: CMT0_CMI0 */
    &Mcu_UnhandledException,
    /* 0x0074: CMT1_CMI1 */
    &Mcu_UnhandledException,
    /* 0x0078: CMTW0_CMWI0 */
    &SchM_Task_Int1ms,
    /* 0x007C: CMTW1_CMWI1 */
    &Mcu_UnhandledException,
    /* 0x0080: Reserved */
    &Mcu_UnhandledException,
    /* 0x0084: Reserved */
    &Mcu_UnhandledException,
    /* 0x0088: USB0_D0FIFO0 */
    &Mcu_UnhandledException,
    /* 0x008C: USB0_D1FIFO0 */
    &Mcu_UnhandledException,
    /* 0x0090: Reserved */
    &Mcu_UnhandledException,
    /* 0x0094: Reserved */
    &Mcu_UnhandledException,
    /* 0x0098: RSPI0_SPRI0 */
    &Mcu_UnhandledException,
    /* 0x009C: RSPI0_SPTI0 */
    &Mcu_UnhandledException,
    /* 0x00A0: RSPI1_SPRI1 */
    &Mcu_UnhandledException,
    /* 0x00A4: RSPI1_SPTI1 */
    &Mcu_UnhandledException,
    /* 0x00A8: QSPI_SPRI */
    &Mcu_UnhandledException,
    /* 0x00AC: QSPI_SPTI */
    &Mcu_UnhandledException,
    /* 0x00B0: SDHI_SBFAI */
    &Mcu_UnhandledException,
    /* 0x00B4: MMCIF_MBFAI */
    &Mcu_UnhandledException,
    /* 0x00B8: Reserved */
    &Mcu_UnhandledException,
    /* 0x00BC: Reserved */
    &Mcu_UnhandledException,
    /* 0x00C0: Reserved */
    &Mcu_UnhandledException,
    /* 0x00C4: Reserved */
    &Mcu_UnhandledException,
    /* 0x00C8: Reserved */
    &Mcu_UnhandledException,
    /* 0x00CC: Reserved */
    &Mcu_UnhandledException,
    /* 0x00D0: RIIC0_RXI0 */
    &Mcu_UnhandledException,
    /* 0x00D4: RIIC0_TXI0 */
    &Mcu_UnhandledException,
    /* 0x00D8: RIIC2_RXI2 */
    &Mcu_UnhandledException,
    /* 0x00DC: RIIC2_TXI2 */
    &Mcu_UnhandledException,
    /* 0x00E0: Reserved */
    &Mcu_UnhandledException,
    /* 0x00E4: Reserved */
    &Mcu_UnhandledException,
    /* 0x00E8: SCI0_RXI0 */
    &Mcu_UnhandledException,
    /* 0x00EC: SCI0_TXI0 */
    &Mcu_UnhandledException,
    /* 0x00F0: SCI1_RXI1 */
    &Sci_RXIHandler,
    /* 0x00F4: SCI1_TXI1 */
    &Sci_TXIHandler,
    /* 0x00F8: SCI2_RXI2 */
    &Mcu_UnhandledException,
    /* 0x00FC: SCI2_TXI2 */
    &Mcu_UnhandledException,
    /* 0x0100: ICU_IRQ0 */
    &Mcu_UnhandledException,
    /* 0x0104: ICU_IRQ1 */
    &Mcu_UnhandledException,
    /* 0x0108: ICU_IRQ2 */
    &Mcu_UnhandledException,
    /* 0x010C: ICU_IRQ3 */
    &Mcu_UnhandledException,
    /* 0x0110: ICU_IRQ4 */
    &Mcu_UnhandledException,
    /* 0x0114: ICU_IRQ5 */
    &Mcu_UnhandledException,
    /* 0x0118: ICU_IRQ6 */
    &Mcu_UnhandledException,
    /* 0x011C: ICU_IRQ7 */
    &Mcu_UnhandledException,
    /* 0x0120: ICU_IRQ8 */
    &Mcu_UnhandledException,
    /* 0x0124: ICU_IRQ9 */
    &Mcu_UnhandledException,
    /* 0x0128: ICU_IRQ10 */
    &Mcu_UnhandledException,
    /* 0x012C: ICU_IRQ11 */
    &Mcu_UnhandledException,
    /* 0x0130: ICU_IRQ12 */
    &Mcu_UnhandledException,
    /* 0x0134: ICU_IRQ13 */
    &Mcu_UnhandledException,
    /* 0x0138: ICU_IRQ14 */
    &Mcu_UnhandledException,
    /* 0x013C: ICU_IRQ15 */
    &Mcu_UnhandledException,
    /* 0x0140: SCI3_RXI3 */
    &Mcu_UnhandledException,
    /* 0x0144: SCI3_TXI3 */
    &Mcu_UnhandledException,
    /* 0x0148: SCI4_RXI4 */
    &Mcu_UnhandledException,
    /* 0x014C: SCI4_TXI4 */
    &Mcu_UnhandledException,
    /* 0x0150: SCI5_RXI5 */
    &Mcu_UnhandledException,
    /* 0x0154: SCI5_TXI5 */
    &Mcu_UnhandledException,
    /* 0x0158: SCI6_RXI6 */
    &Mcu_UnhandledException,
    /* 0x015C: SCI6_TXI6 */
    &Mcu_UnhandledException,
    /* 0x0160: LVD1_LVD1 */
    &Mcu_UnhandledException,
    /* 0x0164: LVD2_LVD2 */
    &Mcu_UnhandledException,
    /* 0x0168: USB0_USBR0 */
    &Mcu_UnhandledException,
    /* 0x016C: Reserved */
    &Mcu_UnhandledException,
    /* 0x0170: RTC_ALM */
    &Mcu_UnhandledException,
    /* 0x0174: RTC_PRD */
    &Mcu_UnhandledException,
    /* 0x0178: Reserved */
    &Mcu_UnhandledException,
    /* 0x017C: IWDT_IWUNI */
    &Mcu_UnhandledException,
    /* 0x0180: WDT_WUNI */
    &Mcu_UnhandledException,
    /* 0x0184: PDC_PCDFI */
    &Mcu_UnhandledException,
    /* 0x0188: SCI7_RXI7 */
    &Mcu_UnhandledException,
    /* 0x018C: SCI7_TXI7 */
    &Mcu_UnhandledException,
    /* 0x0190: SCI8_RXI8 */
    &Mcu_UnhandledException,
    /* 0x0194: SCI8_TXI8 */
    &Mcu_UnhandledException,
    /* 0x0198: SCI9_RXI9 */
    &Mcu_UnhandledException,
    /* 0x019C: SCI9_TXI9 */
    &Mcu_UnhandledException,
    /* 0x01A0: SCI10_RXI10 */
    &Mcu_UnhandledException,
    /* 0x01A4: SCI10_TXI10 */
    &Mcu_UnhandledException,
    /* 0x01A8: ICU_GROUPBE0 */
    &Mcu_GroupInt_BE0Handler,
    /* 0x01AC: ICU_GROUPBL2 */
    &Mcu_GroupInt_BL2Handler,
    /* 0x01B0: RSPI2_SPRI2 */
    &Mcu_UnhandledException,
    /* 0x01B4: RSPI2_SPTI2 */
    &Mcu_UnhandledException,
    /* 0x01B8: ICU_GROUPBL0 */
    &Mcu_GroupInt_BL0Handler,
    /* 0x01BC: ICU_GROUPBL1 */
    &Mcu_GroupInt_BL1Handler,
    /* 0x01C0: ICU_GROUPAL0 */
    &Mcu_GroupInt_AL0Handler,
    /* 0x01C4: ICU_GROUPAL1 */
    &Mcu_GroupInt_AL1Handler,
    /* 0x01C8: SCI11_RXI11 */
    &Mcu_UnhandledException,
    /* 0x01CC: SCI11_TXI11 */
    &Mcu_UnhandledException,
    /* 0x01D0: SCI12_RXI12 */
    &Mcu_UnhandledException,
    /* 0x01D4: SCI12_TXI12 */
    &Mcu_UnhandledException,
    /* 0x01D8: Reserved */
    &Mcu_UnhandledException,
    /* 0x01DC: Reserved */
    &Mcu_UnhandledException,
    /* 0x01E0: DMAC_DMAC0I */
    &Mcu_UnhandledException,
    /* 0x01E4: DMAC_DMAC1I */
    &Mcu_UnhandledException,
    /* 0x01E8: DMAC_DMAC2I */
    &Mcu_UnhandledException,
    /* 0x01EC: DMAC_DMAC3I */
    &Mcu_UnhandledException,
    /* 0x01F0: DMAC_DMAC74I */
    &Mcu_UnhandledException,
    /* 0x01F4: OST_OSTDI */
    &Mcu_UnhandledException,
    /* 0x01F8: EXDMAC_EXDMAC0I */
    &Mcu_UnhandledException,
    /* 0x01FC: EXDMAC_EXDMAC1I */
    &Mcu_UnhandledException,
    /* 0x0200: PERIB_INTB128 */
    &Buzzer_TPU_INT,
    /* 0x0204: PERIB_INTB129 */
    &Mcu_UnhandledException,
    /* 0x0208: PERIB_INTB130 */
    &Mcu_UnhandledException,
    /* 0x020C: PERIB_INTB131 */
    &Mcu_UnhandledException,
    /* 0x0210: PERIB_INTB132 */
    &Mcu_UnhandledException,
    /* 0x0214: PERIB_INTB133 */
    &Mcu_UnhandledException,
    /* 0x0218: PERIB_INTB134 */
    &Mcu_UnhandledException,
    /* 0x021C: PERIB_INTB135 */
    &Mcu_UnhandledException,
    /* 0x0220: PERIB_INTB136 */
    &Mcu_UnhandledException,
    /* 0x0224: PERIB_INTB137 */
    &Mcu_UnhandledException,
    /* 0x0228: PERIB_INTB138 */
    &Mcu_UnhandledException,
    /* 0x022C: PERIB_INTB139 */
    &Mcu_UnhandledException,
    /* 0x0230: PERIB_INTB140 */
    &Mcu_UnhandledException,
    /* 0x0234: PERIB_INTB141 */
    &Mcu_UnhandledException,
    /* 0x0238: PERIB_INTB142 */
    &Mcu_UnhandledException,
    /* 0x023C: PERIB_INTB143 */
    &Mcu_UnhandledException,
    /* 0x0240: PERIB_INTB144 */
    &Mcu_UnhandledException,
    /* 0x0244: PERIB_INTB145 */
    &Mcu_UnhandledException,
    /* 0x0248: PERIB_INTB146 */
    &Mcu_UnhandledException,
    /* 0x024C: PERIB_INTB147 */
    &Mcu_UnhandledException,
    /* 0x0250: PERIB_INTB148 */
    &Mcu_UnhandledException,
    /* 0x0254: PERIB_INTB149 */
    &Mcu_UnhandledException,
    /* 0x0258: PERIB_INTB150 */
    &Mcu_UnhandledException,
    /* 0x025C: PERIB_INTB151 */
    &Mcu_UnhandledException,
    /* 0x0260: PERIB_INTB152 */
    &Mcu_UnhandledException,
    /* 0x0264: PERIB_INTB153 */
    &Mcu_UnhandledException,
    /* 0x0268: PERIB_INTB154 */
    &Mcu_UnhandledException,
    /* 0x026C: PERIB_INTB155 */
    &Mcu_UnhandledException,
    /* 0x0270: PERIB_INTB156 */
    &Mcu_UnhandledException,
    /* 0x0274: PERIB_INTB157 */
    &Mcu_UnhandledException,
    /* 0x0278: PERIB_INTB158 */
    &Mcu_UnhandledException,
    /* 0x027C: PERIB_INTB159 */
    &Mcu_UnhandledException,
    /* 0x0280: PERIB_INTB160 */
    &Mcu_UnhandledException,
    /* 0x0284: PERIB_INTB161 */
    &Mcu_UnhandledException,
    /* 0x0288: PERIB_INTB162 */
    &Mcu_UnhandledException,
    /* 0x028C: PERIB_INTB163 */
    &Mcu_UnhandledException,
    /* 0x0290: PERIB_INTB164 */
    &Mcu_UnhandledException,
    /* 0x0294: PERIB_INTB165 */
    &Mcu_UnhandledException,
    /* 0x0298: PERIB_INTB166 */
    &Mcu_UnhandledException,
    /* 0x029C: PERIB_INTB167 */
    &Mcu_UnhandledException,
    /* 0x02A0: PERIB_INTB168 */
    &Mcu_UnhandledException,
    /* 0x02A4: PERIB_INTB169 */
    &Mcu_UnhandledException,
    /* 0x02A8: PERIB_INTB170 */
    &Mcu_UnhandledException,
    /* 0x02AC: PERIB_INTB171 */
    &Mcu_UnhandledException,
    /* 0x02B0: PERIB_INTB172 */
    &Mcu_UnhandledException,
    /* 0x02B4: PERIB_INTB173 */
    &Mcu_UnhandledException,
    /* 0x02B8: PERIB_INTB174 */
    &Mcu_UnhandledException,
    /* 0x02BC: PERIB_INTB175 */
    &Mcu_UnhandledException,
    /* 0x02C0: PERIB_INTB176 */
    &Mcu_UnhandledException,
    /* 0x02C4: PERIB_INTB177 */
    &Mcu_UnhandledException,
    /* 0x02C8: PERIB_INTB178 */
    &Mcu_UnhandledException,
    /* 0x02CC: PERIB_INTB179 */
    &Mcu_UnhandledException,
    /* 0x02D0: PERIB_INTB180 */
    &Mcu_UnhandledException,
    /* 0x02D4: PERIB_INTB181 */
    &Mcu_UnhandledException,
    /* 0x02D8: PERIB_INTB182 */
    &Mcu_UnhandledException,
    /* 0x02DC: PERIB_INTB183 */
    &Mcu_UnhandledException,
    /* 0x02E0: PERIB_INTB184 */
    &Mcu_UnhandledException,
    /* 0x02E4: PERIB_INTB185 */
    &Mcu_UnhandledException,
    /* 0x02E8: PERIB_INTB186 */
    &Mcu_UnhandledException,
    /* 0x02EC: PERIB_INTB187 */
    &Mcu_UnhandledException,
    /* 0x02F0: PERIB_INTB188 */
    &Mcu_UnhandledException,
    /* 0x02F4: PERIB_INTB189 */
    &Mcu_UnhandledException,
    /* 0x02F8: PERIB_INTB190 */
    &Mcu_UnhandledException,
    /* 0x02FC: PERIB_INTB191 */
    &Mcu_UnhandledException,
    /* 0x0300: PERIB_INTB192 */
    &Mcu_UnhandledException,
    /* 0x0304: PERIB_INTB193 */
    &Mcu_UnhandledException,
    /* 0x0308: PERIB_INTB194 */
    &Mcu_UnhandledException,
    /* 0x030C: PERIB_INTB195 */
    &Mcu_UnhandledException,
    /* 0x0310: PERIB_INTB196 */
    &Mcu_UnhandledException,
    /* 0x0314: PERIB_INTB197 */
    &Mcu_UnhandledException,
    /* 0x0318: PERIB_INTB198 */
    &Mcu_UnhandledException,
    /* 0x031C: PERIB_INTB199 */
    &Mcu_UnhandledException,
    /* 0x0320: PERIB_INTB200 */
    &Mcu_UnhandledException,
    /* 0x0324: PERIB_INTB201 */
    &Mcu_UnhandledException,
    /* 0x0328: PERIB_INTB202 */
    &Mcu_UnhandledException,
    /* 0x032C: PERIB_INTB203 */
    &Mcu_UnhandledException,
    /* 0x0330: PERIB_INTB204 */
    &Mcu_UnhandledException,
    /* 0x0334: PERIB_INTB205 */
    &Mcu_UnhandledException,
    /* 0x0338: PERIB_INTB206 */
    &Mcu_UnhandledException,
    /* 0x033C: PERIB_INTB207 */
    &Mcu_UnhandledException,
    /* 0x0340: PERIA_INTA208 */
    &Mtu3_MTU0_TGRA,
    /* 0x0344: PERIA_INTA209 */
    &Mtu3_MTU0_TGRB,
    /* 0x0348: PERIA_INTA210 */
    &Mtu3_MTU0_TGRD,
    /* 0x034C: PERIA_INTA211 */
    &Mcu_UnhandledException,
    /* 0x0350: PERIA_INTA212 */
    &Mcu_UnhandledException,
    /* 0x0354: PERIA_INTA213 */
    &Mcu_UnhandledException,
    /* 0x0358: PERIA_INTA214 */
    &Mcu_UnhandledException,
    /* 0x035C: PERIA_INTA215 */
    &Mcu_UnhandledException,
    /* 0x0360: PERIA_INTA216 */
    &Mcu_UnhandledException,
    /* 0x0364: PERIA_INTA217 */
    &Mcu_UnhandledException,
    /* 0x0368: PERIA_INTA218 */
    &Mcu_UnhandledException,
    /* 0x036C: PERIA_INTA219 */
    &Mcu_UnhandledException,
    /* 0x0370: PERIA_INTA220 */
    &Mcu_UnhandledException,
    /* 0x0374: PERIA_INTA221 */
    &Mcu_UnhandledException,
    /* 0x0378: PERIA_INTA222 */
    &Mcu_UnhandledException,
    /* 0x037C: PERIA_INTA223 */
    &Mcu_UnhandledException,
    /* 0x0380: PERIA_INTA224 */
    &Mcu_UnhandledException,
    /* 0x0384: PERIA_INTA225 */
    &Mcu_UnhandledException,
    /* 0x0388: PERIA_INTA226 */
    &Mcu_UnhandledException,
    /* 0x038C: PERIA_INTA227 */
    &Mcu_UnhandledException,
    /* 0x0390: PERIA_INTA228 */
    &Mcu_UnhandledException,
    /* 0x0394: PERIA_INTA229 */
    &Mcu_UnhandledException,
    /* 0x0398: PERIA_INTA230 */
    &Mcu_UnhandledException,
    /* 0x039C: PERIA_INTA231 */
    &Mcu_UnhandledException,
    /* 0x03A0: PERIA_INTA232 */
    &Mcu_UnhandledException,
    /* 0x03A4: PERIA_INTA233 */
    &Mcu_UnhandledException,
    /* 0x03A8: PERIA_INTA234 */
    &Mcu_UnhandledException,
    /* 0x03AC: PERIA_INTA235 */
    &Mcu_UnhandledException,
    /* 0x03B0: PERIA_INTA236 */
    &Mcu_UnhandledException,
    /* 0x03B4: PERIA_INTA237 */
    &Mcu_UnhandledException,
    /* 0x03B8: PERIA_INTA238 */
    &Mcu_UnhandledException,
    /* 0x03BC: PERIA_INTA239 */
    &Mcu_UnhandledException,
    /* 0x03C0: PERIA_INTA240 */
    &Mcu_UnhandledException,
    /* 0x03C4: PERIA_INTA241 */
    &Mcu_UnhandledException,
    /* 0x03C8: PERIA_INTA242 */
    &Mcu_UnhandledException,
    /* 0x03CC: PERIA_INTA243 */
    &Mcu_UnhandledException,
    /* 0x03D0: PERIA_INTA244 */
    &Mcu_UnhandledException,
    /* 0x03D4: PERIA_INTA245 */
    &Mcu_UnhandledException,
    /* 0x03D8: PERIA_INTA246 */
    &Mcu_UnhandledException,
    /* 0x03DC: PERIA_INTA247 */
    &Mcu_UnhandledException,
    /* 0x03E0: PERIA_INTA248 */
    &Mcu_UnhandledException,
    /* 0x03E4: PERIA_INTA249 */
    &Mcu_UnhandledException,
    /* 0x03E8: PERIA_INTA250 */
    &Mcu_UnhandledException,
    /* 0x03EC: PERIA_INTA251 */
    &Mcu_UnhandledException,
    /* 0x03F0: PERIA_INTA252 */
    &Mcu_UnhandledException,
    /* 0x03F4: PERIA_INTA253 */
    &Mcu_UnhandledException,
    /* 0x03F8: PERIA_INTA254 */
    &Mcu_UnhandledException,
    /* 0x03FC: PERIA_INTA255 */
    &Mcu_UnhandledException,
};
