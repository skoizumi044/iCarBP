/**
 * @file LcdDrv_Ext.h
 * @brief LCD表示機能を提供する
 */

#ifndef __LcdDrv_H
#define __LcdDrv_H


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def LcdDrv_X_MAX
 * @brief LCDの横文字数
 */
#define LcdDrv_X_MAX                (16u)

/**
 * @def LcdDrv_Y_MAX
 * @brief LCDの縦文字数
 */
#define LcdDrv_Y_MAX                (2u)

/**
 * @brief 初期化
 */
void LcdDrv_Init(void);

/**
 * @brief Lcdドライバがアクティブかを返す
 * @return 初期化済み=TRUE, 未初期化=FALSE
 */
boolean LcdDrv_IsActive(void);

/**
 * @brief Lcdドライバがフェールかを返す
 * @return フェール発生=TRUE, フェール未発生=FALSE
 * @note フェール発生時はLcdDrv_Init()を呼び出し、再初期化する必要がある
 */
boolean LcdDrv_IsFail(void);

/**
 * @brief 画面バッファをクリアしてカーソルを原点に戻す
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_clear(void);
/**
 * @brief カーソルを原点に移動する
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_home(void);

/**
 * @brief VRAM更新用のカーソルを更新する
 * @param ui8t_y 縦位置・・・0が上端
 * @param ui8t_x 横位置・・・0が左端
 * @note 不正な値を指定場合、0が設定される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setCursor(uint8_t ui8t_y, uint8_t ui8t_x);

/**
 * @brief LCDに文字列を設定する
 * @param ct_text 表示文字
 * @note 行端まで書き込むと、自動で次の行に移動する
 * @note 画面バッファに収まらない場合
 *       左上から続きを書き込みする
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_putchar(char ct_text);

/**
 * @brief LCDに文字列を設定する
 * @param szt_text 文字列
 * @param ui8t_length 設定する文字列の長さ
 * @note 行端まで書き込むと、自動で次の行に移動する
 * @note 画面バッファに収まらない文字列を指定した場合、
 *       左上から続きを書き込みする
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_print(const char *szt_text);

/**
 * @brief LCDに数値を設定する 0サプレス有り
 * @param ui32t_num 数値
 * @param ui8t_numdigit 桁数
 * @note 画面バッファに収まらない文字サイズを指定した場合、
 *       左および上にロールオーバーされる
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setNum(uint32_t ui32t_num, uint8_t ui8t_numdigit);

/**
 * @brief LCDに数値を設定する 0サプレス無し
 * @param ui32t_num 数値
 * @param ui8t_numdigit 桁数
 * @note 画面バッファに収まらない文字サイズを指定した場合、
 *       左および上にロールオーバーされる
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setNumNoZeroSup(uint32_t ui32t_num, uint8_t ui8t_numdigit);

/**
 * @brief LCDに16進数を設定する
 * @param ui32t_num 数値
 * @param ui8t_numdigit 桁数
 * @note 画面バッファに収まらない文字サイズを指定した場合、
 *       左および上にロールオーバーされる
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setHex(uint32_t ui32t_num, uint8_t ui8t_numdigit);

/**
 * @brief LCDに2進数を設定する
 * @param ui32t_num 数値
 * @param ui8t_numdigit 桁数
 * @note 画面バッファに収まらない文字サイズを指定した場合、
 *       左および上にロールオーバーされる
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setBin(uint32_t ui32t_num, uint8_t ui8t_numdigit);

/**
 * @brief LCDを更新する
 */
boolean LcdDrv_update(void);


#ifdef __cplusplus
}
#endif


#endif
