/**
 * @file Mtu3Drv.c
 * @brief Mtu3リソースの設定を行う
 */
#include <Std_Types.h>
#include <SystemServices/Mcu.h>

#include "Mtu3Drv.h"

uint16_t ui16_MTU0_carr;
uint16_t ui16_MTU0_tgra;
uint16_t ui16_MTU0_tgrb;
uint16_t ui16_MTU0_tgrd;

/**
 * @brief 初期化
 */
void Mtu3Drv_Init(void)
{
    /* レジスタプロテクト解除 */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY | Mcu_PRCR_PRC1));
    
    /* モジュールスタンバイ解除 */
    Mcu_SFR_Write(MSTP(MTU3), FALSE);
    
    /* レジスタプロテクト */
    Mcu_SFR_Write(SYSTEM.PRCR.WORD, (Mcu_PRCR_KEY));

    /* MTU0 A=FullColorLED      */
    /*      B=FullColorLED      */
    /*      C=-                 */
    /*      D=FullColorLED      */

    /* MTU3 A=-                 */
    /*      B=Motor_L_REV_Hi    */
    /*      C=-                 */
    /*      D=-                 */

    /* MTU4 A=Motor_L_FWD_Hi    */
    /*      B=Motor_R_FWD_Hi    */
    /*      C=-                 */
    /*      D=-                 */

    /* MTU6 A=-                 */
    /*      B=Motor_R_REV_Hi    */
    /*      C=-                 */
    /*      D=-                 */
    
    /* 入力可能周波数 20k-100k */
    /* Led /64 */
}


/**
 * @brief PWMを初期化
 * @param ui8t_ch Ch (Ch0のみ指定可能)
 * @param ui16t_carrier キャリア
 * @param ui16t_duty1
 * @param ui16t_duty2
 * @param ui16t_duty3
 */
void Mtu3Drv_PWM2_Init(uint8_t ui8t_ch, uint16_t ui16t_carrier, uint16_t ui16t_duty1, uint16_t ui16t_duty2, uint16_t ui16t_duty3)
{
    /* タイマを停止 */
    Mcu_SFR_WriteBit(&MTU.TSTRA.BYTE, 0, 0);
    
    /* カウントクロックを選択 */
    Mcu_SFR_Write(MTU0.TCR.BYTE, 0xA3);
    Mcu_SFR_Write(MTU0.TCR2.BYTE, 0x00);
    
    /* カウンタ初期化 */
    Mcu_SFR_Write(MTU0.TCNT, 0);
    
    /* Duty設定 */
    Mcu_SFR_Write(MTU0.TGRA, ui16t_duty1);
    Mcu_SFR_Write(MTU0.TGRB, ui16t_duty2);
    Mcu_SFR_Write(MTU0.TGRD, ui16t_duty3);
    
    /* キャリアを設定 */
    if( ui16t_carrier >= 0xffff )
    {
        ui16t_carrier = 0xfffe;
    }
    ui16_MTU0_carr = ui16t_carrier;
    Mcu_SFR_Write(MTU0.TGRC, ui16t_carrier);
    
    /* PWMモード2設定 */
    Mcu_SFR_Write(MTU0.TMDR1.BYTE, 0x03);
    
    /* タイマI/O設定 */
    /* LED */
    Mcu_SFR_Write(MTU0.TIORH.BYTE, 0x22u);
    Mcu_SFR_Write(MTU0.TIORL.BYTE, 0x20u);
    
    /* 割り込み許可 */
    Mcu_SFR_Write(MTU0.TIER.BYTE, 0x0Bu);

    /* 選択型割り込みA設定 */
    Mcu_SFR_Write(ICU.SLIAR208.BYTE, 1);
    Mcu_SFR_Write(ICU.SLIAR209.BYTE, 2);
    Mcu_SFR_Write(ICU.SLIAR210.BYTE, 4);

    /* 割り込みレベルを設定 */
    Mcu_SFR_Write(IPR(PERIA, INTA208), 9);
    Mcu_SFR_Write(IPR(PERIA, INTA209), 9);
    Mcu_SFR_Write(IPR(PERIA, INTA210), 9);

    /* まだ割り込み禁止 */
    Mcu_SFR_Write(IEN(PERIA, INTA208), FALSE);
    Mcu_SFR_Write(IEN(PERIA, INTA209), FALSE);
    Mcu_SFR_Write(IEN(PERIA, INTA210), FALSE);

    /* タイマ開始 */
    Mcu_SFR_WriteBit(&MTU.TSTRA.BYTE, 0, 1);
}


