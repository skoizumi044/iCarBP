/**
 * @file Distance.h
 * @brief 超音波センサによる距離測定
 */

#ifndef __Distance_H
#define __Distance_H


#ifdef __cplusplus
extern "C" {
#endif


#define Distance_INFINITY           (6027)


void Distance_Init(void);
void Distance_Periodic(void);
uint32_t Distance_GetValue(void);
boolean Distance_GetIsValid(void);


#ifdef __cplusplus
}
#endif


#endif
