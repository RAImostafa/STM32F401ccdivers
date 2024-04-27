#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include"LIB/Error_Status.h"
#include"LIB/STD_TYPES.h"



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define READY                                      0
#define BUSY                                       1
#define     BAUD_RATE                              9600
#define     SYS_FREQUENCY                          16000000
//#define     SYS_FREQUENCY                        25000000UL

#define USART_1_BaseAddress                    ((volatile USART_t*)0x40011000)
#define USART_2_BaseAddress                    ((volatile USART_t*)0x40004400)
#define USART_6_BaseAddress                    ((volatile USART_t*)0x40011400)




typedef void (*CBF)(void);
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef void (*CBF)(void);

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef struct 
{
   struct{
			uint32_t PE:  1;   //Parity error
			uint32_t FE:  1;   //Framing error
			uint32_t NF:  1;  //Noise detected flag
			uint32_t ORE: 1;  //Overrun error
			uint32_t IDLE:1;  //IDLE line detected
			uint32_t RXNE:1;  //Read data register not empty
			uint32_t TC:  1;  //Transmission complete
			uint32_t TXE: 1;  //Transmit data register empty
			uint32_t LBD: 1;  //LIN break detection flag
			uint32_t CTS: 1;  //CTS flag
			uint32_t :22;
		}USART_SR;

   struct{
			uint32_t DATA:9;
			uint32_t :23;
		}USART_DR;

   struct{
			uint32_t DIV_FRACTION:4;
			uint32_t DIV_MANTISSA:12;
			uint32_t :16;
		}USART_BRR;

  struct{
			uint32_t SBK	   :1;  //Send break
			uint32_t RWU    :1;  //Receiver wakeup
			uint32_t RE     :1;  //Receiver enable
			uint32_t TE     :1;  //Transmitter enable
			uint32_t IDLEIE :1;  //IDLE interrupt enable
			uint32_t RXNEIE :1;  //RXNE interrupt enable "Read data register not empty"
			uint32_t TCIE   :1;  //Transmission complete interrupt enable
			uint32_t TXEIE  :1;  //TXE interrupt enable "Transmit data register empty"
			uint32_t PEIE   :1;  //PE interrupt enable
			uint32_t PS     :1;  //Parity selection
			uint32_t PCE    :1;  //Parity control enable
			uint32_t WAKE   :1;  //Wakeup method
			uint32_t M      :1;  //Word length
			uint32_t UE     :1;  //USART enable
			uint32_t        :1;
			uint32_t OVER8  :1;  //Oversampling mode
			uint32_t        :16;
		}USART_CR1;

  struct{
			uint32_t ADD   :4; //Address of the USART node
			uint32_t       :1;
			uint32_t LBDL  :1; //lin break detection length
			uint32_t LBDIE :1; //LIN break detection interrupt enable
			uint32_t       :1;
			uint32_t LBCL  :1; //Last bit clock pulse
			uint32_t CPHA  :1; //Clock phase
			uint32_t CPOL  :1; //Clock polarity
			uint32_t CLKEN :1; //Clock enable 
			uint32_t STOP  :2; //STOP bits
			uint32_t LINEN :1; //LIN mode enable
			uint32_t       :17;
		}USART_CR2;

   struct{
			uint32_t EIE   :1; //Error interrupt enable
			uint32_t IREN  :1; //IrDA mode enable
			uint32_t IRLP  :1; //IrDA low-power
			uint32_t HDSEL :1; //Half-duplex selection
			uint32_t NACK  :1; //Smartcard NACK enable
			uint32_t SCEN  :1; //Smartcard mode enable
			uint32_t DMAR  :1; //DMA enable receiver
			uint32_t DMAT  :1; //DMA enable transmitter
			uint32_t RTSE  :1; //Request To Send enable
			uint32_t CTSE  :1; //clear to send enable
			uint32_t CTSIE :1; //CTS interrupt enable
			uint32_t ONEBIT:1; //One sample bit method enable
			uint32_t       :20;
		}USART_CR3;
    
} USART_t;

#define USART_1    ((volatile USART_t*) USART_1_BaseAddress)
#define USART_2    ((volatile USART_t*) USART_2_BaseAddress)
#define USART_6    ((volatile USART_t*) USART_6_BaseAddress)

typedef enum {
    USART_Channel_1,
    USART_Channel_2,
    USART_Channel_6
} USART_Channel;

typedef struct
{
   USART_Channel Channel;
    uint32_t OVER8;
    uint32_t UE;               // USART enable
    uint32_t M;                // Word length
    uint32_t PCE;
    uint32_t TCIE;             // Transmission complete interrupt enable
    uint32_t TXEIE;
    uint32_t RE;               // Receiver enable
    uint32_t TE;               // Transceiver enable
    uint32_t BaudRate;
} USART_Config;

typedef struct 
{
	uint16_t *data;
	uint32_t volatile size;
	uint16_t volatile position;
} Buffer_t;

typedef struct 
{
	Buffer_t TX_Buffer;
	USART_Channel Channel;
	uint32_t state;
	CBF TX_callBack;
} Uart_TXRequest_t;

typedef struct 
{
  	Buffer_t RX_Buffer;
	USART_Channel Channel;
	uint32_t state;
	CBF RX_callBack;
} Uart_RXRequest_t;

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

E_ErrorStatus_t USART_Init(const USART_Config * Copy_addCFG);

E_ErrorStatus_t USART_SendByteSynchronous(USART_Channel Copy_enuChannel, uint8_t Copy_u8Data);


E_ErrorStatus_t USART_SendByteAsynchronous(USART_Channel Copy_enuChannel, uint8_t Copy_u8Data);
E_ErrorStatus_t USART_GetByteASynchronous(USART_Channel Copy_enuChannel, uint8_t *  Copy_u8Data);

/*Asynch function*/
E_ErrorStatus_t USART_ReceiveBuffer(Uart_RXRequest_t * Copy_addRequest);

/*Asynch function*/
E_ErrorStatus_t USART_SendBufferZeroCopy(Uart_TXRequest_t * Copy_addRequest);

//E_ErrorStatus_t USART_RegisterCallBackFunction(USART_Channel Channel, USART_Mode Mode, CallBack CallBackFunction);

#endif // MCAL_UART_UART_H_
