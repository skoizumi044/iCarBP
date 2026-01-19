/**
 * @file CallGate.cpp
 * @brief ユーザプログラム呼び出しコード
 */


#include <board.h>
#include <BSW/SystemServices/SchM.h>


/* loop task Configuration */
#define LOOPTASK_ASYNC      (0)                 /* 非同期的にloop関数を呼び出し→setup/loop関数内でdelay関数/無限ループ処理使用可能 */
#define LOOPTASK_SYNC10MS   (1)                 /* 10ms定期でloop関数を呼び出し→setup/loop関数内は10ms以内に完了する必要がある, delay関数/無限ループ処理使用不可 */
#define LOOPTASK            (LOOPTASK_ASYNC)

#define INIT_WAITTIME       (100)

static int CallGate_isCalledSetup;          /**< setup関数呼び出し済みフラグ */
static int CallGate_isInitCompleted;        /**< 初期化完了フラグ */


/**
 * @brief 初期化
 * 初期化処理を記述
 */
extern "C" void CallGate_init(void)
{

#if LOOPTASK == LOOPTASK_ASYNC
    /* 非同期呼び出しの場合、ここではsetup関数を呼び出さず、初期化済みフラグをクリア */
    CallGate_isCalledSetup = 0;
    
#elif LOOPTASK == LOOPTASK_SYNC10MS
    /* 非同期呼び出しの場合、ここでsetup関数を呼び出す */
    setup();
    CallGate_isCalledSetup = 1;
    
#else
#endif
}


/**
 * @brief アイドル時処理
 * 他のドライバ処理を行っていない場合に実行する処理を記述
 */
extern "C" void CallGate_idle(void)
{
#if LOOPTASK == LOOPTASK_ASYNC
    /* 初期化済み？ */
    if (CallGate_isInitCompleted == 1)
    {
        /* 非同期呼び出しの場合 setup関数未呼び出しの場合呼び出す */
        if (CallGate_isCalledSetup == 0)
        {
            setup();
            /* setup関数呼び出し済みフラグを立てる */
            CallGate_isCalledSetup = 1;
        }

        /* loop関数を呼び出す */
        loop();
    }
    else
    {
        if (SchM_Get1msCounter() >= INIT_WAITTIME)
        {
            CallGate_isInitCompleted = 1;
        }
    }

#elif LOOPTASK == LOOPTASK_SYNC10MS
    /* 同期呼び出しの場合何もしない */
#else
#endif
}


/**
 * @brief 10ms定期処理
 * 10ms定期処理を記述
 */
extern "C" void CallGate_10ms(void)
{

#if LOOPTASK == LOOPTASK_ASYNC
    /* 非同期呼び出しの場合何もしない */

#elif LOOPTASK == LOOPTASK_SYNC10MS
    /* loop関数を呼び出す */
    loop();
#else
#endif
}


/**
 * @brief 1ms割り込み処理
 * 1ms割り込み処理を記述
 */
extern "C" void CallGate_int1ms(void)
{
}
