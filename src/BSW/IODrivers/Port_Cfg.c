/**
 * @file Port_Cfg.c
 * @brief I/Oポート設定を行う
 */

#include <SystemServices/Mcu.h>

#include "Port.h"


/* PODR初期設定 */
#define Port_PODR_PORT0_INIT (0x00)
#define Port_PODR_PORT1_INIT (0x00)
#define Port_PODR_PORT2_INIT (0x60)
#define Port_PODR_PORT3_INIT (0x04)
#define Port_PODR_PORT4_INIT (0x00)
#define Port_PODR_PORT5_INIT (0x08)
#define Port_PODR_PORT6_INIT (0x00)
#define Port_PODR_PORT7_INIT (0x00)
#define Port_PODR_PORT8_INIT (0x00)
#define Port_PODR_PORT9_INIT (0x00)
#define Port_PODR_PORTA_INIT (0xC0)
#define Port_PODR_PORTB_INIT (0x30)
#define Port_PODR_PORTC_INIT (0x00)
#define Port_PODR_PORTD_INIT (0x00)
#define Port_PODR_PORTE_INIT (0x00)
#define Port_PODR_PORTF_INIT (0x00)
#define Port_PODR_PORTG_INIT (0x00)
#define Port_PODR_PORTJ_INIT (0x00)

/* PDR初期設定 */
#define Port_PDR_PORT0_INIT (0xFF)
#define Port_PDR_PORT1_INIT (0xF3)
#define Port_PDR_PORT2_INIT (0x75)
#define Port_PDR_PORT3_INIT (0x14)
#define Port_PDR_PORT4_INIT (0x99)
#define Port_PDR_PORT5_INIT (0xFF)
#define Port_PDR_PORT6_INIT (0xFF)
#define Port_PDR_PORT7_INIT (0xFF)
#define Port_PDR_PORT8_INIT (0xFF)
#define Port_PDR_PORT9_INIT (0xFF)
#define Port_PDR_PORTA_INIT (0xFF)
#define Port_PDR_PORTB_INIT (0xF9)
#define Port_PDR_PORTC_INIT (0x7F)
#define Port_PDR_PORTD_INIT (0xFD)
#define Port_PDR_PORTE_INIT (0x38)
#define Port_PDR_PORTF_INIT (0xFF)
#define Port_PDR_PORTG_INIT (0xFF)
#define Port_PDR_PORTJ_INIT (0xFF)

/* PMR初期設定 */
#define Port_PMR_PORT0_INIT (0x00)
#define Port_PMR_PORT1_INIT (0x4C)
#define Port_PMR_PORT2_INIT (0x42)
#define Port_PMR_PORT3_INIT (0x1D)
#define Port_PMR_PORT4_INIT (0x00)
#define Port_PMR_PORT5_INIT (0x00)
#define Port_PMR_PORT6_INIT (0x00)
#define Port_PMR_PORT7_INIT (0x00)
#define Port_PMR_PORT8_INIT (0x00)
#define Port_PMR_PORT9_INIT (0x00)
#define Port_PMR_PORTA_INIT (0x2A)
#define Port_PMR_PORTB_INIT (0x08)
#define Port_PMR_PORTC_INIT (0x20)
#define Port_PMR_PORTD_INIT (0x00)
#define Port_PMR_PORTE_INIT (0x08)
#define Port_PMR_PORTF_INIT (0x00)
#define Port_PMR_PORTG_INIT (0x00)
#define Port_PMR_PORTJ_INIT (0x00)

/* ODR0初期設定 */
#define Port_ODR0_PORT0_INIT (0x00)
#define Port_ODR0_PORT1_INIT (0x00)
#define Port_ODR0_PORT2_INIT (0x00)
#define Port_ODR0_PORT3_INIT (0x00)
#define Port_ODR0_PORT4_INIT (0x00)
#define Port_ODR0_PORT5_INIT (0x00)
#define Port_ODR0_PORT6_INIT (0x00)
#define Port_ODR0_PORT7_INIT (0x00)
#define Port_ODR0_PORT8_INIT (0x00)
#define Port_ODR0_PORT9_INIT (0x00)
#define Port_ODR0_PORTA_INIT (0x00)
#define Port_ODR0_PORTB_INIT (0x00)
#define Port_ODR0_PORTC_INIT (0x00)
#define Port_ODR0_PORTD_INIT (0x00)
#define Port_ODR0_PORTE_INIT (0x00)
#define Port_ODR0_PORTF_INIT (0x00)
#define Port_ODR0_PORTG_INIT (0x00)
#define Port_ODR0_PORTJ_INIT (0x00)

