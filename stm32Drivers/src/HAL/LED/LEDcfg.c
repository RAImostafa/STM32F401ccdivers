
#include"LED.h"
#include"LEDcfg.h"
#include"MCAL\GPIO\GPIO.h"


/********************************************************************************************************/
/************************************************CFGs****************************************************/
/********************************************************************************************************/

LED_strState_t LED_Configs[_NUM_OF_LEDS]=
 {
	[LED_ONE]=
	{
        .port = PORT_NAME_A,
        .pin = PIN_NUM_7,
        .LED_strActive =LED_LOW_Active,
        .LED_strStatus= LED_strOutput_ON,
	},
    
	[LED_TWO]=
	{
        .port =  PORT_NAME_A,
        .pin= PIN_NUM_5,
        .LED_strActive =  LED_LOW_Active,
         .LED_strStatus= LED_strOutput_ON,
	},    

/*	[LED_THREE]=
	{
        .port= PORT_NAME_C,
        .pin = PIN_NUM_14,
        .LED_strActive =  LED_High_Active,
        .LED_strStatus = LED_strOutput_ON,
	},*/
 };