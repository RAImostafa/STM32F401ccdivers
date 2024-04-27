// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "MCAL\RCC\RCC.h"
#include "MCAL\GPIO\GPIO.h"
#include "HAL\LED\LED.h"
#include "HAL\LED\LEDcfg.h"
#include "HAL\SWITCH\SWITCH.h"
#include "HAL\SWITCH\SWIcfg.h"
#include "MCAL\NVIC\NVIC.h"
#include"MCAL\SysTick\SysTick.h"
#include"sched.h"
#include"MCAL/UART/UART.h"
#include"APP_/DEMO.h"




void Copy_Cbf(void)
{
 //GPIO_SetPinValue(PORT_NAME_A , PIN_NUM_8 , GPIO_HIGH);

}







int main(int argc, char* argv[])
{
  
/*UART TEST*/

RCC_EnablePeripheral(PERIPHRAL_GPIO_A);
RCC_EnablePeripheral(PERIPHRAL_USART_2);
NVIC_EnableInterrupt(NVIC_USART2_INTERRUPT);

/*TX pin*/

	GPIO_PIN_config_t TX_pin;
	TX_pin.GPIOPort=PORT_NAME_A;
	TX_pin.GPIOPin=PIN_NUM_2;
	TX_pin.GPIOSpeed =GPIO_OUTPUT_SPEED_HIGH_SPEED;
	TX_pin.GPIOMode=GPIO_Mod_AF;
    TX_pin.GPIO_OUTPUTTYPE=PUSHPULL;
    TX_pin.AF_ID=AF_USART1_2;
	GPIO_SetPinConfig(&TX_pin);
/*RX pin*/
	GPIO_PIN_config_t RX_pin;
	RX_pin.GPIOPort=PORT_NAME_A;
	RX_pin.GPIOPin=PIN_NUM_3;
    RX_pin.GPIO_OUTPUTTYPE=PUSHPULL;
	RX_pin.GPIOSpeed =GPIO_OUTPUT_SPEED_HIGH_SPEED;
	RX_pin.GPIOMode=GPIO_Mod_AF;
    RX_pin.AF_ID=AF_USART1_2;
	GPIO_SetPinConfig(&RX_pin);





USART_Config Transmit_frame;
Transmit_frame.Channel= USART_Channel_2;
Transmit_frame.OVER8=0; //oversample by 16
Transmit_frame.UE=1;
Transmit_frame.M=0;
Transmit_frame.PCE=0; //disable parity
Transmit_frame.TCIE=1;
Transmit_frame.TXEIE=0;
Transmit_frame.TE =1; 
Transmit_frame.RE=1;
Transmit_frame.BaudRate=BAUD_RATE;
USART_Init(&Transmit_frame);

  // Prepare a buffer with data to be sent
   u16 sendData[] = {'h', 'e', 'l', 'l', 'o','\r', '\n'};
   //  u16 sendData[5];
    u32 dataSize = sizeof(sendData) / sizeof(sendData[0]);




    // Initialize a UART transmission request
    Uart_TXRequest_t txRequest = {
        .TX_Buffer.data = sendData,
        .TX_Buffer.size = dataSize,
        .TX_Buffer.position = 0,
        .Channel = USART_Channel_2,
        .state = READY,
        .TX_callBack = Copy_Cbf
    };
   
    Uart_RXRequest_t rxRequest = {
        .RX_Buffer.data = sendData,
        .RX_Buffer.size = 5,
        .RX_Buffer.position = 0,
        .Channel = USART_Channel_2,
        .state = READY,
        .RX_callBack = Copy_Cbf
    };

    // Call USART receive function
    //USART_ReceiveBuffer(&rxRequest);



  u8 volatile Copy_u8Data_ = 0;
 //USART_SendByteSynchronous( USART_Channel_2, 8);
  

//USART_GetByteSynchronous(USART_Channel_2,Copy_u8Data);



USART_SendByteAsynchronous(USART_Channel_2, '8');



  while (1)
{ 
// USART_SendByteAsynchronous(USART_Channel_2, '8');


}




}









 //interruput app
 /* 
  u8 priority_Value;
  volatile u8 *NVIC_priority =&priority_Value;
   
  NVIC_EnableInterrupt(NVIC_EXT0_INTERRRUPT);
  NVIC_SetPending(NVIC_EXT0_INTERRRUPT);
   
  NVIC_SetPeriority(NVIC_DMA1_STREAM0 , 70);
  NVIC_GetPeriority(NVIC_DMA1_STREAM0 , NVIC_priority);
*/ 