/* ODR1初期設定 */
#define Port_ODR1_PORT0_INIT (0x00)
#define Port_ODR1_PORT1_INIT (0x00)
#define Port_ODR1_PORT2_INIT (0x00)
#define Port_ODR1_PORT3_INIT (0x00)
#define Port_ODR1_PORT4_INIT (0x00)
#define Port_ODR1_PORT5_INIT (0x00)
#define Port_ODR1_PORT6_INIT (0x00)
#define Port_ODR1_PORT7_INIT (0x00)
#define Port_ODR1_PORT8_INIT (0x00)
#define Port_ODR1_PORT9_INIT (0x00)
#define Port_ODR1_PORTA_INIT (0x00)
#define Port_ODR1_PORTB_INIT (0x00)
#define Port_ODR1_PORTC_INIT (0x00)
#define Port_ODR1_PORTD_INIT (0x00)
#define Port_ODR1_PORTE_INIT (0x00)
#define Port_ODR1_PORTF_INIT (0x00)
#define Port_ODR1_PORTG_INIT (0x00)
#define Port_ODR1_PORTJ_INIT (0x00)

/* PCR初期設定 */
#define Port_PCR_PORT0_INIT (0x00)
#define Port_PCR_PORT1_INIT (0x00)
#define Port_PCR_PORT2_INIT (0x80)
#define Port_PCR_PORT3_INIT (0x09)
#define Port_PCR_PORT4_INIT (0x00)
#define Port_PCR_PORT5_INIT (0x00)
#define Port_PCR_PORT6_INIT (0x00)
#define Port_PCR_PORT7_INIT (0x00)
#define Port_PCR_PORT8_INIT (0x00)
#define Port_PCR_PORT9_INIT (0x00)
#define Port_PCR_PORTA_INIT (0x00)
#define Port_PCR_PORTB_INIT (0x00)
#define Port_PCR_PORTC_INIT (0x00)
#define Port_PCR_PORTD_INIT (0x00)
#define Port_PCR_PORTE_INIT (0x07)
#define Port_PCR_PORTF_INIT (0x00)
#define Port_PCR_PORTG_INIT (0x00)
#define Port_PCR_PORTJ_INIT (0x00)

/* DSCR初期設定 */
#define Port_DSCR_PORT0_INIT (0x00)
#define Port_DSCR_PORT1_INIT (0x00)
#define Port_DSCR_PORT2_INIT (0x00)
/* PORT3.DSCRなし */
/* PORT4.DSCRなし */
#define Port_DSCR_PORT5_INIT (0x00)
/* PORT6.DSCRなし */
#define Port_DSCR_PORT7_INIT (0x00)
#define Port_DSCR_PORT8_INIT (0x00)
#define Port_DSCR_PORT9_INIT (0x00)
#define Port_DSCR_PORTA_INIT (0x00)
#define Port_DSCR_PORTB_INIT (0x00)
#define Port_DSCR_PORTC_INIT (0x00)
#define Port_DSCR_PORTD_INIT (0x00)
#define Port_DSCR_PORTE_INIT (0x00)
/* PORTF.DSCRなし */
#define Port_DSCR_PORTG_INIT (0x00)
#define Port_DSCR_PORTJ_INIT (0x00)

/* DSCR2初期設定 */
#define Port_DSCR2_PORT0_INIT (0x00)
#define Port_DSCR2_PORT1_INIT (0x00)
#define Port_DSCR2_PORT2_INIT (0x00)
#define Port_DSCR2_PORT3_INIT (0x00)
/* PORT4.DSCR2なし */
#define Port_DSCR2_PORT5_INIT (0x00)
/* PORT6.DSCR2なし */
#define Port_DSCR2_PORT7_INIT (0x00)
#define Port_DSCR2_PORT8_INIT (0x00)
#define Port_DSCR2_PORT9_INIT (0x00)
#define Port_DSCR2_PORTA_INIT (0x00)
#define Port_DSCR2_PORTB_INIT (0x00)
#define Port_DSCR2_PORTC_INIT (0x00)
#define Port_DSCR2_PORTD_INIT (0x00)
#define Port_DSCR2_PORTE_INIT (0x00)
/* PORTF.DSCR2なし */
#define Port_DSCR2_PORTG_INIT (0x00)
#define Port_DSCR2_PORTJ_INIT (0x00)


/**
 * @brief ポートの初期化を行う
 */
