/********************************************************************************************************/
/************************************************Includes************************************************/
/*******************************************************************************************************/

#include"MCAL/GPIO/GPIO.h"
#include"UART.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

Uart_TXRequest_t transmitbuffer[5];
Uart_RXRequest_t recievebuffer[5];


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

static void configure_USART_registers(USART_t *USART, const USART_Config *config);
 uint8_t *Copy_u8Data_global = 0;

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

E_ErrorStatus_t USART_Init(const USART_Config *Copy_addCFG)
{ 
    E_ErrorStatus_t UART_ErrorStatus_t = E_NOK;

    if (Copy_addCFG == NULL) {return UART_ErrorStatus_t;}

 
    /*clac Baud Rate */
 float USARTDIV = (float)SYS_FREQUENCY / (Copy_addCFG->BaudRate * (16 * (2 - 1)));

 uint16_t mantissa = (uint16_t)USARTDIV;

USARTDIV -=mantissa;
USARTDIV *= (16 * (2 - Copy_addCFG->OVER8));
uint8_t fraction=0;
//Check if the fractional part needs rounding
if ((USARTDIV - (uint16_t)USARTDIV) >= 0.5) {
    fraction = (uint16_t)USARTDIV + 1;
} else {
    fraction = (uint16_t)USARTDIV;
}


    switch (Copy_addCFG->Channel) {
        case USART_Channel_1:
            // Write configuration to USART 1
            configure_USART_registers(USART_1, Copy_addCFG);
             USART_1->USART_BRR.DIV_MANTISSA = mantissa;
            USART_1->USART_BRR.DIV_FRACTION = fraction;

            break;
        case USART_Channel_2:
            // Write configuration to USART 2
            configure_USART_registers(USART_2, Copy_addCFG);
            USART_2->USART_BRR.DIV_FRACTION=fraction;
            USART_2->USART_BRR.DIV_MANTISSA=mantissa;
            break;
        case USART_Channel_6:
            // Write configuration to USART 6
            configure_USART_registers(USART_6,Copy_addCFG);
            USART_6->USART_BRR.DIV_FRACTION=fraction;
            USART_6->USART_BRR.DIV_MANTISSA=mantissa;
            break;
        default:
            return UART_ErrorStatus_t; // Invalid channel
    }

    return UART_ErrorStatus_t;
}






// Define the configure_USART_registers function
static void configure_USART_registers(USART_t *USART, const USART_Config *config ) {
   
    USART->USART_CR1.RE = config->RE;
    USART->USART_CR1.TE = config->TE;
  // USART->USART_CR1.TXEIE = config->TXEIE;
  // USART->USART_CR1.TCIE = config->TCIE;
    USART->USART_CR1.OVER8 = config->OVER8;
    USART->USART_CR1.UE = config->UE;
    USART->USART_CR1.M = config->M;
    USART->USART_CR1.PCE = config->PCE;
}







E_ErrorStatus_t USART_SendByteAsynchronous(USART_Channel Copy_enuChannel, uint8_t Copy_u8Data)
{


 E_ErrorStatus_t UART_ErrorStatus_t = E_NOK;

switch (Copy_enuChannel)
{
        case USART_Channel_1:
        USART_1 ->USART_DR.DATA = Copy_u8Data;

        break;
        case USART_Channel_2:
        USART_2 ->USART_DR.DATA = Copy_u8Data;

        break;
        case USART_Channel_6:
        USART_6 ->USART_DR.DATA = Copy_u8Data;
        break;
        default:
            return UART_ErrorStatus_t; // Invalid channel
}
return UART_ErrorStatus_t;
}



E_ErrorStatus_t USART_SendByteSynchronous(USART_Channel Copy_enuChannel, uint8_t Copy_u8Data)
  
