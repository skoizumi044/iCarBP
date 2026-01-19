/**
 * @file LcdDrv.c
 * @brief LCD表示機能を提供する
 */

#include <Std_Types.h>
#include <BSW/SystemServices/Mcu.h>
#include <BSW/IODrivers/I2c.h>
#include <LIB/Bcd.h>

#include "LcdDrv.h"


#define LcdDrv_I2C_Ch   (0)
#define LcdDrv_I2C_Addr (0x3Eu)

#define LcdDrv_CmdWaitTime          (324)
#define LcdDrv_POWERON_WAITTIME     (4)
#define LcdDrv_INIT2_WAITTIME       (20)

#define LcdDrv_State_DISABLED       (0x00u)
#define LcdDrv_State_POWERON_WAIT   (0x01u)
#define LcdDrv_State_INIT1          (0x02u)
#define LcdDrv_State_INIT2          (0x03u)
#define LcdDrv_State_INIT3          (0x04u)
#define LcdDrv_State_ACTIVE         (0x05u)
#define LcdDrv_State_FAIL           (0xFFu)

#define LcdDrv_CD_CMD               (0x00u)
#define LcdDrv_CD_DATA              (0x40u)

#define LcdDrv_CMD_SetCursor        (0x80u)
#define LcdDrv_CMD_ClearScreen      (0x01u)


uint8_t LcdDrv_State = LcdDrv_State_DISABLED;
volatile boolean LcdDrv_UpdateFlag = FALSE;
uint8_t LcdDrv_WaitCounter;

char LcdDrv_VRAM1[LcdDrv_Y_MAX * LcdDrv_X_MAX];
char LcdDrv_VRAM2[LcdDrv_Y_MAX * LcdDrv_X_MAX];
uint8_t LcdDrv_CursorX;
uint8_t LcdDrv_CursorY;



static const uint8_t LcdDrv_InitialData[] = {
    0x38,   /* Function set */
    0x39,   /* Function set */
    0x14,   /* Internal OSC frequency */
    0x73,   /* Contrast set */
    0x56,   /* Power ICON Contrast control */
    0x6C,   /* Follower control */
    0x38,   /* Function set */
    0x01,   /* Clear Display */
    0x0C    /* Display ON/OFF control */
};

const uint8_t LcdDrv_FontTable[] =
{
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F
};


static void LcdDrv_Wait27us(void);
static void LcdDrv_ActiveOperation(void);


/**
 * @brief 初期化
 */
void LcdDrv_Init(void)
{
    /* 状態を初期化 */
    LcdDrv_State = LcdDrv_State_POWERON_WAIT;
    
    /* 更新フラグを初期化 */
    LcdDrv_UpdateFlag = FALSE;
    
    /* タイマカウンタを初期化 */
    LcdDrv_WaitCounter = VAL_0;
    
    /* 画面バッファをクリア */
    LcdDrv_clear();
}


/**
 * @brief 解放
 */
void LcdDrv_DeInit(void)
{
    /* 状態を初期化 */
    LcdDrv_State = LcdDrv_State_DISABLED;
}


/**
 * @brief Lcdドライバがアクティブかを返す
 * @return 初期化済み=TRUE, 未初期化=FALSE
 */
boolean LcdDrv_IsActive(void)
{
    return (LcdDrv_State == LcdDrv_State_ACTIVE);
}


/**
 * @brief Lcdドライバがフェールかを返す
 * @return フェール発生=TRUE, フェール未発生=FALSE
 * @note フェール発生時はLcdDrv_Init()を呼び出し、再初期化する必要がある
 */
boolean LcdDrv_IsFail(void)
{
    return (LcdDrv_State == LcdDrv_State_FAIL);
}


/**
 * @brief ドライバ用の27us待機
 * @note ICLK=120MHz想定
 */
static void LcdDrv_Wait27us(void)
{
    /* 最適化による処理時間のブレを少なくす為 */
    /* ループカウンタを意図的に32bit signedレジスタ変数に割り付け */
    register int32_t si32t_cnt;
    
    /* @120MHz 3240 NOP */
    /* 3240 = 8NOPs + 2LOOP Instractions (DEC, JMP) */
    si32t_cnt = LcdDrv_CmdWaitTime;
    while (si32t_cnt-- > IDX_0) {
#if Mcu_Clk_Cfg_ILCK_FREQ_KHZ == (120000)
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
        Mcu_NOP();
#else
#error "LcdDrv_Wait27us() Invalid Mcu_Clk_Cfg_ILCK_FREQ_KHZ. Please configure."
#endif
    }
}


