#ifndef MCAL_NVIC_NVIC_H_
#define MCAL_NVIC_NVIC_H_




/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include"interrupts.h"
#include"LIB\Error_Status.h"
#include"LIB\Std_Types.h"
#include"LIB\Bit_Mask.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/*Enables the given interrupt*/
E_ErrorStatus_t NVIC_EnableInterrupt(u8 NVIC_InterruptID);


/*Disables the given interrupt*/
E_ErrorStatus_t NVIC_DisableInterrupt(u8 NVIC_InterruptID);


/*Sets the pending state for the given interrupt*/
E_ErrorStatus_t NVIC_SetPending(u8 NVIC_InterruptID);


/*Clears the pending state for the given interrupt*/
E_ErrorStatus_t NVIC_ClearPending(u8 NVIC_InterruptID);


/* Returns wether the given interrupt is pending or not*/
E_ErrorStatus_t NVIC_GetPending(u8 NVIC_InterruptID, u8 *Add_ReturnPending);


/*Returns wether the given interrupt is active or not*/
E_ErrorStatus_t NVIC_GetActive(u8 NVIC_InterruptID, u8* Add_ReturnActive);


/*Sets the priority for the given interrupt*/
E_ErrorStatus_t NVIC_SetPeriority(u8 NVIC_InterruptID, u8 NVIC_Periority);


/*Gets the priority for the given interrupt*/
E_ErrorStatus_t NVIC_GetPeriority(u8 NVIC_InterruptID, u8 *NVIC_Periority);



#endif // MCAL_NVIC_NVIC_H_