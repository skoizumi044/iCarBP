/**
 * @file IODrv.h
 * @brief IO Driver
 */

#ifndef __IODrv_H
#define __IODrv_H


#ifdef __cplusplus
extern "C" {
#endif


const int IODrv_Ill_Brightness_Invalid;


void IODrv_Periodic(void);
void IODrv_1msInt(void);


int IODrv_Volume_Get(void);
int IODrv_Ill_GetBrightness(void);
int IODrv_Toggle_Get(void);


#ifdef __cplusplus
}
#endif


#endif