/**
 * @brief PWMのDUTYを設定
 * @param ui8t_ch Ch (Ch0のみ指定可能)
 * @param ui16t_duty1
 * @param ui16t_duty2
 * @param ui16t_duty3
 */
void Mtu3Drv_PWM2_SetDuty(uint8_t ui8t_ch, uint16_t ui16t_duty1, uint16_t ui16t_duty2, uint16_t ui16t_duty3)
{
    /* Duty 100%時に+1しないとON/OFFが不定になることがある？マイコンメーカに要確認 */
    if( ui16_MTU0_carr == ui16t_duty1 )
    {
        ui16t_duty1++;
    }
    if( ui16_MTU0_carr == ui16t_duty2 )
    {
        ui16t_duty2++;
    }
    if( ui16_MTU0_carr == ui16t_duty3 )
    {
        ui16t_duty3++;
    }

    /* Duty更新用にコンペアマッチ割り込み許可 ただし現Duty100%時はコンペアマッチが発生しないのでここで直接更新 */
    Mcu_SFR_Write(IEN(PERIA, INTA208), FALSE);
    ui16_MTU0_tgra = ui16t_duty1;
    if( ui16_MTU0_carr < Mcu_SFR_Read(MTU0.TGRA) ) {  /* 100%(キャリア+1)設定時は割り込み発生しないのでココで書き込む */
        Mcu_SFR_Write(MTU0.TGRA, ui16_MTU0_tgra);
    }
    else {
        /* 割り込み要求クリアしてから許可 */
        Mcu_SFR_Write(IR(PERIA, INTA208), FALSE);
        Mcu_SFR_Write(IEN(PERIA, INTA208), TRUE);
    }

    Mcu_SFR_Write(IEN(PERIA, INTA209), FALSE);
    ui16_MTU0_tgrb = ui16t_duty2;
    if( ui16_MTU0_carr < Mcu_SFR_Read(MTU0.TGRB) ) {
        Mcu_SFR_Write(MTU0.TGRB, ui16_MTU0_tgrb);
    }
    else {
        Mcu_SFR_Write(IR(PERIA, INTA209), FALSE);
        Mcu_SFR_Write(IEN(PERIA, INTA209), TRUE);
    }

    Mcu_SFR_Write(IEN(PERIA, INTA210), FALSE);
    ui16_MTU0_tgrd = ui16t_duty3;
    if( ui16_MTU0_carr < Mcu_SFR_Read(MTU0.TGRD) ) {
        Mcu_SFR_Write(MTU0.TGRD, ui16_MTU0_tgrd);
    }
    else {
        Mcu_SFR_Write(IR(PERIA, INTA210), FALSE);
        Mcu_SFR_Write(IEN(PERIA, INTA210), TRUE);
    }
}

/**
 * @brief MTU0 TGRA割り込み
 */
void __attribute__((interrupt)) Mtu3_MTU0_TGRA(void)
{
    Mcu_SFR_Write(IEN(PERIA, INTA208), FALSE);

    Mcu_SFR_Write(MTU0.TGRA, ui16_MTU0_tgra);
}

/**
 * @brief MTU0 TGRB割り込み
 */
void __attribute__((interrupt)) Mtu3_MTU0_TGRB(void)
{
    Mcu_SFR_Write(IEN(PERIA, INTA209), FALSE);

    Mcu_SFR_Write(MTU0.TGRB, ui16_MTU0_tgrb);
}

/**
 * @brief MTU0 TGRD割り込み
 */
void __attribute__((interrupt)) Mtu3_MTU0_TGRD(void)
{
    Mcu_SFR_Write(IEN(PERIA, INTA210), FALSE);

    Mcu_SFR_Write(MTU0.TGRD, ui16_MTU0_tgrd);
}