/**
 * @brief LCDにデータを送信する
 * @param ui8tp_data 送信データ
 * @param ui16t_length 送信データの長さ
 * @return TRUE=送信成功, FALSE=送信失敗
 */
boolean LcdDrv_WriteData(const uint8_t *ui8tp_data, uint16_t ui16t_length)
{
    boolean bt_ret;
    uint8_t txBuf;
    uint8_t ui8t_addr;
    
    txBuf = LcdDrv_CD_DATA;
    
    /* スタートビット送信 */
    if (I2c_SendStart(LcdDrv_I2C_Ch) == FALSE) {
        return (FALSE);
    }
    
    bt_ret = FALSE;
    
    /* アドレスを送信する */
    ui8t_addr = LcdDrv_I2C_Addr << IDX_1;
    if (I2c_WriteRaw(LcdDrv_I2C_Ch, &ui8t_addr, sizeof(ui8t_addr)) == TRUE) {
        /* Control Byteを送信する */
        if (I2c_WriteRaw(LcdDrv_I2C_Ch, &txBuf, sizeof(txBuf))) {
            /* データを送信する */
            if (I2c_WriteRaw(LcdDrv_I2C_Ch, ui8tp_data, ui16t_length) == TRUE) {
                bt_ret = TRUE;
                
                /* 送信完了するまで待つ */
                while (I2c_WriteIsFinish(LcdDrv_I2C_Ch, &bt_ret) == FALSE) {}
            }
        }
    }
    
    /* ストップビット送信 */
    if (I2c_SendStop(LcdDrv_I2C_Ch) == FALSE) {
        return (FALSE);
    }
    
    LcdDrv_Wait27us();
    
    return (bt_ret);
}


/**
 * @brief LCDにコマンドを送信する
 * @param ui8t_cmd 送信コマンド
 * @return TRUE=送信成功, FALSE=送信失敗
 */
boolean LcdDrv_WriteCommand(uint8_t ui8t_cmd)
{
    boolean bt_ret;
    uint8_t txBuf[IDX_2];
    
    txBuf[IDX_0] = LcdDrv_CD_CMD;
    txBuf[IDX_1] = ui8t_cmd;
    
    bt_ret = I2c_Write(LcdDrv_I2C_Ch, LcdDrv_I2C_Addr, &txBuf[IDX_0], sizeof(txBuf));
    LcdDrv_Wait27us();
    
    return (bt_ret);
}


/**
 * @brief 定期処理
 * @note 本処理は10ms定期で呼び出されることを想定している
 */
void LcdDrv_PeriodicTask(void)
{
    uint8_t ui8t_idx;
    
    switch (LcdDrv_State) {
    case LcdDrv_State_DISABLED:
        break;
    case LcdDrv_State_FAIL:
        break;
    case LcdDrv_State_POWERON_WAIT:
        /* Wait for 40ms */
        if (LcdDrv_WaitCounter >= LcdDrv_POWERON_WAITTIME) {
            LcdDrv_WaitCounter = VAL_0;
            LcdDrv_State = LcdDrv_State_INIT1;
        } else {
            LcdDrv_WaitCounter++;
        }
        break;
    case LcdDrv_State_INIT1:
        if (LcdDrv_WriteCommand(LcdDrv_InitialData[IDX_0]) == FALSE) {
            LcdDrv_State = LcdDrv_State_FAIL;
        }
        
        for (ui8t_idx = IDX_1; ui8t_idx < IDX_6; ui8t_idx++) {
            LcdDrv_WriteCommand(LcdDrv_InitialData[ui8t_idx]);
        }
        LcdDrv_State = LcdDrv_State_INIT2;
        break;
    case LcdDrv_State_INIT2:
        if (LcdDrv_WaitCounter >= LcdDrv_INIT2_WAITTIME) {
            LcdDrv_WaitCounter = VAL_0;
            
            LcdDrv_WriteCommand(LcdDrv_InitialData[IDX_6]);
            LcdDrv_WriteCommand(LcdDrv_InitialData[IDX_7]);
            LcdDrv_State = LcdDrv_State_INIT3;
        } else {
            LcdDrv_WaitCounter++;
        }
        break;
    case LcdDrv_State_INIT3:

        /* Set Fonts */
        LcdDrv_WriteCommand(0x40 | 0x00);
        LcdDrv_WriteData(&LcdDrv_FontTable[0], sizeof(LcdDrv_FontTable));

        LcdDrv_WriteCommand(LcdDrv_InitialData[IDX_8]);
        LcdDrv_State = LcdDrv_State_ACTIVE;
        break;
    case LcdDrv_State_ACTIVE:
        LcdDrv_ActiveOperation();
        break;
    default:
        LcdDrv_State = LcdDrv_State_DISABLED;
        break;
    }
}


