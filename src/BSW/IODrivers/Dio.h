/**
 * @file Dio.h
 * @brief デジタル(汎用ポート) 入出力を提供する
 */

#ifndef __Dio_H
#define __Dio_H


#include <SystemServices/Mcu.h>


#include "Dio_Cfg.h"


#ifdef __cplusplus
extern "C" {
#endif


/** @def ポートのBitを読み出す
 *  ChannelId ポート Pxxの形で指定する P01の場合P01、PD1の場合PD1
 */
#define Dio_ReadChannel(ChannelId)          Mcu_SFR_Read(Port_Cfg_Ch_Rd_##ChannelId)


/** @def ポートのBitを書き込む
 *  ChannelId ポート Pxxの形で指定する P01の場合P01、PD1の場合PD1
 *  Level レベル
 */
#if Dio_Use_BitOperation == FALSE
/* RAM干渉対策無し時 ビットフィールドアクセスを行う */
#define Dio_WriteChannel(ChannelId, Level)  Mcu_SFR_Write(Port_Cfg_Ch_Wr_##ChannelId, (Level))
#else
/* RAM干渉対策有り時 Mcu_SFR_WriteBit関数にてビットアクセス命令を発行してアクセスする */
#define Dio_WriteChannel(ChannelId, Level)  Mcu_SFR_WriteBit(&Port_Cfg_Ch_Wr_Byte_##ChannelId, Port_Cfg_Ch_Wr_Bit_##ChannelId, (Level))
#endif


/* 内部用マクロ PortをPortIdに変換 */
#define Dio_PortId__(PortId)                PORT##PortId


/** @def ポートを一括で読み出す
 *  PortId ポートグループ PORT0の場合0、PODRTDの場合Dを指定する
 *  Level レベル
 */
#define Dio_ReadPort(PortId)                Mcu_SFR_Read(Dio_PortId__(PortId).PIDR.BYTE)


/** @def ポートを一括で書き込む
 *  PortId ポートグループ PORT0の場合0、PODRTDの場合Dを指定する
 *  Level レベル ポートレベル指定レジスタに設定する値
 */
#define Dio_WritePort(PortId, Level)        Mcu_SFR_Write(Dio_PortId__(PortId).PODR.BYTE, (Level))


#ifdef __cplusplus
}
#endif


#endif
