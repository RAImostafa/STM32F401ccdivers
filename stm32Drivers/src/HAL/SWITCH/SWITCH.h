#ifndef HAL_SWITCH_SWITCH_H_
#define HAL_SWITCH_SWITCH_H_





/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include"LIB\Error_Status.h"
#include"LIB\Std_Types.h"
#include"LIB\Bit_Mask.h"


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/


typedef enum { 
 SWI_High_Active = 1,	 
 SWI_LOW_Active = 0, 
}SWITCH_Activity_t;

typedef enum { 
SWI_PULL_UP,
SWI_PULL_DOWN
}SWITCH_Internal_State_t;

/* Enumeration for Switch states (pressed/released) */

/*pull up and pin is zero = not pressed */
/*pull down and pin is zero = pressed */
typedef enum {
    SWITCH_RELEASED = 0x00000000,  
    SWITCH_PRESSED = 0x00000001,   
} SWITCH_StateType_t;

typedef struct{
    u32 port;
    u8 pin;
    SWITCH_Internal_State_t SWI_InternalStatus; 
	SWITCH_Activity_t SWI_ActiveType;	
}SWI_strState_t;




/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

E_ErrorStatus_t SWI_init(void);

u8 SWI_getSwiState(u8 SWI_NUM );








#endif // HAL_SWITCH_SWITCH_H_