/**
 * @brief 相補PWMを初期化
 * @param ui8t_ch Ch (Ch3 or Ch6のみ指定可能)
 * @param ui16t_carrier キャリア
 * @param ui16t_deadtime デッドタイム (0=なし)
 * @param ui16t_duty1 Ch_(n+0)Bに出力するDuty
 * @param ui16t_duty2 Ch_(n+1)Aに出力するDuty
 * @param ui16t_duty3 Ch_(n+1)Bに出力するDuty
 */
void Mtu3Drv_CompPWM_Init(uint8_t ui8t_ch, uint16_t ui16t_carrier, uint16_t ui16t_deadtime, uint16_t ui16t_duty1, uint16_t ui16t_duty2, uint16_t ui16t_duty3)
{
    if (ui8t_ch == Mtu3Drv_CH3) {
        /* タイマリードライト許可 */
        Mcu_SFR_Write(MTU.TRWERA.BYTE, 0x01);
        
        /* MTU出力許可設定 */
        /* 3B, 4A, 4Bを許可 */
        /* 3D, 4C, 4Dは予約のため禁止 */
        Mcu_SFR_Write(MTU.TOERA.BYTE, 0xC7u);
        
        /* タイマを停止 */
        Mcu_SFR_WriteBit(&MTU.TSTRA.BYTE, 7, 0);
        Mcu_SFR_WriteBit(&MTU.TSTRA.BYTE, 6, 0);
        
        /* カウントクロックを選択 */
        Mcu_SFR_Write(MTU3.TCR.BYTE, 0x00);
        Mcu_SFR_Write(MTU3.TCR2.BYTE, 0x00);
        
        Mcu_SFR_Write(MTU4.TCR.BYTE, 0x00);
        Mcu_SFR_Write(MTU4.TCR2.BYTE, 0x00);
        
        /* Duty設定 */
        Mcu_SFR_Write(MTU3.TGRB, ui16t_duty1);
        Mcu_SFR_Write(MTU4.TGRA, ui16t_duty2);
        Mcu_SFR_Write(MTU4.TGRB, ui16t_duty3);
        
        Mcu_SFR_Write(MTU3.TGRD, ui16t_duty1);
        Mcu_SFR_Write(MTU4.TGRC, ui16t_duty2);
        Mcu_SFR_Write(MTU4.TGRD, ui16t_duty3);
        
        /* デッドタイムを設定 */
        if (ui16t_deadtime == 0) {
            Mcu_SFR_Write(MTU.TDERA.BYTE, 0x00);
            ui16t_deadtime = 1;
        }
        Mcu_SFR_Write(MTU.TDDRA, ui16t_deadtime);
        
        /* カウンタ初期値を設定 */
        Mcu_SFR_Write(MTU3.TCNT, ui16t_deadtime);
        /* MTU4.TCNTを0設定 */
        Mcu_SFR_Write(MTU4.TCNT, 0);
        
        /* キャリアを設定 */
        Mcu_SFR_Write(MTU.TCDRA, ui16t_carrier);
        Mcu_SFR_Write(MTU.TCBRA, ui16t_carrier);
        
        Mcu_SFR_Write(MTU3.TGRA, ui16t_carrier + ui16t_deadtime);
        Mcu_SFR_Write(MTU3.TGRC, ui16t_carrier + ui16t_deadtime);
        
        /* PWM出力レベル設定 */
        Mcu_SFR_Write(MTU.TOCR1A.BYTE, 0x01);
        
        /* 相補PWMモード設定 */
        Mcu_SFR_Write(MTU3.TMDR1.BYTE, 0x3D);
        
        /* 端子設定 */
        Mcu_SFR_Write(MTU3.TIORH.BYTE, 0x00u);
        Mcu_SFR_Write(MTU3.TIORL.BYTE, 0x00u);
        Mcu_SFR_Write(MTU4.TIORH.BYTE, 0x00u);
        Mcu_SFR_Write(MTU4.TIORL.BYTE, 0x00u);

        /* タイマリードライト禁止 */
        /*Mcu_SFR_Write(MTU.TRWERA.BYTE, 0x00);*/
        
    } else if (ui8t_ch == Mtu3Drv_CH6) {
        /* タイマリードライト許可 */
        Mcu_SFR_Write(MTU.TRWERB.BYTE, 0x01);
        
        /* MTU出力許可設定 */
        /* 6Bを許可 */
        /* 6Dは予約のため禁止 */
        Mcu_SFR_Write(MTU.TOERB.BYTE, 0xC1u);
        
        /* タイマを停止 */
        Mcu_SFR_WriteBit(&MTU.TSTRB.BYTE, 7, 0);
        Mcu_SFR_WriteBit(&MTU.TSTRB.BYTE, 6, 0);
        
        /* カウントクロックを選択 */
        Mcu_SFR_Write(MTU6.TCR.BYTE, 0x00);
        Mcu_SFR_Write(MTU6.TCR2.BYTE, 0x00);
        
        Mcu_SFR_Write(MTU7.TCR.BYTE, 0x00);
        Mcu_SFR_Write(MTU7.TCR2.BYTE, 0x00);
        
        /* Duty設定 */
        Mcu_SFR_Write(MTU6.TGRB, ui16t_duty1);
        Mcu_SFR_Write(MTU7.TGRA, ui16t_duty2);
        Mcu_SFR_Write(MTU7.TGRB, ui16t_duty3);
        
        Mcu_SFR_Write(MTU6.TGRD, ui16t_duty1);
        Mcu_SFR_Write(MTU7.TGRC, ui16t_duty2);
        Mcu_SFR_Write(MTU7.TGRD, ui16t_duty3);
        
        /* デッドタイムを設定 */
        if (ui16t_deadtime == 0) {
            Mcu_SFR_Write(MTU.TDERB.BYTE, 0x00);
            ui16t_deadtime = 1;
        }
        Mcu_SFR_Write(MTU.TDDRB, ui16t_deadtime);
        
        /* カウンタ初期値を設定 */
        Mcu_SFR_Write(MTU6.TCNT, ui16t_deadtime);
        /* MTU7.TCNTを0設定 */
        Mcu_SFR_Write(MTU7.TCNT, 0);
        
        /* キャリアを設定 */
        Mcu_SFR_Write(MTU.TCDRB, ui16t_carrier);
        Mcu_SFR_Write(MTU.TCBRB, ui16t_carrier);
        
        Mcu_SFR_Write(MTU6.TGRA, ui16t_carrier + ui16t_deadtime);
        Mcu_SFR_Write(MTU6.TGRC, ui16t_carrier + ui16t_deadtime);
        
        /* PWM出力レベル設定 */
        Mcu_SFR_Write(MTU.TOCR1B.BYTE, 0x01);
        
        /* 相補PWMモード設定 */
        Mcu_SFR_Write(MTU6.TMDR1.BYTE, 0x3D);
        
        /* 端子設定 */
        Mcu_SFR_Write(MTU6.TIORH.BYTE, 0x00u);
        Mcu_SFR_Write(MTU6.TIORL.BYTE, 0x00u);
        Mcu_SFR_Write(MTU7.TIORH.BYTE, 0x00u);
        Mcu_SFR_Write(MTU7.TIORL.BYTE, 0x00u);
        
        /* タイマリードライト禁止 */
        /*Mcu_SFR_Write(MTU.TRWERB.BYTE, 0x00);*/
    }
}


