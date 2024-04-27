/*
 * GPIO.h
 *
 * Created: 19/02/2024 14:20:59
 *  Author: Rania
 */



#ifndef GPIO_H_
#define GPIO_H_


#include"LIB\Error_Status.h"
#include"LIB\Std_Types.h"
#include"LIB\Bit_Mask.h"


#define NUMBER_OF_USED_PINS  6

typedef enum{
 GPIO_Mod_INPUT   =  0b00, /*input no pull up*/
 GPIO_Mod_OUTPUT  =  0b01,
 GPIO_Mod_AF      =  0b10,
 GPIO_Mod_ANALOG  =  0b11
 
}GPIO_PIN_MOD;

typedef enum{
 GPIO_OUTPUT_SPEED_LOW_SPEED         =  0b00,
 GPIO_OUTPUT_SPEED_NORMAL_SPEED      =  0b01,
 GPIO_OUTPUT_SPEED_HIGH_SPEED        =  0b10,
 GPIO_OUTPUT_SPEED_VERY_HIGH_SPEED   =  0b11

}GPIO_OUTPUT_SPEED;



typedef enum {
    PORT_NAME_A = 0x40020000,
    PORT_NAME_B = 0x40020400,
    PORT_NAME_C = 0x40020800
} GPIO_PORT_NAME;


typedef enum {
	PIN_NUM_0 = 0 ,
	PIN_NUM_1 = 1 ,
	PIN_NUM_2 = 2 ,
	PIN_NUM_3 = 3 ,
	PIN_NUM_4 = 4 ,
	PIN_NUM_5 = 5 ,
	PIN_NUM_6 = 6 ,
	PIN_NUM_7 = 7 ,
	PIN_NUM_8 = 8 ,
	PIN_NUM_9 = 9 ,
	PIN_NUM_10 =10,
	PIN_NUM_11 =11,
	PIN_NUM_12 =12,
	PIN_NUM_13 =13,
	PIN_NUM_14 =14,
	PIN_NUM_15 =15
}GPIO_PIN_NUM;

typedef enum {
	PUSHPULL = 0,
	OPENDRAIN = 1

}GPIO_OUTPUT_MODS;

typedef enum {
	NO_PULL_UP_PULL_DOWN = 0 ,
	PULL_UP = 1 ,
	PULL_DOWN = 2 ,
}GPIO_INPUT_MOD;

typedef enum {
	GPIO_LOW = 0 ,
    GPIO_HIGH = 1 ,
}GPIO_OUTPUT_VALUE;

typedef enum{
	AF_SYSTEM= 0 ,
	AF_TIM1_2= 1 ,
	AF_TIM3_5= 2 ,
	AF_TIM9_11= 3 ,
	AF_I2C1_3= 4 ,
	AF_SPI1_4= 5 ,
	AF_SPI3= 6 ,
	AF_USART1_2= 7,
	AF_USAART6= 8 ,
	AF_I2C2_3= 9 ,
	AF_OTG_FS =10,
	AF_NF1 =11,
	AF_SDIO =12,
	AF_NF2 =13,
	AF_NF3=14,
	AF_EVENTOUT =15,
}GPIO_AF_ID;


typedef struct
{
	GPIO_PORT_NAME  GPIOPort;               // GPIO port number
    GPIO_PIN_NUM  GPIOPin;                 // GPIO pin number
	GPIO_PIN_MOD GPIOMode;                // GPIO pin mode
	GPIO_OUTPUT_MODS  GPIO_OUTPUTTYPE;    // GPIO pin output type
	GPIO_INPUT_MOD  GPIO_INPUTTYPE;      // GPIO pin input type
	GPIO_OUTPUT_SPEED  GPIOSpeed;          // GPIO pin speed
	GPIO_OUTPUT_VALUE  GPIOValue;
	GPIO_AF_ID AF_ID;
}GPIO_PIN_config_t;




E_ErrorStatus_t GPIO_SetPinConfig(GPIO_PIN_config_t * local_newPinStr);

E_ErrorStatus_t GPIO_SetPinValue(GPIO_PORT_NAME local_u8PortID, GPIO_PIN_NUM local_u8PinID,u8 local_u8Value);

E_ErrorStatus_t GPIO_SetPortValue(GPIO_PORT_NAME local_u8PortID , u16  local_u16PortValue);

u8 GPIO_GetPinValue(GPIO_PORT_NAME local_u8PortID, GPIO_PIN_NUM local_u8PinID );

E_ErrorStatus_t GPIO_TogPinValue(GPIO_PORT_NAME local_u8PortID, GPIO_PIN_NUM local_u8PinID);








#endif /* GPIO_H_ */