/**
 * @brief 画面バッファをクリアしてカーソルを原点に戻す
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_clear(void)
{
    uint8_t ui8t_idx;
    
    /* カーソルを原点に戻す */
    LcdDrv_CursorX = IDX_0;
    LcdDrv_CursorY = IDX_0;
    
    /* VRAMクリア */
    for (ui8t_idx = IDX_0; ui8t_idx < sizeof(LcdDrv_VRAM1); ui8t_idx++) {
        LcdDrv_VRAM1[ui8t_idx] = ' ';
    }
}


/**
 * @brief カーソルを原点に移動する
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_home(void)
{
    LcdDrv_CursorX = IDX_0;
    LcdDrv_CursorY = IDX_0;
}


/**
 * @brief VRAM更新用のカーソルを更新する
 * @param ui8t_y 縦位置・・・0が上端
 * @param ui8t_x 横位置・・・0が左端
 * @note 不正な値を指定場合、0が設定される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setCursor(uint8_t ui8t_y, uint8_t ui8t_x)
{
    /* カーソル上限値ガード */
    if (LcdDrv_X_MAX <= ui8t_x) {
        ui8t_x = IDX_0;
    }
        
    if (LcdDrv_Y_MAX <= ui8t_y) {
        ui8t_y = IDX_0;
    }
    
    /* カーソルを設定 */
    LcdDrv_CursorX = ui8t_x;
    LcdDrv_CursorY = ui8t_y;
}


/**
 * @brief VRAMに文字列を設定する
 * @param ct_text 表示文字
 * @note 行端まで書き込むと、自動で次の行に移動する
 * @note 画面バッファに収まらない場合
 *       左上から続きを書き込みする
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_putchar(char ct_text)
{
    LcdDrv_VRAM1[(LcdDrv_CursorY * IDX_16) + LcdDrv_CursorX] = ct_text;


    /* カーソルを移動 */
    LcdDrv_CursorX = LcdDrv_CursorX + IDX_1;
    if (LcdDrv_X_MAX <= LcdDrv_CursorX) {
        LcdDrv_CursorX = IDX_0;
        LcdDrv_CursorY = LcdDrv_CursorY + IDX_1;
    }

    if (LcdDrv_Y_MAX <= LcdDrv_CursorY) {
        LcdDrv_CursorY = IDX_0;
    }
}


/**
 * @brief VRAMに文字列を設定する
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
void LcdDrv_print(const char *szt_text)
{
    while  (*szt_text != '\0') {
        LcdDrv_putchar(*szt_text);
        szt_text++;
    }
}


/**
 * @brief VRAMに数値を設定する 0サプレス有り
 * @param ui32t_num 数値
 * @param ui8t_numdigit 桁数
 * @note 画面バッファに収まらない文字サイズを指定した場合、
 *       左および上にロールオーバーされる
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setNum(uint32_t ui32t_num, uint8_t ui8t_numdigit)
{
    uint32_t ui32t_bcd;
    uint32_t ui32t_idx;
    boolean bt_isdisp;
    char cht_digit;
    
    /* 桁数上限ガード */
    if (ui8t_numdigit > IDX_8) {
        ui8t_numdigit = IDX_8;
    }
    
    /* 引数の値をBCD変換する */
    ui32t_bcd = BCD_UI32_to_BCD(ui32t_num);
    
    /* 表示フラグを設定 */
    bt_isdisp = FALSE;
    
    for (ui32t_idx = ui8t_numdigit; ui32t_idx > IDX_0; ui32t_idx--) {
        cht_digit = '0' + ((ui32t_bcd >> ((ui32t_idx - 1) * IDX_4)) & BCD_DIGIT);
        
        /* 0サプレス */
        if ((bt_isdisp == FALSE) && (cht_digit == '0') && (ui32t_idx != IDX_1)) {
            cht_digit = ' ';
            
        } else {
            bt_isdisp = TRUE;
        }
        
        LcdDrv_putchar(cht_digit);
    }
}


/**
 * @brief VRAMに数値を設定する 0サプレス無し
 * @param ui32t_num 数値
 * @param ui8t_numdigit 桁数
 * @note 画面バッファに収まらない文字サイズを指定した場合、
 *       左および上にロールオーバーされる
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setNumNoZeroSup(uint32_t ui32t_num, uint8_t ui8t_numdigit)
{
    uint32_t ui32t_bcd;
    uint32_t ui32t_idx;
    char cht_digit;
    
    /* 桁数上限ガード */
    if (ui8t_numdigit > IDX_8) {
        ui8t_numdigit = IDX_8;
    }
    
    /* 引数の値をBCD変換する */
    ui32t_bcd = BCD_UI32_to_BCD(ui32t_num);
    
    for (ui32t_idx = ui8t_numdigit; ui32t_idx > IDX_0; ui32t_idx--) {
        cht_digit = '0' + ((ui32t_bcd >> ((ui32t_idx - 1) * IDX_4)) & BCD_DIGIT);
        LcdDrv_putchar(cht_digit);
    }
}