/**
 * @brief 相補PWMを開始
 * @param bt_mtu3_start Ch3開始
 * @param bt_mtu6_start Ch6開始
 */
void Mtu3Drv_CompPWM_Start(boolean bt_mtu3_start, boolean bt_mtu6_start)
{
    uint8_t ui8t_regset;
    
    ui8t_regset = 0x00;
    if (bt_mtu3_start == TRUE) {
        ui8t_regset |= 0x18;
    }
    
    if (bt_mtu6_start == TRUE) {
        ui8t_regset |= 0x03;
    }
    
    /* MTU3,4,6,7 同時スタート */
    Mcu_SFR_Write(MTU.TCSYSTR.BYTE, ui8t_regset);
}


/**
 * @brief 相補PWMのDutyを設定
 * @param ui8t_ch ch (指定可能な値・・・ch3 or ch6)
 * @param ui16t_duty1 Ch_(n+0)Bに出力するDuty
 * @param ui16t_duty2 Ch_(n+1)Aに出力するDuty
 * @param ui16t_duty3 Ch_(n+1)Bに出力するDuty
 * @note 指定不能なchを指定した場合何もしない
 * @note Mtu3Drv_CH3指定時、以下Ch設定となる
 *       ui16t_duty1・・・Ch3B
 *       ui16t_duty2・・・Ch4A
 *       ui16t_duty3・・・Ch4B
 */