//Switch app and Led app/	
/* if(SWI_getSwiState(SWITCH_ONE) == SWITCH_RELEASED)
        {
            LED_setLedState(LED_ONE, LED_strOutput_ON);
        }
        else
        {
            LED_setLedState(LED_TWO,LED_strOutput_ON);
        }
        for(int i=0;i<100000;i++)
        {
            x++;
       }
 }*/

    

/*systick test*/
/*RCC_EnablePeripheral(PERIPHRAL_GPIO_A);

Systick_vidInit();
Systick_vidStart();
Systick_RegisterCbf(Copy_Cbf);
Systick_SetTicTime_ms(5000);*/

//GPIO app/
	/*GPIO_PIN_config_t Led;
	Led.GPIOPort=PORT_NAME_A;
	Led.GPIOPin=PIN_NUM_6;
	Led.GPIOSpeed =GPIO_OUTPUT_SPEED_NORMAL_SPEED;
	Led.GPIO_INPUTTYPE=PULL_UP ;
	Led.GPIOMode=GPIO_Mod_OUTPUT;
	Led.GPIO_OUTPUTTYPE=PUSHPULL;
	Led.GPIOValue=GPIO_HIGH;
	GPIO_SetPinConfig(&Led);*/



 //Switch app and Led app/		
//LED_init();
//SWI_init();



 //systick test/
/*Systick_vidInit();
Systick_vidStart();
Systick_RegisterCbf(Copy_Cbf);
Systick_SetTicTime_ms(5000);*/
//Systick_vidStop();


/* SCHED TEST*/
/* Sched_Init();
 Sched_Start();*/


/* DELAY dumb function  */
/*void Delay(u32 delay) {
    volatile u32 i;
    for (i = 0; i < delay; i++) {
        // This loop will take some time
    }
}*/




/*UART TEST*/
/*
RCC_EnablePeripheral(PERIPHRAL_GPIO_A);
RCC_EnablePeripheral(PERIPHRAL_USART_2);
NVIC_EnableInterrupt(NVIC_USART2_INTERRUPT);

/*TX pin*/
/*
	GPIO_PIN_config_t TX_pin;
	TX_pin.GPIOPort=PORT_NAME_A;
	TX_pin.GPIOPin=PIN_NUM_2;
	TX_pin.GPIOSpeed =GPIO_OUTPUT_SPEED_HIGH_SPEED;
	TX_pin.GPIOMode=GPIO_Mod_AF;
    //TX_pin.GPIO_OUTPUTTYPE=PUSHPULL;
    TX_pin.AF_ID=AF_USART1_2;
	GPIO_SetPinConfig(&TX_pin);
/*RX pin*/
	/*GPIO_PIN_config_t RX_pin;
	RX_pin.GPIOPort=PORT_NAME_A;
	RX_pin.GPIOPin=PIN_NUM_3;
    //RX_pin.GPIO_OUTPUTTYPE=PUSHPULL;
	RX_pin.GPIOSpeed =GPIO_OUTPUT_SPEED_HIGH_SPEED;
	RX_pin.GPIOMode=GPIO_Mod_AF;
    RX_pin.AF_ID=AF_USART1_2;
	GPIO_SetPinConfig(&RX_pin);





USART_Config Transmit_frame;
Transmit_frame.Channel= USART_Channel_2;
Transmit_frame.OVER8=0; //oversample by 16
Transmit_frame.UE=1;
Transmit_frame.M=0;
Transmit_frame.PCE=0; //disable parity
Transmit_frame.TCIE=1;
Transmit_frame.TXEIE=0;
Transmit_frame.TE =1; 
Transmit_frame.RE=1;
Transmit_frame.BaudRate=BAUD_RATE;
USART_Init(&Transmit_frame);

  // Prepare a buffer with data to be sent
    u16 sendData[] = {'H', 'e', 'l', 'l', 'o', '\r', '\n'};
    u32 dataSize = sizeof(sendData) / sizeof(sendData[0]);




    // Initialize a UART transmission request
    Uart_TXRequest_t txRequest = {
        .TX_Buffer.data = sendData,
        .TX_Buffer.size = dataSize,
        .TX_Buffer.position = 0,
        .Channel = USART_Channel_2,
        .state = READY,
        .TX_callBack = Copy_Cbf
    };

 //USART_SendBufferZeroCopy(&txRequest);
  u8 Copy_u8Data = 0;
//USART_SendByteSynchronous( USART_Channel_2, 'b');
USART_GetByteSynchronous(USART_Channel_2,Copy_u8Data);
*/