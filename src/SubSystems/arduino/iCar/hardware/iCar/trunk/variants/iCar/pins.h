/**
 * @file pins.h
 * @brief Pin定義
 */
#ifndef Pins_h
#define Pins_h


#include "LcdDrv_Ext.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def LED_BUILTIN
 * @brief ビルトインLEDのPinを表す
 * @note iCarではLED3がビルトインLEDとなっています
 */
#define LED_BUILTIN     (PIN_LED3)

/**
 * @def PIN_VOLUME
 * @brief スライドボリュームのPin番号
 */
#define PIN_VOLUME      (0)

/**
 * @def PIN_DISTANCE
 * @brief 距離センサのPin番号
 */
#define PIN_DISTANCE    (1)

/**
 * @def PIN_BRIGHTNESS
 * @brief 明るさセンサのPin番号
 */
#define PIN_BRIGHTNESS  (2)

/**
 * @def PIN_LINE_L
 * @brief ラインセンサL(左側)のPin番号
 */
#define PIN_LINE_L      (3)

/**
 * @def PIN_LINE_R
 * @brief ラインセンサR(右側)のPin番号
 */
#define PIN_LINE_R      (4)

/**
 * @def PIN_TOGGLE
 * @brief トグルスイッチのPin番号
 */
#define PIN_TOGGLE      (5)

/**
 * @def PIN_BTN1
 * @brief ボタン1のPin番号
 */
#define PIN_BTN1        (6)

/**
 * @def PIN_BTN2
 * @brief ボタン2のPin番号
 */
#define PIN_BTN2        (7)

/**
 * @def PIN_LED1
 * @brief LED1のPin番号
 */
#define PIN_LED1        (8)

/**
 * @def PIN_LED2
 * @brief LED2のPin番号
 */
#define PIN_LED2        (9)

/**
 * @def PIN_LED3
 * @brief LED3のPin番号
 */
#define PIN_LED3        (10)

/**
 * @def PIN_LED4
 * @brief LED4のPin番号
 */
#define PIN_LED4        (11)

/**
 * @def PIN_LED5
 * @brief LED5のPin番号
 */
#define PIN_LED5        (12)

/**
 * @def PIN_LED6
 * @brief LED6のPin番号
 */
#define PIN_LED6        (13)

/**
 * @def PIN_MOTOR_L
 * @brief MotorL (左モータ)のPin番号
 */
#define PIN_MOTOR_L     (14)

/**
 * @def PIN_MOTOR_R
 * @brief MotorR (右モータ)のPin番号
 */
#define PIN_MOTOR_R     (15)

/**
 * @def PIN_BUZZER
 * @brief ブザーのPin番号
 */
#define PIN_BUZZER      (16)

/**
 * @def PIN_FLED_R
 * @brief フルカラーLED R(赤) Pin番号
 */
#define PIN_FLED_R      (17)

/**
 * @def PIN_FLED_G
 * @brief フルカラーLED G(緑) Pin番号
 */
#define PIN_FLED_G      (18)

/**
 * @def PIN_FLED_B
 * @brief フルカラーLED B(青) Pin番号
 */
#define PIN_FLED_B      (19)


#ifdef __cplusplus
}
#endif


#endif
