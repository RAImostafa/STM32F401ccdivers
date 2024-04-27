#ifndef MCAL_SYSTICK_SYSTICK_H_
#define MCAL_SYSTICK_SYSTICK_H_


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include"LIB\Error_Status.h"
#include"LIB\Std_Types.h"
#include"LIB\Bit_Mask.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define   	SYSTICK_u32SRC_CLK_MASK                (u32)0x4
#define   	SYSTICK_u32ENABLE_MASK                 (u32)0x1
#define     SYSTICK_u32TICKINT_MASK                (u32)0x2

#define     SYSTICK_u8CLK_PROC_DIV_EIGHT           0
#define     SYSTICK_u8CLK_PROC                     1


//#define     SOURCE_CLK                             SYSTICK_u8CLK_PROC
#define     SOURCE_CLK                             SYSTICK_u8CLK_PROC_DIV_EIGHT 
#define     SYS_FREQUENCY                          16000000
#define     SYSTICK_MAX                            0x00FFFFFF
#define     MAX_ALLOWED_TIME_MS             ((SYSTICK_MAX * 1000) / (SYS_FREQUENCY / 1000))

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/


typedef void (*SystickCbf_t)(void);

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/




void Systick_vidInit();
void Systick_vidStart();
void Systick_vidStop();
E_ErrorStatus_t Systick_SetTicTime_ms(u32 Systick_u32TimeMs);
E_ErrorStatus_t Systick_SetTicTime_Tick(u32 Systick_u32setTick);
E_ErrorStatus_t Systick_RegisterCbf(SystickCbf_t Systick_Cbf);


#endif // MCAL_SYSTICK_SYSTICK_H_