{      E_ErrorStatus_t UART_ErrorStatus_t = E_NOK;
        uint16_t TimeOut = 6000;
    switch (Copy_enuChannel)
    { 
      case USART_Channel_1:
        USART_1 ->USART_DR.DATA = Copy_u8Data;
        USART_1->USART_CR1.TXEIE  = 1;
        USART_1 ->USART_CR1.TCIE = 1; 
        while (TimeOut)
        {
            TimeOut--;
        }
        USART_1->USART_CR1.TXEIE  = 0;
         USART_1->USART_CR1.TCIE = 0;
        break;

        case USART_Channel_2:
        USART_2 ->USART_DR.DATA = Copy_u8Data;
        USART_2->USART_CR1.TXEIE  = 1;
        USART_2 ->USART_CR1.TCIE = 1; 
       while (TimeOut)
        {
           TimeOut--;
        }
        USART_2->USART_CR1.TXEIE  = 0;
        USART_2 ->USART_CR1.TCIE = 0;
        break;

        case USART_Channel_6:
        USART_6 ->USART_DR.DATA = Copy_u8Data;
        break;
        default: return UART_ErrorStatus_t;
           
     }
return UART_ErrorStatus_t;
}







E_ErrorStatus_t USART_GetByteASynchronous(USART_Channel Copy_enuChannel,  uint8_t* Copy_u8Data)
{  E_ErrorStatus_t UART_ErrorStatus_t = E_NOK;
       
    
    switch (Copy_enuChannel)
    { 
      case USART_Channel_1:
       USART_1->USART_CR1.RXNEIE = 0; 
        USART_1->USART_CR1.RE=1;
       *(Copy_u8Data)= USART_1->USART_DR.DATA;
        USART_1->USART_CR1.RE=1; 
       USART_1->USART_CR1.RXNEIE  = 1; 
        break;

        case USART_Channel_2:
       USART_2->USART_CR1.RXNEIE = 0; 
        USART_2->USART_CR1.RE=1;
       (Copy_u8Data_global) = (Copy_u8Data);
      USART_2->USART_CR1.RE=1; 
        USART_2->USART_CR1.RXNEIE  = 1; 
        break;

        case USART_Channel_6:

        break;
        default: return UART_ErrorStatus_t;
           
     }
return UART_ErrorStatus_t;
}















E_ErrorStatus_t USART_SendBufferZeroCopy(Uart_TXRequest_t * Copy_addRequest)
{
     E_ErrorStatus_t UART_ErrorStatus_t = E_NOK;


    switch ( Copy_addRequest ->Channel)
{
        case USART_Channel_1:
        
        if ( Copy_addRequest->state == READY)
         {
         transmitbuffer[0].state = BUSY;

           //if (Copy_addRequest->TX_Buffer.data < 51)
               transmitbuffer[0].TX_Buffer.data=Copy_addRequest->TX_Buffer.data;
               transmitbuffer[0].TX_Buffer.size=Copy_addRequest->TX_Buffer.size;
               transmitbuffer[0].TX_Buffer.position=0;
               transmitbuffer[0].TX_callBack =Copy_addRequest->TX_callBack;

               USART_1 ->USART_DR.DATA =  transmitbuffer[0].TX_Buffer.data[0] ;
               transmitbuffer[0].TX_Buffer.position++;
               USART_1 ->USART_CR1.TXEIE =1;
               USART_1 ->USART_CR1.TCIE = 1;     
                   
         }
		break;

        break;
        case USART_Channel_2:
             if ( Copy_addRequest->state == READY)
        {
         transmitbuffer[0].state = BUSY;

               transmitbuffer[0].TX_Buffer.data=Copy_addRequest->TX_Buffer.data;
               transmitbuffer[0].TX_Buffer.size=Copy_addRequest->TX_Buffer.size;
               transmitbuffer[0].TX_Buffer.position=0;
               transmitbuffer[0].TX_callBack =Copy_addRequest->TX_callBack;

            /*to provoke an interrupt */
            USART_2 ->USART_DR.DATA =  transmitbuffer[0].TX_Buffer.data[0] ;
            transmitbuffer[0].TX_Buffer.position++;
            USART_2 ->USART_CR1.TXEIE = 1;
            USART_2->USART_CR1.TCIE =1;  
                   
         }
		break;
        case USART_Channel_6:
                     if ( Copy_addRequest->state == READY)
        {
         transmitbuffer[0].state = BUSY;

           //if (Copy_addRequest->TX_Buffer.data < 51)
               transmitbuffer[0].TX_Buffer.data=Copy_addRequest->TX_Buffer.data;
               transmitbuffer[0].TX_Buffer.size=Copy_addRequest->TX_Buffer.size;
               transmitbuffer[0].TX_Buffer.position=0;
               transmitbuffer[0].TX_callBack =Copy_addRequest->TX_callBack;

            /*to provoke an interrupt */
            USART_6 ->USART_DR.DATA=  transmitbuffer[0].TX_Buffer.data[0];
            transmitbuffer[0].TX_Buffer.position++;
               USART_6 ->USART_CR1.TXEIE =1;
               USART_6 ->USART_CR1.TCIE = 1;  
                   
         }
		break;
        default:
            return UART_ErrorStatus_t; // Invalid channel
}

return UART_ErrorStatus_t;

     
}


