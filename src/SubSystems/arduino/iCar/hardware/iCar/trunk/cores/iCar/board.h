/**
 * @file board.h
 * @brief APIs
 */

#ifndef board_H
#define board_H


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @def PROGMEM
 * @brief Arduino環境との互換性確保のためのマクロ
 */
#define PROGMEM         const


/**
 * @def HIGH
 * @brief digitalRead/digitalWrite用 電圧Hiレベル
 */
#define HIGH            (0x01)

/**
 * @def LOW
 * @brief digitalRead/digitalWrite用 電圧Loレベル
 */
#define LOW             (0x00)


/**
 * @def INPUT
 * @brief pinMode用 Pinを入力に設定
 */
#define INPUT           (0x00)

/**
 * @def OUTPUT
 * @brief pinMode用 Pinを出力に設定
 */
#define OUTPUT          (0x01)

/**
 * @def INPUT_PULLUP
 * @brief pinMode用 Pinを入力+プルアップに設定(プルアップ=配線未接続時Hiとなる)
 */
#define INPUT_PULLUP    (0x02)


#define PI              (3.1415926535897932384626433832795)
#define HALF_PI         (1.5707963267948966192313216916398)
#define TWO_PI          (6.283185307179586476925286766559)
#define DEG_TO_RAD      (0.017453292519943295769236907684886)
#define RAD_TO_DEG      (57.295779513082320876798154814105)
#define EULER           (2.718281828459045235360287471352)


/**
 * @def DEFAULT
 * @brief analogReference用 基準電圧=デフォルト
 */
#define DEFAULT     (0)

/**
 * @def EXTERNAL
 * @brief analogReference用 基準電圧=外部電源
 * @note 本マクロは互換性確保のために定義されており、DEFAULTの設定となる
 */
#define EXTERNAL    (DEFAULT)

/**
 * @def INTERNAL
 * @brief analogReference用 基準電圧=外部電源
 * @note 本マクロは互換性確保のために定義されており、DEFAULTの設定となる
 */
#define INTERNAL    (DEFAULT)


/**
 * @def min
 * @brief 引数で指定された2つの値のうち、小さいほうを返す
 * @param a 引数1
 * @param b 引数2
 * @return aかb小さいほうの値
 */
#define min(a, b)       ((a) < (b) ? (a) : (b))

/**
 * @def max
 * @brief 引数で指定された2つの値のうち、大きいほうを返す
 * @param a 引数1
 * @param b 引数2
 * @return aかb大きいほうの値
 */
#define max(a, b)       ((a) > (b) ? (a) : (b))

/**
 * @def constrain
 * @brief 入力値amtを上限・下限範囲に制限した値を返す
 * @param amt 入力値
 * @param low 下限値
 * @param high 上限値
 * @return amtをlowからhighの間に収めた値
 */
#define constrain(amt, low, high) (((amt) < (low)) ? (low) : ((amt) > (high) ? (high) : (amt)))

/**
 * @def round
 * @brief 入力値を四捨五入する
 */
#define round(x)        (((x) >= 0) ? ((long)((x) + 0.5)) : ((long)((x) - 0.5)))

/**
 * @def radians
 * @brief 度単位で表された角度をラジアンに変換する
 */
#define radians(deg)    ((deg) * DEG_TO_RAD)

/**
 * @def degrees
 * @brief ラジアンで表された角度を度に変換する
 */
#define degrees(rad)    ((rad) * RAD_TO_DEG)

/**
 * @def sq
 * @brief 引数で指定された値を2乗する
 */
#define sq(x)           ((x) * (x))


/**
 * @def interrupts
 * @brief 割り込みを許可する
 * @note 割り込み禁止した場合は許可する必要がある
 */
#define interrupts()    asm volatile ("SETPSW I")

/**
 * @def noInterrupts
 * @brief 割り込みを禁止する
 * @note 割り込み禁止した場合はinterruptsを呼び出して再度許可する必要がある
 * @note 割り込み禁止時間が長い場合、デバイス動作が不安定となる場合があります
 */
#define noInterrupts()  asm volatile ("CLRPSW I")


