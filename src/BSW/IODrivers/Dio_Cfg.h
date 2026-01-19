/**
 * @file Dio_Cfg.h
 * @brief Digital IO入力を定義する
 */
#ifndef __Dio_Cfg_H
#define __Dio_Cfg_H


#ifdef __cplusplus
extern "C" {
#endif


#define Dio_Use_BitOperation (TRUE) /**<ポート書き込み時のRAM干渉対策有無 */

/* for Dio_ReadChannel */
/* Pin1:AVCC1*/
/* Pin2:EMLE*/
/* Pin3:AVSS1*/
#define Port_Cfg_Ch_Rd_PJ3 PORTJ.PIDR.BIT.B3
/* Pin5:VCL*/
/* Pin6:VBATT*/
/* Pin7:MD/FINED*/
/* Pin8:XCIN*/
/* Pin9:XCOUT*/
/* Pin10:RES#*/
#define Port_Cfg_Ch_Rd_P37 PORT3.PIDR.BIT.B7
/* Pin12:VSS*/
#define Port_Cfg_Ch_Rd_P36 PORT3.PIDR.BIT.B6
/* Pin14:VCC*/
#define Port_Cfg_Ch_Rd_P35 PORT3.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_P34 PORT3.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_P33 PORT3.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_P32 PORT3.PIDR.BIT.B2
#define Port_Cfg_Ch_Rd_P31 PORT3.PIDR.BIT.B1
#define Port_Cfg_Ch_Rd_P30 PORT3.PIDR.BIT.B0
#define Port_Cfg_Ch_Rd_P27 PORT2.PIDR.BIT.B7
#define Port_Cfg_Ch_Rd_P26 PORT2.PIDR.BIT.B6
#define Port_Cfg_Ch_Rd_P25 PORT2.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_P24 PORT2.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_P23 PORT2.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_P22 PORT2.PIDR.BIT.B2
#define Port_Cfg_Ch_Rd_P21 PORT2.PIDR.BIT.B1
#define Port_Cfg_Ch_Rd_P20 PORT2.PIDR.BIT.B0
#define Port_Cfg_Ch_Rd_P17 PORT1.PIDR.BIT.B7
#define Port_Cfg_Ch_Rd_P16 PORT1.PIDR.BIT.B6
#define Port_Cfg_Ch_Rd_P15 PORT1.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_P14 PORT1.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_P13 PORT1.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_P12 PORT1.PIDR.BIT.B2
/* Pin35:VCC_USB*/
/* Pin36:USB0_DM*/
/* Pin37:USB0_DP*/
/* Pin38:VSS_USB*/
#define Port_Cfg_Ch_Rd_P55 PORT5.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_P54 PORT5.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_P53 PORT5.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_P52 PORT5.PIDR.BIT.B2
#define Port_Cfg_Ch_Rd_P51 PORT5.PIDR.BIT.B1
#define Port_Cfg_Ch_Rd_P50 PORT5.PIDR.BIT.B0
#define Port_Cfg_Ch_Rd_PC7 PORTC.PIDR.BIT.B7
#define Port_Cfg_Ch_Rd_PC6 PORTC.PIDR.BIT.B6
#define Port_Cfg_Ch_Rd_PC5 PORTC.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_PC4 PORTC.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_PC3 PORTC.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_PC2 PORTC.PIDR.BIT.B2
#define Port_Cfg_Ch_Rd_PC1 PORTC.PIDR.BIT.B1
#define Port_Cfg_Ch_Rd_PC0 PORTC.PIDR.BIT.B0
#define Port_Cfg_Ch_Rd_PB7 PORTB.PIDR.BIT.B7
#define Port_Cfg_Ch_Rd_PB6 PORTB.PIDR.BIT.B6
#define Port_Cfg_Ch_Rd_PB5 PORTB.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_PB4 PORTB.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_PB3 PORTB.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_PB2 PORTB.PIDR.BIT.B2
#define Port_Cfg_Ch_Rd_PB1 PORTB.PIDR.BIT.B1
/* Pin60:VCC*/
#define Port_Cfg_Ch_Rd_PB0 PORTB.PIDR.BIT.B0
/* Pin62:VSS*/
#define Port_Cfg_Ch_Rd_PA7 PORTA.PIDR.BIT.B7
#define Port_Cfg_Ch_Rd_PA6 PORTA.PIDR.BIT.B6
#define Port_Cfg_Ch_Rd_PA5 PORTA.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_PA4 PORTA.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_PA3 PORTA.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_PA2 PORTA.PIDR.BIT.B2
#define Port_Cfg_Ch_Rd_PA1 PORTA.PIDR.BIT.B1
#define Port_Cfg_Ch_Rd_PA0 PORTA.PIDR.BIT.B0
#define Port_Cfg_Ch_Rd_PE7 PORTE.PIDR.BIT.B7
#define Port_Cfg_Ch_Rd_PE6 PORTE.PIDR.BIT.B6
#define Port_Cfg_Ch_Rd_PE5 PORTE.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_PE4 PORTE.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_PE3 PORTE.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_PE2 PORTE.PIDR.BIT.B2
#define Port_Cfg_Ch_Rd_PE1 PORTE.PIDR.BIT.B1
#define Port_Cfg_Ch_Rd_PE0 PORTE.PIDR.BIT.B0
#define Port_Cfg_Ch_Rd_PD7 PORTD.PIDR.BIT.B7
#define Port_Cfg_Ch_Rd_PD6 PORTD.PIDR.BIT.B6
#define Port_Cfg_Ch_Rd_PD5 PORTD.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_PD4 PORTD.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_PD3 PORTD.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_PD2 PORTD.PIDR.BIT.B2
#define Port_Cfg_Ch_Rd_PD1 PORTD.PIDR.BIT.B1
#define Port_Cfg_Ch_Rd_PD0 PORTD.PIDR.BIT.B0
#define Port_Cfg_Ch_Rd_P47 PORT4.PIDR.BIT.B7
#define Port_Cfg_Ch_Rd_P46 PORT4.PIDR.BIT.B6
#define Port_Cfg_Ch_Rd_P45 PORT4.PIDR.BIT.B5
#define Port_Cfg_Ch_Rd_P44 PORT4.PIDR.BIT.B4
#define Port_Cfg_Ch_Rd_P43 PORT4.PIDR.BIT.B3
#define Port_Cfg_Ch_Rd_P42 PORT4.PIDR.BIT.B2
#define Port_Cfg_Ch_Rd_P41 PORT4.PIDR.BIT.B1
/* Pin94:VREFL0*/
#define Port_Cfg_Ch_Rd_P40 PORT4.PIDR.BIT.B0
/* Pin96:VREFH0*/
/* Pin97:AVCC0*/
#define Port_Cfg_Ch_Rd_P07 PORT0.PIDR.BIT.B7
/* Pin99:AVSS0*/
#define Port_Cfg_Ch_Rd_P05 PORT0.PIDR.BIT.B5
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

/* for Dio_WriteChannel */
#if Dio_Use_BitOperation == FALSE
/* ビットアクセス命令未使用時 */
/* Pin1:AVCC1*/
/* Pin2:EMLE*/
/* Pin3:AVSS1*/
#define Port_Cfg_Ch_Wr_PJ3 PORTJ.PODR.BIT.B3
/* Pin5:VCL*/
/* Pin6:VBATT*/
/* Pin7:MD/FINED*/
/* Pin8:XCIN*/
/* Pin9:XCOUT*/
/* Pin10:RES#*/
#define Port_Cfg_Ch_Wr_P37 PORT3.PODR.BIT.B7
/* Pin12:VSS*/
#define Port_Cfg_Ch_Wr_P36 PORT3.PODR.BIT.B6
/* Pin14:VCC*/
#define Port_Cfg_Ch_Wr_P35 PORT3.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_P34 PORT3.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_P33 PORT3.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_P32 PORT3.PODR.BIT.B2
#define Port_Cfg_Ch_Wr_P31 PORT3.PODR.BIT.B1
#define Port_Cfg_Ch_Wr_P30 PORT3.PODR.BIT.B0
#define Port_Cfg_Ch_Wr_P27 PORT2.PODR.BIT.B7
#define Port_Cfg_Ch_Wr_P26 PORT2.PODR.BIT.B6
#define Port_Cfg_Ch_Wr_P25 PORT2.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_P24 PORT2.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_P23 PORT2.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_P22 PORT2.PODR.BIT.B2
#define Port_Cfg_Ch_Wr_P21 PORT2.PODR.BIT.B1
#define Port_Cfg_Ch_Wr_P20 PORT2.PODR.BIT.B0
#define Port_Cfg_Ch_Wr_P17 PORT1.PODR.BIT.B7
#define Port_Cfg_Ch_Wr_P16 PORT1.PODR.BIT.B6
#define Port_Cfg_Ch_Wr_P15 PORT1.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_P14 PORT1.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_P13 PORT1.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_P12 PORT1.PODR.BIT.B2
/* Pin35:VCC_USB*/
/* Pin36:USB0_DM*/
/* Pin37:USB0_DP*/
/* Pin38:VSS_USB*/
#define Port_Cfg_Ch_Wr_P55 PORT5.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_P54 PORT5.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_P53 PORT5.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_P52 PORT5.PODR.BIT.B2
#define Port_Cfg_Ch_Wr_P51 PORT5.PODR.BIT.B1
#define Port_Cfg_Ch_Wr_P50 PORT5.PODR.BIT.B0
#define Port_Cfg_Ch_Wr_PC7 PORTC.PODR.BIT.B7
#define Port_Cfg_Ch_Wr_PC6 PORTC.PODR.BIT.B6
#define Port_Cfg_Ch_Wr_PC5 PORTC.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_PC4 PORTC.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_PC3 PORTC.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_PC2 PORTC.PODR.BIT.B2
#define Port_Cfg_Ch_Wr_PC1 PORTC.PODR.BIT.B1
#define Port_Cfg_Ch_Wr_PC0 PORTC.PODR.BIT.B0
#define Port_Cfg_Ch_Wr_PB7 PORTB.PODR.BIT.B7
#define Port_Cfg_Ch_Wr_PB6 PORTB.PODR.BIT.B6
#define Port_Cfg_Ch_Wr_PB5 PORTB.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_PB4 PORTB.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_PB3 PORTB.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_PB2 PORTB.PODR.BIT.B2
#define Port_Cfg_Ch_Wr_PB1 PORTB.PODR.BIT.B1
/* Pin60:VCC*/
#define Port_Cfg_Ch_Wr_PB0 PORTB.PODR.BIT.B0
/* Pin62:VSS*/
#define Port_Cfg_Ch_Wr_PA7 PORTA.PODR.BIT.B7
#define Port_Cfg_Ch_Wr_PA6 PORTA.PODR.BIT.B6
#define Port_Cfg_Ch_Wr_PA5 PORTA.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_PA4 PORTA.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_PA3 PORTA.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_PA2 PORTA.PODR.BIT.B2
#define Port_Cfg_Ch_Wr_PA1 PORTA.PODR.BIT.B1
#define Port_Cfg_Ch_Wr_PA0 PORTA.PODR.BIT.B0
#define Port_Cfg_Ch_Wr_PE7 PORTE.PODR.BIT.B7
#define Port_Cfg_Ch_Wr_PE6 PORTE.PODR.BIT.B6
#define Port_Cfg_Ch_Wr_PE5 PORTE.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_PE4 PORTE.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_PE3 PORTE.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_PE2 PORTE.PODR.BIT.B2
#define Port_Cfg_Ch_Wr_PE1 PORTE.PODR.BIT.B1
#define Port_Cfg_Ch_Wr_PE0 PORTE.PODR.BIT.B0
#define Port_Cfg_Ch_Wr_PD7 PORTD.PODR.BIT.B7
#define Port_Cfg_Ch_Wr_PD6 PORTD.PODR.BIT.B6
#define Port_Cfg_Ch_Wr_PD5 PORTD.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_PD4 PORTD.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_PD3 PORTD.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_PD2 PORTD.PODR.BIT.B2
#define Port_Cfg_Ch_Wr_PD1 PORTD.PODR.BIT.B1
#define Port_Cfg_Ch_Wr_PD0 PORTD.PODR.BIT.B0
#define Port_Cfg_Ch_Wr_P47 PORT4.PODR.BIT.B7
#define Port_Cfg_Ch_Wr_P46 PORT4.PODR.BIT.B6
#define Port_Cfg_Ch_Wr_P45 PORT4.PODR.BIT.B5
#define Port_Cfg_Ch_Wr_P44 PORT4.PODR.BIT.B4
#define Port_Cfg_Ch_Wr_P43 PORT4.PODR.BIT.B3
#define Port_Cfg_Ch_Wr_P42 PORT4.PODR.BIT.B2
#define Port_Cfg_Ch_Wr_P41 PORT4.PODR.BIT.B1
/* Pin94:VREFL0*/
#define Port_Cfg_Ch_Wr_P40 PORT4.PODR.BIT.B0
/* Pin96:VREFH0*/
/* Pin97:AVCC0*/
#define Port_Cfg_Ch_Wr_P07 PORT0.PODR.BIT.B7
/* Pin99:AVSS0*/
#define Port_Cfg_Ch_Wr_P05 PORT0.PODR.BIT.B5
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

#else
/* ビットアクセス命令使用時 */

/* Byte位置定義 */
/* Pin1:AVCC1*/
/* Pin2:EMLE*/
/* Pin3:AVSS1*/
#define Port_Cfg_Ch_Wr_Byte_PJ3 PORTJ.PODR.BYTE
/* Pin5:VCL*/
/* Pin6:VBATT*/
/* Pin7:MD/FINED*/
/* Pin8:XCIN*/
/* Pin9:XCOUT*/
/* Pin10:RES#*/
#define Port_Cfg_Ch_Wr_Byte_P37 PORT3.PODR.BYTE
/* Pin12:VSS*/
#define Port_Cfg_Ch_Wr_Byte_P36 PORT3.PODR.BYTE
/* Pin14:VCC*/
#define Port_Cfg_Ch_Wr_Byte_P35 PORT3.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P34 PORT3.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P33 PORT3.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P32 PORT3.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P31 PORT3.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P30 PORT3.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P27 PORT2.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P26 PORT2.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P25 PORT2.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P24 PORT2.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P23 PORT2.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P22 PORT2.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P21 PORT2.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P20 PORT2.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P17 PORT1.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P16 PORT1.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P15 PORT1.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P14 PORT1.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P13 PORT1.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P12 PORT1.PODR.BYTE
/* Pin35:VCC_USB*/
/* Pin36:USB0_DM*/
/* Pin37:USB0_DP*/
/* Pin38:VSS_USB*/
#define Port_Cfg_Ch_Wr_Byte_P55 PORT5.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P54 PORT5.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P53 PORT5.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P52 PORT5.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P51 PORT5.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P50 PORT5.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PC7 PORTC.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PC6 PORTC.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PC5 PORTC.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PC4 PORTC.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PC3 PORTC.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PC2 PORTC.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PC1 PORTC.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PC0 PORTC.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PB7 PORTB.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PB6 PORTB.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PB5 PORTB.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PB4 PORTB.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PB3 PORTB.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PB2 PORTB.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PB1 PORTB.PODR.BYTE
/* Pin60:VCC*/
#define Port_Cfg_Ch_Wr_Byte_PB0 PORTB.PODR.BYTE
/* Pin62:VSS*/
#define Port_Cfg_Ch_Wr_Byte_PA7 PORTA.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PA6 PORTA.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PA5 PORTA.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PA4 PORTA.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PA3 PORTA.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PA2 PORTA.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PA1 PORTA.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PA0 PORTA.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PE7 PORTE.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PE6 PORTE.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PE5 PORTE.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PE4 PORTE.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PE3 PORTE.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PE2 PORTE.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PE1 PORTE.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PE0 PORTE.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PD7 PORTD.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PD6 PORTD.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PD5 PORTD.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PD4 PORTD.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PD3 PORTD.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PD2 PORTD.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PD1 PORTD.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_PD0 PORTD.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P47 PORT4.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P46 PORT4.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P45 PORT4.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P44 PORT4.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P43 PORT4.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P42 PORT4.PODR.BYTE
#define Port_Cfg_Ch_Wr_Byte_P41 PORT4.PODR.BYTE
/* Pin94:VREFL0*/
#define Port_Cfg_Ch_Wr_Byte_P40 PORT4.PODR.BYTE
/* Pin96:VREFH0*/
/* Pin97:AVCC0*/
#define Port_Cfg_Ch_Wr_Byte_P07 PORT0.PODR.BYTE
/* Pin99:AVSS0*/
#define Port_Cfg_Ch_Wr_Byte_P05 PORT0.PODR.BYTE
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


/* Bit位置定義 */
/* Pin1:AVCC1*/
/* Pin2:EMLE*/
/* Pin3:AVSS1*/
#define Port_Cfg_Ch_Wr_Bit_PJ3 3
/* Pin5:VCL*/
/* Pin6:VBATT*/
/* Pin7:MD/FINED*/
/* Pin8:XCIN*/
/* Pin9:XCOUT*/
/* Pin10:RES#*/
#define Port_Cfg_Ch_Wr_Bit_P37 7
/* Pin12:VSS*/
#define Port_Cfg_Ch_Wr_Bit_P36 6
/* Pin14:VCC*/
#define Port_Cfg_Ch_Wr_Bit_P35 5
#define Port_Cfg_Ch_Wr_Bit_P34 4
#define Port_Cfg_Ch_Wr_Bit_P33 3
#define Port_Cfg_Ch_Wr_Bit_P32 2
#define Port_Cfg_Ch_Wr_Bit_P31 1
#define Port_Cfg_Ch_Wr_Bit_P30 0
#define Port_Cfg_Ch_Wr_Bit_P27 7
#define Port_Cfg_Ch_Wr_Bit_P26 6
#define Port_Cfg_Ch_Wr_Bit_P25 5
#define Port_Cfg_Ch_Wr_Bit_P24 4
#define Port_Cfg_Ch_Wr_Bit_P23 3
#define Port_Cfg_Ch_Wr_Bit_P22 2
#define Port_Cfg_Ch_Wr_Bit_P21 1
#define Port_Cfg_Ch_Wr_Bit_P20 0
#define Port_Cfg_Ch_Wr_Bit_P17 7
#define Port_Cfg_Ch_Wr_Bit_P16 6
#define Port_Cfg_Ch_Wr_Bit_P15 5
#define Port_Cfg_Ch_Wr_Bit_P14 4
#define Port_Cfg_Ch_Wr_Bit_P13 3
#define Port_Cfg_Ch_Wr_Bit_P12 2
/* Pin35:VCC_USB*/
/* Pin36:USB0_DM*/
/* Pin37:USB0_DP*/
/* Pin38:VSS_USB*/
#define Port_Cfg_Ch_Wr_Bit_P55 5
#define Port_Cfg_Ch_Wr_Bit_P54 4
#define Port_Cfg_Ch_Wr_Bit_P53 3
#define Port_Cfg_Ch_Wr_Bit_P52 2
#define Port_Cfg_Ch_Wr_Bit_P51 1
#define Port_Cfg_Ch_Wr_Bit_P50 0
#define Port_Cfg_Ch_Wr_Bit_PC7 7
#define Port_Cfg_Ch_Wr_Bit_PC6 6
#define Port_Cfg_Ch_Wr_Bit_PC5 5
#define Port_Cfg_Ch_Wr_Bit_PC4 4
#define Port_Cfg_Ch_Wr_Bit_PC3 3
#define Port_Cfg_Ch_Wr_Bit_PC2 2
#define Port_Cfg_Ch_Wr_Bit_PC1 1
#define Port_Cfg_Ch_Wr_Bit_PC0 0
#define Port_Cfg_Ch_Wr_Bit_PB7 7
#define Port_Cfg_Ch_Wr_Bit_PB6 6
#define Port_Cfg_Ch_Wr_Bit_PB5 5
#define Port_Cfg_Ch_Wr_Bit_PB4 4
#define Port_Cfg_Ch_Wr_Bit_PB3 3
#define Port_Cfg_Ch_Wr_Bit_PB2 2
#define Port_Cfg_Ch_Wr_Bit_PB1 1
/* Pin60:VCC*/
#define Port_Cfg_Ch_Wr_Bit_PB0 0
/* Pin62:VSS*/
#define Port_Cfg_Ch_Wr_Bit_PA7 7
#define Port_Cfg_Ch_Wr_Bit_PA6 6
#define Port_Cfg_Ch_Wr_Bit_PA5 5
#define Port_Cfg_Ch_Wr_Bit_PA4 4
#define Port_Cfg_Ch_Wr_Bit_PA3 3
#define Port_Cfg_Ch_Wr_Bit_PA2 2
#define Port_Cfg_Ch_Wr_Bit_PA1 1
#define Port_Cfg_Ch_Wr_Bit_PA0 0
#define Port_Cfg_Ch_Wr_Bit_PE7 7
#define Port_Cfg_Ch_Wr_Bit_PE6 6
#define Port_Cfg_Ch_Wr_Bit_PE5 5
#define Port_Cfg_Ch_Wr_Bit_PE4 4
#define Port_Cfg_Ch_Wr_Bit_PE3 3
#define Port_Cfg_Ch_Wr_Bit_PE2 2
#define Port_Cfg_Ch_Wr_Bit_PE1 1
#define Port_Cfg_Ch_Wr_Bit_PE0 0
#define Port_Cfg_Ch_Wr_Bit_PD7 7
#define Port_Cfg_Ch_Wr_Bit_PD6 6
#define Port_Cfg_Ch_Wr_Bit_PD5 5
#define Port_Cfg_Ch_Wr_Bit_PD4 4
#define Port_Cfg_Ch_Wr_Bit_PD3 3
#define Port_Cfg_Ch_Wr_Bit_PD2 2
#define Port_Cfg_Ch_Wr_Bit_PD1 1
#define Port_Cfg_Ch_Wr_Bit_PD0 0
#define Port_Cfg_Ch_Wr_Bit_P47 7
#define Port_Cfg_Ch_Wr_Bit_P46 6
#define Port_Cfg_Ch_Wr_Bit_P45 5
#define Port_Cfg_Ch_Wr_Bit_P44 4
#define Port_Cfg_Ch_Wr_Bit_P43 3
#define Port_Cfg_Ch_Wr_Bit_P42 2
#define Port_Cfg_Ch_Wr_Bit_P41 1
/* Pin94:VREFL0*/
#define Port_Cfg_Ch_Wr_Bit_P40 0
/* Pin96:VREFH0*/
/* Pin97:AVCC0*/
#define Port_Cfg_Ch_Wr_Bit_P07 7
/* Pin99:AVSS0*/
#define Port_Cfg_Ch_Wr_Bit_P05 5
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

#endif


#ifdef __cplusplus
}
#endif


#endif
