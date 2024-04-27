   
#include "LED.h"
#include"LEDcfg.h"
#include "MCAL\GPIO\GPIO.h"



extern LED_strState_t LED_Configs[_NUM_OF_LEDS];


E_ErrorStatus_t LED_init(void)
{

E_ErrorStatus_t LED_ErrorStatus = E_NOK;

    GPIO_PIN_config_t Led_GPIO_Handler; 

    /*Configure all LEDs speed as GPIO_NORMAL_SPEED */  
    Led_GPIO_Handler.GPIOSpeed=GPIO_OUTPUT_SPEED_NORMAL_SPEED;

    /*Configure all LEDs mode as General purpose output mode */  
     Led_GPIO_Handler.GPIOMode=GPIO_Mod_OUTPUT;

    /*Configure all LEDs Moode as Push PUll */ 
    Led_GPIO_Handler.GPIO_OUTPUTTYPE = PUSHPULL;

  
   for(u8 i =0 ; i< _NUM_OF_LEDS ;i++)
   {
     Led_GPIO_Handler.GPIOPin = LED_Configs[i].pin;
     Led_GPIO_Handler.GPIOPort = LED_Configs[i].port;
    switch (LED_Configs[i].LED_strActive)
     {
     case LED_LOW_Active: 
        Led_GPIO_Handler.GPIOValue= GPIO_LOW;
         LED_ErrorStatus = E_OK; 
        break;
      case LED_High_Active: 
        Led_GPIO_Handler.GPIOValue= GPIO_HIGH; 
         LED_ErrorStatus = E_OK;
        break;
     default: LED_ErrorStatus = E_NOK;
        break;
     }
        GPIO_SetPinConfig(&Led_GPIO_Handler);
     
   }

  return LED_ErrorStatus;

}


E_ErrorStatus_t LED_setLedState(u8 Led_NUM, LED_State_t LedState)
{

E_ErrorStatus_t LED_ErrorStatus = E_NOK;
GPIO_SetPinValue(LED_Configs[Led_NUM].port , LED_Configs[Led_NUM].pin ,LedState);
 LED_ErrorStatus = E_OK;
return E_OK;

}

E_ErrorStatus_t LED_TogLedState(u8 Led_NUM)
{

E_ErrorStatus_t LED_ErrorStatus = E_NOK;
GPIO_TogPinValue(LED_Configs[Led_NUM].port , LED_Configs[Led_NUM].pin);
 LED_ErrorStatus = E_OK;
return E_OK;
}


E_ErrorStatus_t LED_getLedState(u8 Led_NUM, LED_Activity_t *LED_Activity)
{
    E_ErrorStatus_t LED_ErrorStatus = E_NOK;
    *LED_Activity = LED_Configs[Led_NUM].LED_strActive;
    LED_ErrorStatus = E_OK;
    return LED_ErrorStatus;
}