/**
 * @def lowByte
 * @brief 2バイトの内、下位のバイトを取得する
 */
#define lowByte(w)      ((uint8_t)((w) & 0xFF))

/**
 * @def highByte
 * @brief 2バイトの内、上位のバイトを取得する
 */
#define highByte(w)     ((uint8_t)((((uint32_t)(w)) >> 8) & 0xFF))


/**
 * @def bitRead
 * @brief valueから指定したビットを読み出す
 * @param value 値
 * @param bit 読み出しビット (0-31)
 * @return 0(false) / 1(true)
 */
#define bitRead(value, bit)             ((((uint32_t)(value)) >> (bit)) & 0x01)

/**
 * @def bitSet
 * @brief 指定したビットを1にする
 * @param value 変数 (定数/戻り値の指定不可)
 * @param bit 読み出しビット (0-31)
 * @note 本関数はvalueで指定された変数を直接書換する valueには変数のみ指定可能
 */
#define bitSet(value, bit)              ((value) |= (0x01UL << (bit)))

/**
 * @def bitClear
 * @brief 指定したビットを0にする
 * @param value 変数 (定数/戻り値の指定不可)
 * @param bit 読み出しビット (0-31)
 * @note 本関数はvalueで指定された変数を直接書換する valueには変数のみ指定可能
 */
#define bitClear(value, bit)            ((value) &= ~(0x01UL << (bit)))

/**
 * @def bitWrite
 * @brief 指定したビットに値を書き込む
 * @param value 変数 (定数/戻り値の指定不可)
 * @param bit 読み出しビット (0-31)
 * @param bitvalue 書き込み値 (0 or 1)
 * @note 本関数はvalueで指定された変数を直接書換する valueには変数のみ指定可能
 */
#define bitWrite(value, bit, bitvalue)  ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))


/**
 * @def _NOP
 * @brief nop命令を生成する(nop命令=1クロック何も実行しない)
 * @note 本関数は一定時間待機するためなどの用途に用いる
 */
#define _NOP()      asm volatile ("NOP")


/**
 * @def bit
 * @brief 指定ビットを1にした値を返す
 * @param b ビット
 * @note bit(7)を呼び出した場合、戻り値は0x80(128)
 */
#define bit(b)  (1UL << (b))

typedef bool boolean;
typedef uint8_t byte;
typedef uint16_t word;


void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
int analogRead(uint8_t pin);
void analogReference(uint8_t mode);
void analogWrite(uint8_t pin, int val);


uint32_t millis(void);
uint32_t micros(void);
void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
#include "WCharacter.h"
#include "WString.h"
#include "HardwareSerial.h"


void tone(uint8_t pin, unsigned int frequency, unsigned long duration = 0);
void noTone(uint8_t pin);


/**
 * @brief 0から指定した値 - 1までの乱数を生成する
 * @param howbig 乱数最大値 + 1
 * @note howbigには[生成したい乱数最大値 + 1を指定する]
 *       (0～9までの乱数を生成する場合10を指定しなければならない)
 */
long random(long);

/**
 * @brief 0から指定した値 - 1までの乱数を生成する
 * @param howsmall 乱数最小値
 * @param howbig 乱数最大値 + 1
 * @note howbigには[生成したい乱数最大値 + 1を指定する]
 *       (0～9までの乱数を生成する場合10を指定しなければならない)
 */
long random(long, long);

/**
 * @brief 乱数のシードを設定する
 * @param seed 乱数のシード
 */
void randomSeed(unsigned long);

/**
 * @brief 引数で指定された値を線形補完した値を返す
 * @param x 入力値
 * @param in_min 入力値最小値
 * @param in_max 入力値最大値
 * @param out_min 出力値最小値
 * @param out_max 出力値最大値
 */
long map(long, long, long, long, long);
#endif


/**
 * @brief セットアップ処理
 * @note ボードに電源を入れたときやリセットされたときに、一度だけ実行される。
 * 変数の初期化やライブラリの準備に使用します。
 */
void setup();

/**
 * @brief プログラムのメイン処理
 * @note 本関数に制御を記述してください。本関数は繰り返し実行されます。
 */
void loop();


#include "pins.h"


#endif
