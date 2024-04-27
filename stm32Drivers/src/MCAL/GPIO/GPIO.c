#include"GPIO.h"

#define GPIO_MODE_MASK      0x00000003
#define GPIO_MODER_MASK     0xFFFFFFFF 
#define GPIO_OTYPE_MASK     0x00000004
#define GPIO_CLEAR_MASK     0x00000003
#define GPIO_CLEAR_MASK_    0x0000000F
#define GPIO_SET_ALL_BITS_MASK  0x55555555





typedef struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDT;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIOReg_t;



E_ErrorStatus_t GPIO_SetPinConfig(GPIO_PIN_config_t * local_newPinStr)
{

	E_ErrorStatus_t GPIO_Error=  E_OK;


	if((local_newPinStr->GPIOPin)> 15 )
	{
		return GPIO_Error=  E_NOK;
	}
	else
	{

	   ((GPIOReg_t*)(local_newPinStr->GPIOPort))->MODER&= ~(GPIO_CLEAR_MASK << (local_newPinStr->GPIOPin) * 2);
       ((GPIOReg_t*)(local_newPinStr->GPIOPort))->MODER |= ( local_newPinStr->GPIOMode<< (local_newPinStr->GPIOPin) * 2);

       ((GPIOReg_t*)(local_newPinStr->GPIOPort))->OTYPER &=~(GPIO_CLEAR_MASK<<(local_newPinStr->GPIOPin));
       ((GPIOReg_t*)(local_newPinStr->GPIOPort))->OTYPER|= (local_newPinStr->GPIO_OUTPUTTYPE<<(local_newPinStr->GPIOPin));

       ((GPIOReg_t*)(local_newPinStr->GPIOPort))->PUPDR &=~(GPIO_CLEAR_MASK<<(local_newPinStr->GPIOPin)*2);
       ((GPIOReg_t*)(local_newPinStr->GPIOPort))->PUPDR |= (local_newPinStr->GPIO_INPUTTYPE<<(local_newPinStr->GPIOPin)*2);

       ((GPIOReg_t*)(local_newPinStr->GPIOPort))->OSPEEDT &=~(GPIO_CLEAR_MASK<<(local_newPinStr->GPIOPin)*2);
       ((GPIOReg_t*)(local_newPinStr->GPIOPort))->OSPEEDT |= (local_newPinStr->GPIOSpeed<<(local_newPinStr->GPIOPin)*2);
       
	  ((GPIOReg_t*)(local_newPinStr->GPIOPort))->ODR &=~(GPIO_CLEAR_MASK<<(local_newPinStr->GPIOPin)*1);
      ((GPIOReg_t*)(local_newPinStr->GPIOPort))->ODR |= (local_newPinStr->GPIOValue<<(local_newPinStr->GPIOPin)*1);

    if (local_newPinStr->GPIOMode == GPIO_Mod_AF)
	{
		if(local_newPinStr->GPIOPin < 8)
		{
        ((GPIOReg_t*)(local_newPinStr->GPIOPort))-> AFRL &=~(GPIO_CLEAR_MASK_<<(local_newPinStr->GPIOPin)*4);
       ((GPIOReg_t*)(local_newPinStr->GPIOPort))-> AFRL|= (local_newPinStr-> AF_ID<<(local_newPinStr->GPIOPin)*4);
		}
	else {
    ((GPIOReg_t*)(local_newPinStr->GPIOPort))-> AFRH &=~(GPIO_CLEAR_MASK_<<(((local_newPinStr->GPIOPin)-8)*4));
    ((GPIOReg_t*)(local_newPinStr->GPIOPort))-> AFRH|= ((local_newPinStr-> AF_ID)<<(((local_newPinStr->GPIOPin)-8)*4));

		}
	}


       GPIO_Error=  E_OK;

	}
	return GPIO_Error;

}


E_ErrorStatus_t GPIO_SetPinValue(GPIO_PORT_NAME local_u8PortID, GPIO_PIN_NUM local_u8PinID,u8 local_u8Value)
{
	E_ErrorStatus_t  GPIO_SetPinValueError = E_NOK;
((GPIOReg_t*)(local_u8PortID))->MODER &= ~(GPIO_CLEAR_MASK << (local_u8PinID) * 2);
((GPIOReg_t*)(local_u8PortID))->MODER |= ( GPIO_Mod_OUTPUT<< (local_u8PinID) * 2);
((GPIOReg_t*)(local_u8PortID))->ODR &= ~(GPIO_CLEAR_MASK << (local_u8PinID) * 1);
((GPIOReg_t*)(local_u8PortID))->ODR |= ((local_u8Value << local_u8PinID) * 1);
GPIO_SetPinValueError = E_OK;
return GPIO_SetPinValueError;
}


E_ErrorStatus_t GPIO_TogPinValue(GPIO_PORT_NAME local_u8PortID, GPIO_PIN_NUM local_u8PinID)
{
E_ErrorStatus_t  GPIO_SetPinValueError = E_NOK;
((GPIOReg_t*)(local_u8PortID))->MODER &= ~(GPIO_CLEAR_MASK << (local_u8PinID) * 2);
((GPIOReg_t*)(local_u8PortID))->MODER |= ( GPIO_Mod_OUTPUT<< (local_u8PinID) * 2);
((GPIOReg_t*)(local_u8PortID))->ODR ^= (1<< local_u8PinID);
GPIO_SetPinValueError = E_OK;
return GPIO_SetPinValueError;
}

E_ErrorStatus_t GPIO_SetPortValue(GPIO_PORT_NAME local_u8PortID , u16  local_u16PortValue)
{
	E_ErrorStatus_t  GPIO_SetPortValueError = E_NOK;
((GPIOReg_t*)(local_u8PortID))->MODER &=~(GPIO_MODER_MASK);
((GPIOReg_t*)(local_u8PortID))->MODER |= (GPIO_SET_ALL_BITS_MASK);
((GPIOReg_t*)(local_u8PortID))->ODR = ((local_u16PortValue) ? 0xFFFF : 0);
GPIO_SetPortValueError = E_OK;
return GPIO_SetPortValueError;
}


u8 GPIO_GetPinValue(GPIO_PORT_NAME local_u8PortID, GPIO_PIN_NUM local_u8PinID )
{

E_ErrorStatus_t  GPIO_GetPinValueError = E_NOK;
u8 local_u8GetValue =0;
((GPIOReg_t*)(local_u8PortID))->MODER &= ~(GPIO_CLEAR_MASK << (local_u8PinID) * 2);
((GPIOReg_t*)(local_u8PortID))->MODER |= ( GPIO_Mod_INPUT<< (local_u8PinID) * 2);
local_u8GetValue = (((GPIOReg_t*)(local_u8PortID))->IDR >> (local_u8PinID))& BIT_0_MASK;
GPIO_GetPinValueError = E_OK;
return local_u8GetValue ;
}