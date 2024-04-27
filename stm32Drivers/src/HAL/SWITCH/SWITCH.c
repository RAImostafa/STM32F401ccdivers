/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include"SWIcfg.h"
#include"SWITCH.h"
#include"MCAL\GPIO\GPIO.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

extern SWI_strState_t Switch_Configs[ _NUM_OF_SWITCHES];



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


E_ErrorStatus_t SWI_init(void)
{
    E_ErrorStatus_t SWI_ERROR = E_NOK;
    GPIO_PIN_config_t SWI_PIN_config;
       /*Configure all LEDs speed as GPIO_NORMAL_SPEED */  
    SWI_PIN_config.GPIOSpeed=GPIO_OUTPUT_SPEED_NORMAL_SPEED;

    /*Configure all LEDs mode as General purpose output mode */  
    SWI_PIN_config.GPIOMode=GPIO_Mod_INPUT;

  
   for(u8 i =0 ; i<_NUM_OF_SWITCHES ;i++)
   {
      SWI_PIN_config.GPIOPin = Switch_Configs[i].pin;
      SWI_PIN_config.GPIOPort =Switch_Configs[i].port;
    switch (Switch_Configs[i].SWI_InternalStatus)
     {
    
     case SWI_PULL_DOWN: 
        SWI_PIN_config.GPIO_INPUTTYPE= PULL_DOWN;
          SWI_ERROR= E_OK; 
        break;
      case SWI_PULL_UP: 
         SWI_PIN_config.GPIO_INPUTTYPE= PULL_UP; 
          SWI_ERROR= E_OK;
        break;
     default:  SWI_ERROR = E_NOK;
        break;
     }
        GPIO_SetPinConfig(&SWI_PIN_config);
     
   }

  return SWI_ERROR;
    

}


u8 SWI_getSwiState(u8 SWI_NUM )
{
E_ErrorStatus_t SWI_ERROR = E_NOK;
u8 SWI_PIN_STATE =0;
u8 SwiState =0;
SWI_PIN_STATE = GPIO_GetPinValue(Switch_Configs[SWI_NUM].port ,Switch_Configs[SWI_NUM].pin);
SwiState =(SWITCH_StateType_t)(SWI_PIN_STATE)^(SWITCH_StateType_t)(Switch_Configs[SWI_NUM].SWI_ActiveType);
SWI_ERROR = E_OK;
return SwiState ;

}
