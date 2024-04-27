
#ifndef RCC_H_
#define RCC_H_

#include"LIB/Error_Status.h"
#include"LIB/Std_Types.h"
#include"LIB/Bit_Mask.h"


typedef enum {
	SysClock_HSI =  0x00000000,
	SysClock_HSE  = 0x00000001,
	SysClock_PLL  =0x00000002,
	SysClock_PLL2 = 0x04000000,
	SysClock_LES =  0x00000001
}SysClock;

typedef enum {
	PERIPHRAL_GPIO_A ,
	PERIPHRAL_GPIO_B ,
	PERIPHRAL_GPIO_C ,
	PERIPHRAL_GPIO_D ,
	PERIPHRAL_GPIO_E ,
	PERIPHRAL_GPIO_H ,
	PERIPHRAL_CRC    ,
	PERIPHRAL_DMA_1  ,
	PERIPHRAL_DMA_2  ,
	PERIPHRAL_OTG_FS ,
	PERIPHRAL_TIMER_2,
	PERIPHRAL_TIMER_3,
	PERIPHRAL_TIMER_4,
	PERIPHRAL_TIMER_5,
	PERIPHRAL_WWDG  ,
	PERIPHRAL_SPI_2 ,
	PERIPHRAL_SPI_3 ,
	PERIPHRAL_USART_2,
	PERIPHRAL_I2C_1  ,
	PERIPHRAL_I2C_2  ,
	PERIPHRAL_I2C_3  ,
	PERIPHRAL_PWR_INTFC,
	PERIPHRAL_TIMER_1  ,
	PERIPHRAL_USART_1  ,
	PERIPHRAL_USART_6  ,
	PERIPHRAL_ADC_1 ,
	PERIPHRAL_SDIO  ,
	PERIPHRAL_SPI_1 ,
	PERIPHRAL_SPI_4 ,
	PERIPHRAL_SYSCFG,
	PERIPHRAL_TIMER_9 ,
	PERIPHRAL_TIMER_10,
	PERIPHRAL_TIMER_11
} PERIPHRAL;




/*  Function Name  : RCC_SelectClock.                                                    */
/* Return Type     : ERROR_STATES enum.                                                 */
/* Arguments       : Pointer to ClockConfig_str for RCC Configuration and seslcting.   */
/* Functionality   : Selecting Sys Clock,without any prescaling, with default calibration
                    without enabling any peripheral and disabling clock security. */


E_ErrorStatus_t RCC_SelectSysClock ( u8  SysClock);

/*  Function Name  : RCC_EnablePeripheral                                                */
/* Return Type     : ERROR_STATES enum.                                                 */
/* Arguments       : peripheral and its bus type.                                      */
/* Functionality   : Selecting any peripheral and enable its clock                    */

E_ErrorStatus_t  RCC_EnablePeripheral(PERIPHRAL PeriphralId);

/*  Function Name  : RCC_DisablePeripheral                                               */
/* Return Type     : ERROR_STATES enum.                                                 */
/* Arguments       : peripheral and its bus type.                                      */
/* Functionality   : Selecting any peripheral and disable its clock                   */
E_ErrorStatus_t  RCC_DisablePeripheral(PERIPHRAL PeriphralId);




/*
* @constraints
*          1) PLL must be OFF before configuring!
*          2) PLL must not be selected as the system clock before configuring!
*
RCC_PLLM values-> 2 to 63
RCC_PLLN values -> 192 to 432
RCC_PLLP values -> 2, 4, 6, 8
RCC_PLLQ values -> 2 ≤ PLLQ ≤15
(PLL_CLK_HSI, PLL_CLK_HSE)

* @note:  - The USB OTG FS requires a 48 MHz clock to work correctly.
*         - The SDIO and the random number generator need a frequency lower than or equal to 48 MHz to work
*		   	 correctly.
*		   - Ensure that the VCO output frequency (FreqInput/M*N) is between 192 and 432MHz.
*/
E_ErrorStatus_t RCC_SetPLLConfiguration(u8 RCC_PLLM, u16 RCC_PLLN, u8 RCC_PLLP, u8 RCC_PLLQ);


#endif /* RCC_H_ */