E_ErrorStatus_t  USART_ReceiveBuffer( Uart_RXRequest_t * Copy_addRequest)
{
	E_ErrorStatus_t UART_ErrorStatus_t = E_NOK;
	
	if(Copy_addRequest->RX_Buffer.data == NULL){return UART_ErrorStatus_t;}
	
	switch ( Copy_addRequest ->Channel)
	{
		 case USART_Channel_1:
            if (recievebuffer[0].state == READY) {
                recievebuffer[0].state = BUSY;
                USART_1->USART_CR1.RXNEIE = 0;
                USART_1->USART_CR1.RE = 1;
                recievebuffer[0].RX_Buffer.data = Copy_addRequest->RX_Buffer.data;
                recievebuffer[0].RX_Buffer.size = Copy_addRequest->RX_Buffer.size;
                recievebuffer[0].RX_Buffer.position = 0;
                recievebuffer[0].RX_callBack = Copy_addRequest->RX_callBack;

                // Wait for data to be received
                while (!(USART_1->USART_SR.RXNE)) {
                    // Optionally, you can implement a timeout mechanism here
                }

                recievebuffer[0].RX_Buffer.data[0] = USART_1->USART_DR.DATA;
                recievebuffer[0].RX_Buffer.position++;

                // Re-enable USART receiver and receive interrupt
                USART_1->USART_CR1.RE = 1;
                USART_1->USART_CR1.RXNEIE = 1;
            }
            break;

		case USART_Channel_2:
		
		if (recievebuffer[Copy_addRequest->Channel].state == READY) {
    recievebuffer[Copy_addRequest->Channel].state = BUSY;
    USART_2->USART_CR1.RXNEIE = 0;
    USART_2->USART_CR1.RE = 1;
    recievebuffer[Copy_addRequest->Channel].RX_Buffer.data = Copy_addRequest->RX_Buffer.data;
    recievebuffer[Copy_addRequest->Channel].RX_Buffer.size = Copy_addRequest->RX_Buffer.size;
    //recievebuffer[Copy_addRequest->Channel].RX_Buffer.size = 5;
    recievebuffer[Copy_addRequest->Channel].RX_Buffer.position = 0;
    recievebuffer[Copy_addRequest->Channel].RX_callBack = Copy_addRequest->RX_callBack;

    // Wait for data to be received
    while (!(USART_2->USART_SR.RXNE)) {
        // Optionally, you can implement a timeout mechanism here
    }
   
recievebuffer[Copy_addRequest->Channel].RX_Buffer.data[0] = USART_2->USART_DR.DATA;
//recievebuffer[Copy_addRequest->Channel].RX_Buffer.position++;

    // Re-enable USART receiver and receive interrupt
   USART_2->USART_CR1.RE = 1;
    USART_2->USART_CR1.RXNEIE = 1;
}
		break;
		case USART_Channel_6:
	 if (recievebuffer[0].state == READY) {
                recievebuffer[0].state = BUSY;
                USART_6->USART_CR1.RXNEIE = 0;
                USART_6->USART_CR1.RE = 1;
                recievebuffer[0].RX_Buffer.data = Copy_addRequest->RX_Buffer.data;
                recievebuffer[0].RX_Buffer.size = Copy_addRequest->RX_Buffer.size;
                recievebuffer[0].RX_Buffer.position = 0;
                recievebuffer[0].RX_callBack = Copy_addRequest->RX_callBack;

                // Wait for data to be received
                while (!(USART_6->USART_SR.RXNE)) {
                    // Optionally, you can implement a timeout mechanism here
                }

                recievebuffer[0].RX_Buffer.data[0] = USART_6->USART_DR.DATA;
                recievebuffer[0].RX_Buffer.position++;

                // Re-enable USART receiver and receive interrupt
                USART_6->USART_CR1.RE = 1;
                USART_6->USART_CR1.RXNEIE = 1;
            }
		break;
		default:
		return UART_ErrorStatus_t; // Invalid channel
	}

	return UART_ErrorStatus_t;

	
}