void Port_Init(void)
{
    /* 周辺機能モードを設定 */
    /* レジスタプロテクトを解除 */
    Mcu_SFR_Write(MPC.PWPR.BIT.B0WI, FALSE);
    Mcu_SFR_Write(MPC.PWPR.BIT.PFSWE, TRUE);

    /* Pin1:AVCC1*/
    /* Pin2:EMLE*/
    /* Pin3:AVSS1*/
    Mcu_SFR_Write(MPC.PJ3PFS.BYTE, 0x00);    /* Pin4:PJ3*/
    /* Pin5:VCL*/
    /* Pin6:VBATT*/
    /* Pin7:MD/FINED*/
    /* Pin8:XCIN*/
    /* Pin9:XCOUT*/
    /* Pin10:RES#*/
    /* Pin11:P37*/
    /* Pin12:VSS*/
    /* Pin13:P36*/
    /* Pin14:VCC*/
    /* Pin15:P35*/
    Mcu_SFR_Write(MPC.P34PFS.BYTE, 0x01);    /* Pin16:P34*/
    Mcu_SFR_Write(MPC.P33PFS.BYTE, 0x0A);    /* Pin17:P33*/
    Mcu_SFR_Write(MPC.P32PFS.BYTE, 0x0A);    /* Pin18:P32*/
    Mcu_SFR_Write(MPC.P31PFS.BYTE, 0x00);    /* Pin19:P31*/
    Mcu_SFR_Write(MPC.P30PFS.BYTE, 0x0A);    /* Pin20:P30*/
    Mcu_SFR_Write(MPC.P27PFS.BYTE, 0x00);    /* Pin21:P27*/
    Mcu_SFR_Write(MPC.P26PFS.BYTE, 0x0A);    /* Pin22:P26*/
    Mcu_SFR_Write(MPC.P25PFS.BYTE, 0x00);    /* Pin23:P25*/
    Mcu_SFR_Write(MPC.P24PFS.BYTE, 0x00);    /* Pin24:P24*/
    Mcu_SFR_Write(MPC.P23PFS.BYTE, 0x00);    /* Pin25:P23*/
    Mcu_SFR_Write(MPC.P22PFS.BYTE, 0x00);    /* Pin26:P22*/
    Mcu_SFR_Write(MPC.P21PFS.BYTE, 0x03);    /* Pin27:P21*/
    Mcu_SFR_Write(MPC.P20PFS.BYTE, 0x00);    /* Pin28:P20*/
    Mcu_SFR_Write(MPC.P17PFS.BYTE, 0x00);    /* Pin29:P17*/
    Mcu_SFR_Write(MPC.P16PFS.BYTE, 0x03);    /* Pin30:P16*/
    Mcu_SFR_Write(MPC.P15PFS.BYTE, 0x00);    /* Pin31:P15*/
    Mcu_SFR_Write(MPC.P14PFS.BYTE, 0x00);    /* Pin32:P14*/
    Mcu_SFR_Write(MPC.P13PFS.BYTE, 0x0F);    /* Pin33:P13*/
    Mcu_SFR_Write(MPC.P12PFS.BYTE, 0x0F);    /* Pin34:P12*/
    /* Pin35:VCC_USB*/
    /* Pin36:USB0_DM*/
    /* Pin37:USB0_DP*/
    /* Pin38:VSS_USB*/
    Mcu_SFR_Write(MPC.P55PFS.BYTE, 0x00);    /* Pin39:P55*/
    Mcu_SFR_Write(MPC.P54PFS.BYTE, 0x00);    /* Pin40:P54*/
    /* Pin41:P53*/
    Mcu_SFR_Write(MPC.P52PFS.BYTE, 0x00);    /* Pin42:P52*/
    Mcu_SFR_Write(MPC.P51PFS.BYTE, 0x00);    /* Pin43:P51*/
    Mcu_SFR_Write(MPC.P50PFS.BYTE, 0x00);    /* Pin44:P50*/
    Mcu_SFR_Write(MPC.PC7PFS.BYTE, 0x00);    /* Pin45:PC7*/
    Mcu_SFR_Write(MPC.PC6PFS.BYTE, 0x00);    /* Pin46:PC6*/
    Mcu_SFR_Write(MPC.PC5PFS.BYTE, 0x01);    /* Pin47:PC5*/
    Mcu_SFR_Write(MPC.PC4PFS.BYTE, 0x00);    /* Pin48:PC4*/
    Mcu_SFR_Write(MPC.PC3PFS.BYTE, 0x00);    /* Pin49:PC3*/
    Mcu_SFR_Write(MPC.PC2PFS.BYTE, 0x00);    /* Pin50:PC2*/
    Mcu_SFR_Write(MPC.PC1PFS.BYTE, 0x00);    /* Pin51:PC1*/
    Mcu_SFR_Write(MPC.PC0PFS.BYTE, 0x00);    /* Pin52:PC0*/
    Mcu_SFR_Write(MPC.PB7PFS.BYTE, 0x03);    /* Pin53:PB7*/
    Mcu_SFR_Write(MPC.PB6PFS.BYTE, 0x03);    /* Pin54:PB6*/
    Mcu_SFR_Write(MPC.PB5PFS.BYTE, 0x03);    /* Pin55:PB5*/
    Mcu_SFR_Write(MPC.PB4PFS.BYTE, 0x03);    /* Pin56:PB4*/
    Mcu_SFR_Write(MPC.PB3PFS.BYTE, 0x02);    /* Pin57:PB3*/
    Mcu_SFR_Write(MPC.PB2PFS.BYTE, 0x00);    /* Pin58:PB2*/
    Mcu_SFR_Write(MPC.PB1PFS.BYTE, 0x00);    /* Pin59:PB1*/
    /* Pin60:VCC*/
    Mcu_SFR_Write(MPC.PB0PFS.BYTE, 0x00);    /* Pin61:PB0*/
    /* Pin62:VSS*/
    Mcu_SFR_Write(MPC.PA7PFS.BYTE, 0x03);    /* Pin63:PA7*/
    Mcu_SFR_Write(MPC.PA6PFS.BYTE, 0x03);    /* Pin64:PA6*/
    Mcu_SFR_Write(MPC.PA5PFS.BYTE, 0x08);    /* Pin65:PA5*/
    Mcu_SFR_Write(MPC.PA4PFS.BYTE, 0x00);    /* Pin66:PA4*/
    Mcu_SFR_Write(MPC.PA3PFS.BYTE, 0x01);    /* Pin67:PA3*/
    Mcu_SFR_Write(MPC.PA2PFS.BYTE, 0x00);    /* Pin68:PA2*/
    Mcu_SFR_Write(MPC.PA1PFS.BYTE, 0x01);    /* Pin69:PA1*/
    Mcu_SFR_Write(MPC.PA0PFS.BYTE, 0x00);    /* Pin70:PA0*/
    Mcu_SFR_Write(MPC.PE7PFS.BYTE, 0x80);    /* Pin71:PE7*/
    Mcu_SFR_Write(MPC.PE6PFS.BYTE, 0x80);    /* Pin72:PE6*/
    Mcu_SFR_Write(MPC.PE5PFS.BYTE, 0x00);    /* Pin73:PE5*/
    Mcu_SFR_Write(MPC.PE4PFS.BYTE, 0x00);    /* Pin74:PE4*/
    Mcu_SFR_Write(MPC.PE3PFS.BYTE, 0x01);    /* Pin75:PE3*/
    Mcu_SFR_Write(MPC.PE2PFS.BYTE, 0x00);    /* Pin76:PE2*/
    Mcu_SFR_Write(MPC.PE1PFS.BYTE, 0x00);    /* Pin77:PE1*/
    Mcu_SFR_Write(MPC.PE0PFS.BYTE, 0x00);    /* Pin78:PE0*/
    Mcu_SFR_Write(MPC.PD7PFS.BYTE, 0x00);    /* Pin79:PD7*/
    Mcu_SFR_Write(MPC.PD6PFS.BYTE, 0x00);    /* Pin80:PD6*/
    Mcu_SFR_Write(MPC.PD5PFS.BYTE, 0x00);    /* Pin81:PD5*/
    Mcu_SFR_Write(MPC.PD4PFS.BYTE, 0x00);    /* Pin82:PD4*/
    Mcu_SFR_Write(MPC.PD3PFS.BYTE, 0x00);    /* Pin83:PD3*/
    Mcu_SFR_Write(MPC.PD2PFS.BYTE, 0x00);    /* Pin84:PD2*/
    Mcu_SFR_Write(MPC.PD1PFS.BYTE, 0x80);    /* Pin85:PD1*/
    Mcu_SFR_Write(MPC.PD0PFS.BYTE, 0x00);    /* Pin86:PD0*/
    Mcu_SFR_Write(MPC.P47PFS.BYTE, 0x00);    /* Pin87:P47*/
    Mcu_SFR_Write(MPC.P46PFS.BYTE, 0x80);    /* Pin88:P46*/
    Mcu_SFR_Write(MPC.P45PFS.BYTE, 0x80);    /* Pin89:P45*/
    Mcu_SFR_Write(MPC.P44PFS.BYTE, 0x00);    /* Pin90:P44*/
    Mcu_SFR_Write(MPC.P43PFS.BYTE, 0x00);    /* Pin91:P43*/
    Mcu_SFR_Write(MPC.P42PFS.BYTE, 0x80);    /* Pin92:P42*/
    Mcu_SFR_Write(MPC.P41PFS.BYTE, 0x80);    /* Pin93:P41*/
    /* Pin94:VREFL0*/
    Mcu_SFR_Write(MPC.P40PFS.BYTE, 0x00);    /* Pin95:P40*/
    /* Pin96:VREFH0*/
    /* Pin97:AVCC0*/
    Mcu_SFR_Write(MPC.P07PFS.BYTE, 0x00);    /* Pin98:P07*/
    /* Pin99:AVSS0*/
    Mcu_SFR_Write(MPC.P05PFS.BYTE, 0x00);    /* Pin100:P05*/
    /* Pin-:P06*/
    /* Pin-:P04*/
    /* Pin-:P03*/
    /* Pin-:P02*/
    /* Pin-:P01*/
    /* Pin-:P00*/
    /* Pin-:P11*/
    /* Pin-:P10*/
    /* Pin-:P57*/
    /* Pin-:P56*/
    /* Pin-:P67*/
    /* Pin-:P66*/
    /* Pin-:P65*/
    /* Pin-:P64*/
    /* Pin-:P63*/
    /* Pin-:P62*/
    /* Pin-:P61*/
    /* Pin-:P60*/
    /* Pin-:P77*/
    /* Pin-:P76*/
    /* Pin-:P75*/
    /* Pin-:P74*/
    /* Pin-:P73*/
    /* Pin-:P72*/
    /* Pin-:P71*/
    /* Pin-:P70*/
    /* Pin-:P87*/
    /* Pin-:P86*/
    /* Pin-:P85*/
    /* Pin-:P84*/
    /* Pin-:P83*/
    /* Pin-:P82*/
    /* Pin-:P81*/
    /* Pin-:P80*/
    /* Pin-:P97*/
    /* Pin-:P96*/
    /* Pin-:P95*/
    /* Pin-:P94*/
    /* Pin-:P93*/
    /* Pin-:P92*/
    /* Pin-:P91*/
    /* Pin-:P90*/
    /* Pin-:PF7*/
    /* Pin-:PF6*/
    /* Pin-:PF5*/
    /* Pin-:PF4*/
    /* Pin-:PF3*/
    /* Pin-:PF2*/
    /* Pin-:PF1*/
    /* Pin-:PF0*/
    /* Pin-:PG7*/
    /* Pin-:PG6*/
    /* Pin-:PG5*/
    /* Pin-:PG4*/
    /* Pin-:PG3*/
    /* Pin-:PG2*/
    /* Pin-:PG1*/
    /* Pin-:PG0*/
    /* Pin-:PJ7*/
    /* Pin-:PJ6*/
    /* Pin-:PJ5*/
    /* Pin-:PJ4*/
    /* Pin-:PJ2*/
    /* Pin-:PJ1*/
    /* Pin-:PJ0*/
    /* Pin-:Pxx*/

    /* レジスタプロテクト */
    Mcu_SFR_Write(MPC.PWPR.BIT.PFSWE, FALSE);
    Mcu_SFR_Write(MPC.PWPR.BIT.B0WI, TRUE);


    /* 駆動能力設定 */
    Mcu_SFR_Write(PORT0.DSCR.BYTE, Port_DSCR_PORT0_INIT);
    Mcu_SFR_Write(PORT1.DSCR.BYTE, Port_DSCR_PORT1_INIT);
    Mcu_SFR_Write(PORT2.DSCR.BYTE, Port_DSCR_PORT2_INIT);
    /* PORT3.DSCRなし */
    /* PORT4.DSCRなし */
    Mcu_SFR_Write(PORT5.DSCR.BYTE, Port_DSCR_PORT5_INIT);
    /* PORT6.DSCRなし */
    Mcu_SFR_Write(PORT7.DSCR.BYTE, Port_DSCR_PORT7_INIT);
    Mcu_SFR_Write(PORT8.DSCR.BYTE, Port_DSCR_PORT8_INIT);
    Mcu_SFR_Write(PORT9.DSCR.BYTE, Port_DSCR_PORT9_INIT);
    Mcu_SFR_Write(PORTA.DSCR.BYTE, Port_DSCR_PORTA_INIT);
    Mcu_SFR_Write(PORTB.DSCR.BYTE, Port_DSCR_PORTB_INIT);
    Mcu_SFR_Write(PORTC.DSCR.BYTE, Port_DSCR_PORTC_INIT);
    Mcu_SFR_Write(PORTD.DSCR.BYTE, Port_DSCR_PORTD_INIT);
    Mcu_SFR_Write(PORTE.DSCR.BYTE, Port_DSCR_PORTE_INIT);
    /* PORTF.DSCRなし */
    Mcu_SFR_Write(PORTG.DSCR.BYTE, Port_DSCR_PORTG_INIT);
    Mcu_SFR_Write(PORTJ.DSCR.BYTE, Port_DSCR_PORTJ_INIT);
    Mcu_SFR_Write(PORT0.DSCR2.BYTE, Port_DSCR2_PORT0_INIT);
    Mcu_SFR_Write(PORT1.DSCR2.BYTE, Port_DSCR2_PORT1_INIT);
    Mcu_SFR_Write(PORT2.DSCR2.BYTE, Port_DSCR2_PORT2_INIT);
    Mcu_SFR_Write(PORT3.DSCR2.BYTE, Port_DSCR2_PORT3_INIT);
    /* PORT4.DSCR2なし */
    Mcu_SFR_Write(PORT5.DSCR2.BYTE, Port_DSCR2_PORT5_INIT);
    /* PORT6.DSCR2なし */
    Mcu_SFR_Write(PORT7.DSCR2.BYTE, Port_DSCR2_PORT7_INIT);
    Mcu_SFR_Write(PORT8.DSCR2.BYTE, Port_DSCR2_PORT8_INIT);
    Mcu_SFR_Write(PORT9.DSCR2.BYTE, Port_DSCR2_PORT9_INIT);
    Mcu_SFR_Write(PORTA.DSCR2.BYTE, Port_DSCR2_PORTA_INIT);
    Mcu_SFR_Write(PORTB.DSCR2.BYTE, Port_DSCR2_PORTB_INIT);
    Mcu_SFR_Write(PORTC.DSCR2.BYTE, Port_DSCR2_PORTC_INIT);
    Mcu_SFR_Write(PORTD.DSCR2.BYTE, Port_DSCR2_PORTD_INIT);
    Mcu_SFR_Write(PORTE.DSCR2.BYTE, Port_DSCR2_PORTE_INIT);
    /* PORTF.DSCR2なし */
    Mcu_SFR_Write(PORTG.DSCR2.BYTE, Port_DSCR2_PORTG_INIT);
    Mcu_SFR_Write(PORTJ.DSCR2.BYTE, Port_DSCR2_PORTJ_INIT);


    /* 入出力レベル設定 */
    Mcu_SFR_Write(PORT0.PODR.BYTE, Port_PODR_PORT0_INIT);
    Mcu_SFR_Write(PORT1.PODR.BYTE, Port_PODR_PORT1_INIT);
    Mcu_SFR_Write(PORT2.PODR.BYTE, Port_PODR_PORT2_INIT);
    Mcu_SFR_Write(PORT3.PODR.BYTE, Port_PODR_PORT3_INIT);
    Mcu_SFR_Write(PORT4.PODR.BYTE, Port_PODR_PORT4_INIT);
    Mcu_SFR_Write(PORT5.PODR.BYTE, Port_PODR_PORT5_INIT);
    Mcu_SFR_Write(PORT6.PODR.BYTE, Port_PODR_PORT6_INIT);
    Mcu_SFR_Write(PORT7.PODR.BYTE, Port_PODR_PORT7_INIT);
    Mcu_SFR_Write(PORT8.PODR.BYTE, Port_PODR_PORT8_INIT);
    Mcu_SFR_Write(PORT9.PODR.BYTE, Port_PODR_PORT9_INIT);
    Mcu_SFR_Write(PORTA.PODR.BYTE, Port_PODR_PORTA_INIT);
    Mcu_SFR_Write(PORTB.PODR.BYTE, Port_PODR_PORTB_INIT);
    Mcu_SFR_Write(PORTC.PODR.BYTE, Port_PODR_PORTC_INIT);
    Mcu_SFR_Write(PORTD.PODR.BYTE, Port_PODR_PORTD_INIT);
    Mcu_SFR_Write(PORTE.PODR.BYTE, Port_PODR_PORTE_INIT);
    Mcu_SFR_Write(PORTF.PODR.BYTE, Port_PODR_PORTF_INIT);
    Mcu_SFR_Write(PORTG.PODR.BYTE, Port_PODR_PORTG_INIT);
    Mcu_SFR_Write(PORTJ.PODR.BYTE, Port_PODR_PORTJ_INIT);


    /* オープンドレーン設定 */
    Mcu_SFR_Write(PORT0.ODR0.BYTE, Port_ODR0_PORT0_INIT);
    Mcu_SFR_Write(PORT1.ODR0.BYTE, Port_ODR0_PORT1_INIT);
    Mcu_SFR_Write(PORT2.ODR0.BYTE, Port_ODR0_PORT2_INIT);
    Mcu_SFR_Write(PORT3.ODR0.BYTE, Port_ODR0_PORT3_INIT);
    Mcu_SFR_Write(PORT4.ODR0.BYTE, Port_ODR0_PORT4_INIT);
    Mcu_SFR_Write(PORT5.ODR0.BYTE, Port_ODR0_PORT5_INIT);
    Mcu_SFR_Write(PORT6.ODR0.BYTE, Port_ODR0_PORT6_INIT);
    Mcu_SFR_Write(PORT7.ODR0.BYTE, Port_ODR0_PORT7_INIT);
    Mcu_SFR_Write(PORT8.ODR0.BYTE, Port_ODR0_PORT8_INIT);
    Mcu_SFR_Write(PORT9.ODR0.BYTE, Port_ODR0_PORT9_INIT);
    Mcu_SFR_Write(PORTA.ODR0.BYTE, Port_ODR0_PORTA_INIT);
    Mcu_SFR_Write(PORTB.ODR0.BYTE, Port_ODR0_PORTB_INIT);
    Mcu_SFR_Write(PORTC.ODR0.BYTE, Port_ODR0_PORTC_INIT);
    Mcu_SFR_Write(PORTD.ODR0.BYTE, Port_ODR0_PORTD_INIT);
    Mcu_SFR_Write(PORTE.ODR0.BYTE, Port_ODR0_PORTE_INIT);
    Mcu_SFR_Write(PORTF.ODR0.BYTE, Port_ODR0_PORTF_INIT);
    Mcu_SFR_Write(PORTG.ODR0.BYTE, Port_ODR0_PORTG_INIT);
    Mcu_SFR_Write(PORTJ.ODR0.BYTE, Port_ODR0_PORTJ_INIT);
    Mcu_SFR_Write(PORT0.ODR1.BYTE, Port_ODR1_PORT0_INIT);
    Mcu_SFR_Write(PORT1.ODR1.BYTE, Port_ODR1_PORT1_INIT);
    Mcu_SFR_Write(PORT2.ODR1.BYTE, Port_ODR1_PORT2_INIT);
    Mcu_SFR_Write(PORT3.ODR1.BYTE, Port_ODR1_PORT3_INIT);
    Mcu_SFR_Write(PORT4.ODR1.BYTE, Port_ODR1_PORT4_INIT);
    Mcu_SFR_Write(PORT5.ODR1.BYTE, Port_ODR1_PORT5_INIT);
    Mcu_SFR_Write(PORT6.ODR1.BYTE, Port_ODR1_PORT6_INIT);
    Mcu_SFR_Write(PORT7.ODR1.BYTE, Port_ODR1_PORT7_INIT);
    Mcu_SFR_Write(PORT8.ODR1.BYTE, Port_ODR1_PORT8_INIT);
    Mcu_SFR_Write(PORT9.ODR1.BYTE, Port_ODR1_PORT9_INIT);
    Mcu_SFR_Write(PORTA.ODR1.BYTE, Port_ODR1_PORTA_INIT);
    Mcu_SFR_Write(PORTB.ODR1.BYTE, Port_ODR1_PORTB_INIT);
    Mcu_SFR_Write(PORTC.ODR1.BYTE, Port_ODR1_PORTC_INIT);
    Mcu_SFR_Write(PORTD.ODR1.BYTE, Port_ODR1_PORTD_INIT);
    Mcu_SFR_Write(PORTE.ODR1.BYTE, Port_ODR1_PORTE_INIT);
    Mcu_SFR_Write(PORTF.ODR1.BYTE, Port_ODR1_PORTF_INIT);
    Mcu_SFR_Write(PORTG.ODR1.BYTE, Port_ODR1_PORTG_INIT);
    Mcu_SFR_Write(PORTJ.ODR1.BYTE, Port_ODR1_PORTJ_INIT);


    /* プルアップ設定 */
    Mcu_SFR_Write(PORT0.PCR.BYTE, Port_PCR_PORT0_INIT);
    Mcu_SFR_Write(PORT1.PCR.BYTE, Port_PCR_PORT1_INIT);
    Mcu_SFR_Write(PORT2.PCR.BYTE, Port_PCR_PORT2_INIT);
    Mcu_SFR_Write(PORT3.PCR.BYTE, Port_PCR_PORT3_INIT);
    Mcu_SFR_Write(PORT4.PCR.BYTE, Port_PCR_PORT4_INIT);
    Mcu_SFR_Write(PORT5.PCR.BYTE, Port_PCR_PORT5_INIT);
    Mcu_SFR_Write(PORT6.PCR.BYTE, Port_PCR_PORT6_INIT);
    Mcu_SFR_Write(PORT7.PCR.BYTE, Port_PCR_PORT7_INIT);
    Mcu_SFR_Write(PORT8.PCR.BYTE, Port_PCR_PORT8_INIT);
    Mcu_SFR_Write(PORT9.PCR.BYTE, Port_PCR_PORT9_INIT);
    Mcu_SFR_Write(PORTA.PCR.BYTE, Port_PCR_PORTA_INIT);
    Mcu_SFR_Write(PORTB.PCR.BYTE, Port_PCR_PORTB_INIT);
    Mcu_SFR_Write(PORTC.PCR.BYTE, Port_PCR_PORTC_INIT);
    Mcu_SFR_Write(PORTD.PCR.BYTE, Port_PCR_PORTD_INIT);
    Mcu_SFR_Write(PORTE.PCR.BYTE, Port_PCR_PORTE_INIT);
    Mcu_SFR_Write(PORTF.PCR.BYTE, Port_PCR_PORTF_INIT);
    Mcu_SFR_Write(PORTG.PCR.BYTE, Port_PCR_PORTG_INIT);
    Mcu_SFR_Write(PORTJ.PCR.BYTE, Port_PCR_PORTJ_INIT);


    /* 周辺機能を有効化 */
    Mcu_SFR_Write(PORT0.PMR.BYTE, Port_PMR_PORT0_INIT);
    Mcu_SFR_Write(PORT1.PMR.BYTE, Port_PMR_PORT1_INIT);
    Mcu_SFR_Write(PORT2.PMR.BYTE, Port_PMR_PORT2_INIT);
    Mcu_SFR_Write(PORT3.PMR.BYTE, Port_PMR_PORT3_INIT);
    Mcu_SFR_Write(PORT4.PMR.BYTE, Port_PMR_PORT4_INIT);
    Mcu_SFR_Write(PORT5.PMR.BYTE, Port_PMR_PORT5_INIT);
    Mcu_SFR_Write(PORT6.PMR.BYTE, Port_PMR_PORT6_INIT);
    Mcu_SFR_Write(PORT7.PMR.BYTE, Port_PMR_PORT7_INIT);
    Mcu_SFR_Write(PORT8.PMR.BYTE, Port_PMR_PORT8_INIT);
    Mcu_SFR_Write(PORT9.PMR.BYTE, Port_PMR_PORT9_INIT);
    Mcu_SFR_Write(PORTA.PMR.BYTE, Port_PMR_PORTA_INIT);
    Mcu_SFR_Write(PORTB.PMR.BYTE, Port_PMR_PORTB_INIT);
    Mcu_SFR_Write(PORTC.PMR.BYTE, Port_PMR_PORTC_INIT);
    Mcu_SFR_Write(PORTD.PMR.BYTE, Port_PMR_PORTD_INIT);
    Mcu_SFR_Write(PORTE.PMR.BYTE, Port_PMR_PORTE_INIT);
    Mcu_SFR_Write(PORTF.PMR.BYTE, Port_PMR_PORTF_INIT);
    Mcu_SFR_Write(PORTG.PMR.BYTE, Port_PMR_PORTG_INIT);
    Mcu_SFR_Write(PORTJ.PMR.BYTE, Port_PMR_PORTJ_INIT);


    /* 入出力方向を設定 */
    Mcu_SFR_Write(PORT0.PDR.BYTE, Port_PDR_PORT0_INIT);
    Mcu_SFR_Write(PORT1.PDR.BYTE, Port_PDR_PORT1_INIT);
    Mcu_SFR_Write(PORT2.PDR.BYTE, Port_PDR_PORT2_INIT);
    Mcu_SFR_Write(PORT3.PDR.BYTE, Port_PDR_PORT3_INIT);
    Mcu_SFR_Write(PORT4.PDR.BYTE, Port_PDR_PORT4_INIT);
    Mcu_SFR_Write(PORT5.PDR.BYTE, Port_PDR_PORT5_INIT);
    Mcu_SFR_Write(PORT6.PDR.BYTE, Port_PDR_PORT6_INIT);
    Mcu_SFR_Write(PORT7.PDR.BYTE, Port_PDR_PORT7_INIT);
    Mcu_SFR_Write(PORT8.PDR.BYTE, Port_PDR_PORT8_INIT);
    Mcu_SFR_Write(PORT9.PDR.BYTE, Port_PDR_PORT9_INIT);
    Mcu_SFR_Write(PORTA.PDR.BYTE, Port_PDR_PORTA_INIT);
    Mcu_SFR_Write(PORTB.PDR.BYTE, Port_PDR_PORTB_INIT);
    Mcu_SFR_Write(PORTC.PDR.BYTE, Port_PDR_PORTC_INIT);
    Mcu_SFR_Write(PORTD.PDR.BYTE, Port_PDR_PORTD_INIT);
    Mcu_SFR_Write(PORTE.PDR.BYTE, Port_PDR_PORTE_INIT);
    Mcu_SFR_Write(PORTF.PDR.BYTE, Port_PDR_PORTF_INIT);
    Mcu_SFR_Write(PORTG.PDR.BYTE, Port_PDR_PORTG_INIT);
    Mcu_SFR_Write(PORTJ.PDR.BYTE, Port_PDR_PORTJ_INIT);
}

