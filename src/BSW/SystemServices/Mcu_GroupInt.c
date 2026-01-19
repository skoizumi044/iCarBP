/**
 * @file Mcu_GroupInt.c
 * @brief グループ割り込み処理ハンドラ
 */

#include "Mcu.h"



/* Externs */
extern void Sci_ERIHandler(void);


/**
 * @brief 初期化
 */
void Mcu_GroupInt_Init(void)
{
    /* GROUPBE0割り込みレベルを設定 */
    Mcu_SFR_Write(IPR(ICU, GROUPBE0), 0);
    Mcu_SFR_Write(IEN(ICU, GROUPBE0), FALSE);

    /* GROUPBL0割り込みレベルを設定 */
    Mcu_SFR_Write(IPR(ICU, GROUPBL0), 9);
    Mcu_SFR_Write(IEN(ICU, GROUPBL0), TRUE);

    /* GROUPBL1割り込みレベルを設定 */
    Mcu_SFR_Write(IPR(ICU, GROUPBL1), 0);
    Mcu_SFR_Write(IEN(ICU, GROUPBL1), FALSE);

    /* GROUPBL2割り込みレベルを設定 */
    Mcu_SFR_Write(IPR(ICU, GROUPBL2), 0);
    Mcu_SFR_Write(IEN(ICU, GROUPBL2), FALSE);

    /* GROUPAL0割り込みレベルを設定 */
    Mcu_SFR_Write(IPR(ICU, GROUPAL0), 0);
    Mcu_SFR_Write(IEN(ICU, GROUPAL0), FALSE);

    /* GROUPAL1割り込みレベルを設定 */
    Mcu_SFR_Write(IPR(ICU, GROUPAL1), 0);
    Mcu_SFR_Write(IEN(ICU, GROUPAL1), FALSE);
}


/**
 * @brief GruopBE0割り込み
 * @note 本関数は割込みで呼び出しされる
 */
void __attribute__((interrupt)) Mcu_GroupInt_BE0Handler(void)
{
    /* コードを記載してください */
    /*
    if (Mcu_SFR_Read(IS(SCI1, ERI1) == TRUE))
    {
    }
    */
}


/**
 * @brief GruopBL0割り込み
 * @note 本関数は割込みで呼び出しされる
 */
void __attribute__((interrupt)) Mcu_GroupInt_BL0Handler(void)
{
    /* コードを記載してください */
    /*
    if (Mcu_SFR_Read(IS(SCI1, ERI1) == TRUE))
    {
    }
    */
    
    /* SCI1 ERI */
    if (Mcu_SFR_Read(IS(SCI1, ERI1) == TRUE))
    {
        Sci_ERIHandler();
    }
}


/**
 * @brief GruopBL1割り込み
 * @note 本関数は割込みで呼び出しされる
 */
void __attribute__((interrupt)) Mcu_GroupInt_BL1Handler(void)
{
    /* コードを記載してください */
    /*
    if (Mcu_SFR_Read(IS(SCI1, ERI1) == TRUE))
    {
    }
    */
}


/**
 * @brief GruopBL2割り込み
 * @note 本関数は割込みで呼び出しされる
 */
void __attribute__((interrupt)) Mcu_GroupInt_BL2Handler(void)
{
    /* コードを記載してください */
    /*
    if (Mcu_SFR_Read(IS(SCI1, ERI1) == TRUE))
    {
    }
    */
}


/**
 * @brief GruopAL0割り込み
 * @note 本関数は割込みで呼び出しされる
 */
void __attribute__((interrupt)) Mcu_GroupInt_AL0Handler(void)
{
    /* コードを記載してください */
    /*
    if (Mcu_SFR_Read(IS(SCI1, ERI1) == TRUE))
    {
    }
    */
}


/**
 * @brief GruopAL1割り込み
 * @note 本関数は割込みで呼び出しされる
 */
void __attribute__((interrupt)) Mcu_GroupInt_AL1Handler(void)
{
    /* コードを記載してください */
    /*
    if (Mcu_SFR_Read(IS(SCI1, ERI1) == TRUE))
    {
    }
    */
}