/* IRQ handlers */

void USART1_IRQHandler(void)
{

    /*TXE*/
    //If the content of the TDR register has been transferred into the shift register
   if (USART_1->USART_SR.TXE)
   {
    if(transmitbuffer[0].TX_Buffer.position < transmitbuffer[0].TX_Buffer.size)
       USART_1 ->USART_DR.DATA = transmitbuffer[0].TX_Buffer.data[transmitbuffer[0].TX_Buffer.position];
       transmitbuffer[0].TX_Buffer.position++;
      

   }
   else 
   {  
    transmitbuffer[0].state = READY;
    if (transmitbuffer[0].TX_callBack)
    {
        transmitbuffer[0].TX_callBack();
    }
   }

   /*RXNE*/
   //If content of the RDR shift register has been transferred to the USART_DR register
    if (USART_1->USART_SR.RXNE)
   {
    if(recievebuffer[0].RX_Buffer.position < recievebuffer[0].RX_Buffer.size)
       recievebuffer[0].RX_Buffer.data[recievebuffer[0].RX_Buffer.position] =  USART_2->USART_DR.DATA ;
       recievebuffer[0].RX_Buffer.position++;

   }
   else 
   {  
    recievebuffer[0].state = READY;
    if (recievebuffer[0].RX_callBack)
    {
        recievebuffer[0].RX_callBack();
    }
   }
}

void USART2_IRQHandler(void)
{

    
        /*TXE*/
    //If the content of the TDR register has been transferred into the shift register
   if (USART_2->USART_SR.TXE)
   {
    if(transmitbuffer[0].TX_Buffer.position < transmitbuffer[0].TX_Buffer.size)
       USART_2 ->USART_DR.DATA = transmitbuffer[0].TX_Buffer.data[transmitbuffer[0].TX_Buffer.position];
       transmitbuffer[0].TX_Buffer.position++;

   }
   else 
   {  
    transmitbuffer[0].state = READY;
    if (transmitbuffer[0].TX_callBack)
    {
        transmitbuffer[0].TX_callBack();
    }
   }

   /*RXNE*/
   //If content of the RDR shift register has been transferred to the USART_DR register
   if (USART_2->USART_SR.RXNE) {
        // Check if the receive buffer is in the BUSY state and there is data to be received
             *(Copy_u8Data_global)= USART_2->USART_DR.DATA;
        
            // Check if there is space in the transmit buffer to store the received data
           if (recievebuffer[0].RX_Buffer.position < recievebuffer[0].RX_Buffer.size) 
            {
                // Store received data in the transmit buffer
            
                recievebuffer[0].RX_Buffer.data[recievebuffer[0].RX_Buffer.position] = USART_2->USART_DR.DATA;
               
                recievebuffer[0].RX_Buffer.position++;
            } 
           else {
                // Set the state to READY and invoke the callback function if buffer is full
                recievebuffer[0].state = READY;
                if (recievebuffer[0].RX_callBack) {
                    recievebuffer[0].RX_callBack();
                }
                // Clear the receive interrupt flag
              
               USART_2->USART_CR1.RXNEIE=0;
          }
        
    }

}

void USART6_IRQHandler(void)
{

}