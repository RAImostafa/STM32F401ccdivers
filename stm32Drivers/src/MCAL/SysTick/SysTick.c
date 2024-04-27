
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include"LIB\Error_Status.h"
#include"LIB\Std_Types.h"
#include"LIB\Bit_Mask.h"
#include"MCAL/GPIO/GPIO.h"
#include"SysTick.h"



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define   SYSTICK_BASE_ADDRESS           (u32)(0xE000E010)

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/


typedef struct{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}Systick_t;

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/


static SystickCbf_t AppCbf;
static Systick_t * const Systick = ( Systick_t * const ) SYSTICK_BASE_ADDRESS;
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/





/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


void Systick_vidInit()
{
	u32 Loc_u32reg;

	Loc_u32reg = Systick -> STK_CTRL ;
	Loc_u32reg &= ~(SYSTICK_u32TICKINT_MASK ); //clearing the CTRL register "TICKINT"
	Loc_u32reg |= SYSTICK_u32TICKINT_MASK;     //Counting down to zero to asserts the SysTick exception request
	Loc_u32reg &= ~(SYSTICK_u32SRC_CLK_MASK ); // clearing the Clock source selection bit
	if ( SOURCE_CLK == SYSTICK_u8CLK_PROC )
		 Loc_u32reg |= SYSTICK_u32SRC_CLK_MASK ;
	Systick -> STK_CTRL = Loc_u32reg;
}


E_ErrorStatus_t Systick_SetTicTime_ms(u32 Copy_u32TimeMs)
{
    E_ErrorStatus_t Systick_ErrorStatus_t = E_OK;
    f32 timeInTicks;

    if (Copy_u32TimeMs > MAX_ALLOWED_TIME_MS)
    {
        // Requested time exceeds the maximum allowed time
        Systick_ErrorStatus_t = E_NOK;
    }
    else
    {
        // Calculate the number of ticks needed for the given time in milliseconds
        timeInTicks = ((float)(SYS_FREQUENCY / 1000.0)) * Copy_u32TimeMs;

        // Load the calculated tick value into STK_LOAD register
        Systick->STK_LOAD = timeInTicks-1; // Adjusted by -1 since the counter counts down from the value loaded
        // Start the SysTick timer
        Systick->STK_CTRL |= (1 << 0); // Enable SysTick
    }

    return Systick_ErrorStatus_t;
}




E_ErrorStatus_t Systick_RegisterCbf(SystickCbf_t Copy_Cbf)
{
	E_ErrorStatus_t Systick_ErrorStatus_t = E_NOK;

	if(Copy_Cbf)
		AppCbf = Copy_Cbf;
	else
		 Systick_ErrorStatus_t = E_NOK;

	return  Systick_ErrorStatus_t;
}

void Systick_vidStart()
{
	u32 Loc_u32reg;

	Loc_u32reg = Systick -> STK_CTRL;

	Loc_u32reg &= ~SYSTICK_u32ENABLE_MASK ;
	Systick -> STK_CTRL = Loc_u32reg | SYSTICK_u32ENABLE_MASK ;

}

void Systick_vidStop()
{

		u32 Loc_u32reg;

	Loc_u32reg = Systick -> STK_CTRL;

	Loc_u32reg &= ~SYSTICK_u32ENABLE_MASK ;
	Systick -> STK_CTRL = Loc_u32reg;
	Systick->STK_LOAD=0;
    Systick->STK_VAL=0;
}

void SysTick_Handler(void)
{
 //GPIO_SetPinValue(PORT_NAME_A , PIN_NUM_0 , GPIO_HIGH);
   AppCbf();  // Execute the user-defined callback function (if set) --> ptr() --> user function


}