void Mtu3Drv_CompPWM_SetDuty(uint8_t ui8t_ch, uint16_t ui16t_duty1, uint16_t ui16t_duty2, uint16_t ui16t_duty3)
{
    /* MTU34 */
    if (ui8t_ch == Mtu3Drv_CH3) {
        /* タイマリードライト許可 */
        Mcu_SFR_Write(MTU.TRWERA.BYTE, 0x01);
        
        Mcu_SFR_Write(MTU3.TGRD, ui16t_duty1);
        Mcu_SFR_Write(MTU4.TGRC, ui16t_duty2);
        Mcu_SFR_Write(MTU4.TGRD, ui16t_duty3);
        
        /* タイマリードライト禁止 */
        /*Mcu_SFR_Write(MTU.TRWERA.BYTE, 0x00);*/

    /* MTU67 */
    } else if (ui8t_ch == Mtu3Drv_CH6) {
        /* タイマリードライト許可 */
        Mcu_SFR_Write(MTU.TRWERB.BYTE, 0x01);
        
        Mcu_SFR_Write(MTU6.TGRD, ui16t_duty1);
        Mcu_SFR_Write(MTU7.TGRC, ui16t_duty2);
        Mcu_SFR_Write(MTU7.TGRD, ui16t_duty3);
        
        /* タイマリードライト禁止 */
        /*Mcu_SFR_Write(MTU.TRWERB.BYTE, 0x00);*/
    } else {
        /* なにもしない */
    }
}


/**
 * @brief 相補PWMのDutyを取得
 * @param ui8t_ch ch (指定可能な値・・・ch3 or ch6)
 * @param ui16tp_duty1 Ch_(n+0)BのDutyを格納するポインタ NULL指定時は設定しない
 * @param ui16tp_duty2 Ch_(n+1)AのDutyを格納するポインタ NULL指定時は設定しない
 * @param ui16tp_duty3 Ch_(n+1)BのDutyを格納するポインタ NULL指定時は設定しない
 * @note 指定不能なchを指定した場合何もしない
 * @note Mtu3Drv_CH3指定時、以下Chの設定値が格納される
 *       ui16tp_duty1・・・Ch3B
 *       ui16tp_duty2・・・Ch4A
 *       ui16tp_duty3・・・Ch4B
 */
void Mtu3Drv_CompPWM_GetDuty(uint8_t ui8t_ch, uint16_t *ui16tp_duty1, uint16_t *ui16tp_duty2, uint16_t *ui16tp_duty3)
{
    /* MTU34 */
    if (ui8t_ch == Mtu3Drv_CH3) {
        /* タイマリードライト許可 */
        Mcu_SFR_Write(MTU.TRWERA.BYTE, 0x01);
        
        if (ui16tp_duty1 != NULL) {
            *ui16tp_duty1 = Mcu_SFR_Read(MTU3.TGRD);
        }
        if (ui16tp_duty2 != NULL) {
            *ui16tp_duty2 = Mcu_SFR_Read(MTU4.TGRC);
        }
        if (ui16tp_duty3 != NULL) {
            *ui16tp_duty3 = Mcu_SFR_Read(MTU4.TGRD);
        }
        
        /* タイマリードライト禁止 */
        /*Mcu_SFR_Write(MTU.TRWERA.BYTE, 0x00);*/
        
    /* MTU67 */
    } else if (ui8t_ch == Mtu3Drv_CH6) {
        /* タイマリードライト許可 */
        Mcu_SFR_Write(MTU.TRWERB.BYTE, 0x01);
        
        if (ui16tp_duty1 != NULL) {
            *ui16tp_duty1 = Mcu_SFR_Read(MTU6.TGRD);
        }
        if (ui16tp_duty2 != NULL) {
            *ui16tp_duty2 = Mcu_SFR_Read(MTU7.TGRC);
        }
        if (ui16tp_duty3 != NULL) {
            *ui16tp_duty3 = Mcu_SFR_Read(MTU7.TGRD);
        }
        
        /* タイマリードライト禁止 */
        /*Mcu_SFR_Write(MTU.TRWERB.BYTE, 0x00);*/
    } else {
        /* なにもしない */
    }
}
