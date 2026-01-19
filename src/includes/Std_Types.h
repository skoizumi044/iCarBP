/**
 * @file Std_Types.h
 * @brief 標準で使用する変数型を定義する
 */

/* Include Guard */
#ifndef __Std_Types_H
#define __Std_Types_H

/* Includes */
#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef bool boolean;

#ifndef TRUE
#define TRUE        (1)
#endif

#ifndef FALSE
#define FALSE       (0)
#endif

#ifndef ON
#define ON          (1)
#endif

#ifndef OFF
#define OFF         (0)
#endif

#ifndef HI
#define HI          (1)
#endif

#ifndef LO
#define LO          (0)
#endif

#ifndef NULL
#define NULL        ((void *)0)
#endif


/* 配列インデックス用定義 */
#define IDX_0               (0)
#define IDX_1               (1)
#define IDX_2               (2)
#define IDX_3               (3)
#define IDX_4               (4)
#define IDX_5               (5)
#define IDX_6               (6)
#define IDX_7               (7)
#define IDX_8               (8)
#define IDX_9               (9)
#define IDX_10              (10)
#define IDX_11              (11)
#define IDX_12              (12)
#define IDX_13              (13)
#define IDX_14              (14)
#define IDX_15              (15)
#define IDX_16              (16)
#define IDX_17              (17)
#define IDX_18              (18)
#define IDX_19              (19)
#define IDX_20              (20)
#define IDX_32              (32)


#define BIT_0               (0x01u)
#define BIT_1               (0x02u)
#define BIT_2               (0x04u)
#define BIT_3               (0x08u)
#define BIT_4               (0x10u)
#define BIT_5               (0x20u)
#define BIT_6               (0x40u)
#define BIT_7               (0x80u)
#define BIT_8               (0x0100u)
#define BIT_9               (0x0200u)
#define BIT_10              (0x0400u)
#define BIT_11              (0x0800u)
#define BIT_12              (0x1000u)
#define BIT_13              (0x2000u)
#define BIT_14              (0x4000u)
#define BIT_15              (0x8000u)
#define BIT_16              (0x00010000uL)
#define BIT_17              (0x00020000uL)
#define BIT_18              (0x00040000uL)
#define BIT_19              (0x00080000uL)
#define BIT_20              (0x00100000uL)
#define BIT_21              (0x00200000uL)
#define BIT_22              (0x00400000uL)
#define BIT_23              (0x00800000uL)
#define BIT_24              (0x01000000uL)
#define BIT_25              (0x02000000uL)
#define BIT_26              (0x04000000uL)
#define BIT_27              (0x08000000uL)
#define BIT_28              (0x10000000uL)
#define BIT_29              (0x20000000uL)
#define BIT_30              (0x40000000uL)
#define BIT_31              (0x80000000uL)


#define VAL_0               (0x00u)
#define VAL_FF              (0xFFu)
#define VAL_FFFF            (0xFFFFu)


#ifdef __cplusplus
}
#endif


#endif
