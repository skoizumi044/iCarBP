/**
 * @file IODrv.c
 * @brief IO Driver
 */

#include <Std_Types.h>
#include <SystemServices/Mcu.h>

#include "Adc.h"


#define IODrv_ADC_UNIT_VOLUME              (0u)
#define IODrv_ADC_CH_VOLUME                (6u)

#define IODrv_ADC_UNIT_V3_3                (1u)
#define IODrv_ADC_CH_V3_3                  (5u)

#define IODrv_ADC_UNIT_V5                  (1u)
#define IODrv_ADC_CH_V5                    (4u)

#define IODrv_ADC_UNIT_BRIGHTNESS          (0u)
#define IODrv_ADC_CH_BRIGHTNESS            (5u)


#define IODrv_AD_MAX                       (4095)
#define IODrv_Brightness_Num   (50)


const int IODrv_Ill_Brightness_Invalid = 4095;


int IODrv_Switch1Up;
int IODrv_Switch1Down;
int IODrv_Volume;
int IODrv_Ill_Brightness;


#define BrightnessState_INIT    (0x00)
#define BrightnessState_CAL     (0x01)

static uint8_t ui8g_brightness_state = BrightnessState_INIT;
static uint16_t ui16g_brightness_cnt = VAL_0;
static uint32_t ui32g_brightness_sum = VAL_0;
static uint16_t ui16ag_brightness_buf[IODrv_Brightness_Num];


static uint16_t ui16g_ad_vol;
static uint16_t ui16g_ad_ref;
static uint8_t ui8g_volparc;


static uint8_t IODrv_CalVolume(void);
static void IODrv_SmplBrightness(void);
static void IODrv_CalBrightness(void);


/**
 * @brief Volume位置を取得
 * @return Volume位置 (0～100)
 */
static uint8_t IODrv_CalVolume(void)
{
    
    /* 3.3V端子のA/D値を取得 */
    ui16g_ad_ref = Adc_Read(IODrv_ADC_UNIT_V3_3, IODrv_ADC_CH_V3_3);
    
    /* Volume端子のA/D値を取得 */
    ui16g_ad_vol = Adc_Read(IODrv_ADC_UNIT_VOLUME, IODrv_ADC_CH_VOLUME);
    
    /* Volume位置を算出 (100%となるように最大AD値から20引いた値で割る) */
    ui8g_volparc = (((uint32_t)(ui16g_ad_vol & 0xFFF)) * (uint32_t)100) / (uint32_t)(IODrv_AD_MAX - 20);
    
    return (ui8g_volparc);
}


/**
 * @brief 輝度を取得
 */
static void IODrv_SmplBrightness(void)
{
    uint16_t ui16t_adBuf;
    
    /* 移動平均バッファから減算 */
    if (ui8g_brightness_state == BrightnessState_CAL) {
        ui32g_brightness_sum -= ui16ag_brightness_buf[ui16g_brightness_cnt];
    }
    
    /* AD値を取得 */
    ui16t_adBuf = Adc_Read(IODrv_ADC_UNIT_BRIGHTNESS, IODrv_ADC_CH_BRIGHTNESS);
    
    /* 移動平均バッファに加算 */
    ui32g_brightness_sum += ui16t_adBuf;
    ui16ag_brightness_buf[ui16g_brightness_cnt] = ui16t_adBuf;
    
    /* 平均回数を加算 */
    ui16g_brightness_cnt++;
    
    /* 規定平均回数に到達したら */
    if (ui16g_brightness_cnt >= IODrv_Brightness_Num) {
        /* 積算状態に遷移 */
        ui8g_brightness_state = BrightnessState_CAL;
        ui16g_brightness_cnt = VAL_0;
    }
}


/**
 * @brief 輝度を算出
 */
static void IODrv_CalBrightness(void)
{
    if (ui8g_brightness_state == BrightnessState_CAL) {
        IODrv_Ill_Brightness = ui32g_brightness_sum / IODrv_Brightness_Num;
        
    } else {
        IODrv_Ill_Brightness = IODrv_Ill_Brightness_Invalid;
    }
}


/**
 * @brief 定期処理
 * @note 10ms定期で呼び出しすること
 */
void IODrv_Periodic(void)
{
    uint16_t ui16t_tsw1ad;
    uint16_t ui16t_tsw2ad;

    ui16t_tsw1ad = Adc_Read(1, 9);
    ui16t_tsw2ad = Adc_Read(1, 10);

    if (ui16t_tsw1ad <= 256)
    {
        IODrv_Switch1Up = FALSE;
        IODrv_Switch1Down = TRUE;
    }
    else if (ui16t_tsw1ad <= 2048+256)
    {
        IODrv_Switch1Up = TRUE;
        IODrv_Switch1Down = FALSE;
    }
    else
    {
        IODrv_Switch1Up = FALSE;
        IODrv_Switch1Down = FALSE;
    }
    
    IODrv_Volume = IODrv_CalVolume();
    IODrv_CalBrightness();
}


/**
 * @brief 1ms定期処理
 * @note A/D変換実行後に呼び出しすること
 */
void IODrv_1msInt(void)
{
    IODrv_SmplBrightness();
}


/**
 * @brief スライドボリュームの現在位置を返す
 * @return 0～100
 */
int IODrv_Volume_Get(void)
{
    return (IODrv_Volume);
}


/**
 * @brief 照度センサで取得した周囲の明るさを返す
 * @return 0=明るい～4095=暗い
 * @note 本関数は起動直後の未確定時にIODrv_Ill_Brightness_Invalidを返す
 */
int IODrv_Ill_GetBrightness(void)
{
    return (IODrv_Ill_Brightness);
}


/**
 * @brief トグルスイッチ状態を取得
 * @return 0=下段, 1=中段, 2=上段
 */
int IODrv_Toggle_Get(void)
{
    int ret;
    
    if (IODrv_Switch1Up)
    {
        ret = 2;
    }
    else if (IODrv_Switch1Down)
    {
        ret = 0;
    }
    else
    {
        ret = 1;
    }
    
    return (ret);
}