/**
 * @brief VRAMに16進数を設定する
 * @param ui32t_num 数値
 * @param ui8t_numdigit 桁数
 * @note 画面バッファに収まらない文字サイズを指定した場合、
 *       左および上にロールオーバーされる
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setHex(uint32_t ui32t_num, uint8_t ui8t_numdigit)
{
    uint32_t ui32t_idx;
    char cht_digit;
    
    /* 桁数上限ガード */
    if (ui8t_numdigit > IDX_8) {
        ui8t_numdigit = IDX_8;
    }
    
    for (ui32t_idx = ui8t_numdigit; ui32t_idx > IDX_0; ui32t_idx--) {
        cht_digit = (ui32t_num >> ((ui32t_idx - 1) * IDX_4)) & BCD_DIGIT;
        
        if (IDX_10 <= cht_digit) {
            cht_digit = cht_digit + 'A' - IDX_10;
        } else {
            cht_digit = cht_digit + '0';
        }
        
        LcdDrv_putchar(cht_digit);
    }
}


/**
 * @brief VRAMに2進数を設定する
 * @param ui32t_num 数値
 * @param ui8t_numdigit 桁数
 * @note 画面バッファに収まらない文字サイズを指定した場合、
 *       左および上にロールオーバーされる
 * @note 文字の書き込み位置を指定するには、LcdDrv_setCursor()を使用する
 *       文字列を指定するとカーソルは自動的に更新される
 * @note 本関数を呼び出しただけでは実際のLCDは更新されない
 *       更新を反映するにはLcdDrv_Update()を呼び出す必要がある
 */
void LcdDrv_setBin(uint32_t ui32t_num, uint8_t ui8t_numdigit)
{
    uint32_t ui32t_idx;
    char cht_digit;

    /* 桁数上限ガード */
    if (ui8t_numdigit > IDX_16) {
        ui8t_numdigit = IDX_16;
    }

    for (ui32t_idx = ui8t_numdigit; ui32t_idx > IDX_0; ui32t_idx--) {
        cht_digit = (ui32t_num >> (ui32t_idx - 1)) & 0x1;

        cht_digit = cht_digit + '0';

        LcdDrv_putchar(cht_digit);
    }
}


/**
 * @brief LCDを更新する
 */
boolean LcdDrv_update(void)
{
    uint8_t ui8t_idx;

#if 0
    /* Active状態でない場合 */
    if (LcdDrv_State == LcdDrv_State_DISABLED) {
        return (FALSE);
    }
    
    /* 前回更新が完了していない */
    if (LcdDrv_UpdateFlag == TRUE) {
        return (FALSE);
    }
#endif
    
    /* VRAMをコピー */
    for (ui8t_idx = IDX_0; ui8t_idx < sizeof(LcdDrv_VRAM2); ui8t_idx++) {
        LcdDrv_VRAM2[ui8t_idx] = LcdDrv_VRAM1[ui8t_idx];
    }
    
    /* 更新フラグをセット */
    LcdDrv_UpdateFlag = TRUE;
    
    return (TRUE);
}


/**
 * @brief LCDドライバアクティブ時の処理 (LCD更新処理)
 */
static void LcdDrv_ActiveOperation(void)
{
    /* Active状態でない場合 */
    if (LcdDrv_State != LcdDrv_State_ACTIVE) {
        return;
    }
    
    
    /* 更新フラグが立っていない */
    if (LcdDrv_UpdateFlag == FALSE) {
        return;
    }
    
    /* 更新フラグをクリア */
    LcdDrv_UpdateFlag = FALSE;
    
    /* 0, 0に移動 */
    LcdDrv_WriteCommand(LcdDrv_CMD_SetCursor | (IDX_0 << IDX_6) | IDX_0);
    
    if (LcdDrv_WriteData(&LcdDrv_VRAM2[IDX_0], IDX_16) == FALSE) {
        return;
    }
    
    /* 0, 1に移動 */
    LcdDrv_WriteCommand(LcdDrv_CMD_SetCursor | (IDX_1 << IDX_6) | IDX_0);
    
    if (LcdDrv_WriteData(&LcdDrv_VRAM2[IDX_16], IDX_16) == FALSE) {
        return;
    }
    
    
    return;
}
