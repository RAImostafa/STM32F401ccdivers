#include "RCC.h"





#define clock_HSI             0x00000001
#define clock_HSE             0x00010000
#define clock_PLL             0x01000000


#define RCC_PLL_M_PRESCALE_MASK  0x0000003F
#define RCC_PLL_N_PRESCALE_MASK	 0x00007FC0
#define RCC_PLL_P_PRESCALE_MASK  0x00030000
#define RCC_PLL_Q_PRESCALE_MASK  0x0F000000

#define RCC_SysCLK_MASK          0x00000003
#define RCC_SYSCLK_STATE_MASK    0x0000000C


E_ErrorStatus_t RCC_SetSysClock (u8 SysClock);


#define Peri_Base   0x40023800


typedef struct{
	u32 RCC_CR;
	u32 RCC_PLLCFGR;
	u32 RCC_CFGR;
	u32 RCC_CIR;
	u32 RCC_AHB1RSTR;
	u32 RCC_AHB2RSTR;
	 u32 reserved1[2];
	u32 RCC_APB1RSTR;
	u32 RCC_APB2RSTR;
	u32 reserved2[2];
	u32 RCC_AHB1ENR;
	u32 RCC_AHB2ENR;
	u32 reserved3[2];
	u32 RCC_APB1ENR;
	u32 RCC_APB2ENR;
	u32 reserved4[2];
	u32 RCC_AHB1LPENR;
	u32 RCC_AHB2LPENR;
	u32 reserved5[2];
	u32 RCC_APB1LPENR;
	u32 RCC_APB2LPENR;
	u32 reserved6[2];
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 reserved7[2];
	u32 RCC_SSCGR;
	u32 RCC_PLLI2SCFGR;
	u32 reserved8;
	u32 RCC_DCKCFGR;
}RCC_str;



static volatile RCC_str  *const RCC = (volatile RCC_str  *const ) Peri_Base;




/*#define SysClock_HSI          0x00000000
#define SysClock_HSE          0x00000001
#define SysClock_PLL          0x00000002*/

E_ErrorStatus_t RCC_SelectSysClock (u8 SysClock)
{
	E_ErrorStatus_t RCC_ErrorStatus = E_NOK;

	switch(SysClock)
	{

	case SysClock_HSE:
	    RCC->RCC_CR |= clock_HSE;	//Enabling the clk
	    while ((RCC->RCC_CR & (clock_HSE << 1)) == 0); //shifting to bit 17 making sure it is ready
	    RCC_SetSysClock(SysClock_HSE);     //switch System clock
	    RCC_ErrorStatus = E_OK;

	break;

	case SysClock_HSI:
		RCC->RCC_CR |= clock_HSE;    //Enabling the clk
		while ((RCC->RCC_CR & (clock_HSE << 1)) == 0);//shifting to bit 17 making sure it is ready
		RCC_SetSysClock(SysClock_HSI);      //switch System clock
		RCC_ErrorStatus = E_OK;
	break;

	case SysClock_PLL:
		RCC->RCC_CR |= clock_PLL;    //Enabling the clk
		while ((RCC->RCC_CR & (clock_PLL << 1)) == 0);//shifting to bit 17 making sure it is ready
		RCC_SetSysClock(SysClock_PLL);      //switch System clock
		RCC_ErrorStatus = E_OK;
	break;
	case SysClock_PLL2:
		RCC->RCC_CR |= SysClock_PLL2;    //Enabling the clk
		while ((RCC->RCC_CR & (SysClock_PLL2 << 1)) == 0);//shifting to bit 17 making sure it is ready
		RCC_ErrorStatus = E_OK;
	break;

	default: RCC_ErrorStatus = E_NOK;
    break;

	}
	return RCC_ErrorStatus;
}


E_ErrorStatus_t RCC_SetSysClock (u8 SysClock){
	E_ErrorStatus_t RCC_ErrorStatus = E_NOK;
	 u32 Loc_ReadReg;
	 Loc_ReadReg=RCC->RCC_CFGR;
	 Loc_ReadReg &= (~RCC_SysCLK_MASK);
//	if (RCC->RCC_CR & SysClock)
	//{
     if(SysClock == SysClock_HSI )
     {

		Loc_ReadReg |= clock_HSI;
		RCC->RCC_CFGR = Loc_ReadReg;
     }
     else if(SysClock == SysClock_HSE)
     {
    	 Loc_ReadReg |= clock_HSE;
    	 RCC->RCC_CFGR = Loc_ReadReg;
     }
     else if(SysClock == SysClock_PLL)
     {
    	 Loc_ReadReg |= clock_PLL;
    	 RCC->RCC_CFGR = Loc_ReadReg;
     }
	//}

	 RCC_ErrorStatus = E_OK;
	return  RCC_ErrorStatus;
}

E_ErrorStatus_t RCC_DisSelectSysClock (u8 SysClock)
{
	E_ErrorStatus_t RCC_ErrorStatus = E_OK;

    if((SysClock >clock_PLL) ||  (SysClock < clock_HSI))
    {
    	RCC_ErrorStatus = E_NOK;
	}

    else if ((RCC->RCC_CFGR & RCC_SYSCLK_STATE_MASK) == (clock_HSI | clock_HSE | clock_PLL))
    {
        // Read system clock switch status
        RCC_ErrorStatus = E_NOK;
    }


  else
  {
	switch(SysClock)
	{

	case SysClock_HSE:
	    RCC->RCC_CR  &= ~(SysClock_HSE);	//Disabling the clk
	    RCC_ErrorStatus = E_OK;

	break;

	case SysClock_HSI:
		RCC->RCC_CR &= ~(SysClock_HSI);    //Disabling the clk
		RCC_ErrorStatus = E_OK;
	break;

	case SysClock_PLL:
		RCC->RCC_CR &= ~(SysClock_PLL);      //Disabling the clk
		RCC_ErrorStatus = E_OK;
	break;
	case SysClock_PLL2:
		RCC->RCC_CR  &= ~(SysClock_PLL2);    //Disabling the clk
		RCC_ErrorStatus = E_OK;
	break;

	default: RCC_ErrorStatus = E_NOK;
    break;

	}
    }
	return RCC_ErrorStatus;
}


E_ErrorStatus_t RCC_SetPLLSource(u8 RCC_PLLSrc)
{
	E_ErrorStatus_t RCC_SetPLLConfigurationError = E_InvalidParameter;

	switch(RCC_PLLSrc)
	{
	case SysClock_HSI:
	if(RCC->RCC_CR &SysClock_HSI){}
	}

}

E_ErrorStatus_t RCC_SetPLLConfiguration(u8 RCC_PLLM, u16 RCC_PLLN, u8 RCC_PLLP, u8 RCC_PLLQ)
{

	E_ErrorStatus_t RCC_SetPLLConfigurationError = E_InvalidParameter;
	u32 Loc_PllConfig = 0;

	//check if the entered values within the range
	if ((RCC_PLLM >= 2 && RCC_PLLM <= 63) &&
	    (RCC_PLLN >= 192 && RCC_PLLN <= 432) &&
	    (RCC_PLLP == 2 || RCC_PLLP == 4 || RCC_PLLP == 6 || RCC_PLLP == 8) &&
	    (RCC_PLLQ >= 2 && RCC_PLLQ <= 15)) {

	     Loc_PllConfig  |= (RCC_PLLM & RCC_PLL_M_PRESCALE_MASK);
		 Loc_PllConfig |= (RCC_PLLN & RCC_PLL_N_PRESCALE_MASK);
		 Loc_PllConfig |= (RCC_PLLP & RCC_PLL_P_PRESCALE_MASK);
		 Loc_PllConfig |= (RCC_PLLQ & RCC_PLL_Q_PRESCALE_MASK);

		 // Clear existing PLL configuration bits in RCC_PLLCFGR registe
		 RCC->RCC_PLLCFGR &= ~(RCC_PLL_M_PRESCALE_MASK | RCC_PLL_N_PRESCALE_MASK | RCC_PLL_P_PRESCALE_MASK | RCC_PLL_Q_PRESCALE_MASK);

		 // Apply the new PLL configuration to RCC_PLLCFGR register
		 RCC->RCC_PLLCFGR |= Loc_PllConfig;

		RCC_SetPLLConfigurationError = E_ValidParameter;


	}

	else {

	    return RCC_SetPLLConfigurationError=  E_InvalidParameter;
	}
}



E_ErrorStatus_t RCC_EnablePeripheral(PERIPHRAL PeriphralId)
{
    E_ErrorStatus_t RCC_GetPeriError = E_Peripheral_clk_Disabled;

    switch(PeriphralId)
    {

        case PERIPHRAL_DMA_1:
            RCC->RCC_AHB1ENR |= BIT_21_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_DMA_2:
            RCC->RCC_AHB1ENR |=BIT_22_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_ADC_1:
            RCC->RCC_APB2ENR |=BIT_8_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_CRC:
            RCC->RCC_AHB1ENR |=BIT_11_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_SYSCFG:
            RCC->RCC_APB2ENR |= BIT_14_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_GPIO_A:
            RCC->RCC_AHB1ENR |= BIT_0_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_GPIO_B:
            RCC->RCC_AHB1ENR  |= BIT_1_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_GPIO_C:
            RCC->RCC_AHB1ENR  |= BIT_2_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_GPIO_D:
            RCC->RCC_AHB1ENR  |=BIT_3_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_GPIO_E:
            RCC->RCC_AHB1ENR  |=BIT_4_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
        break;

        case PERIPHRAL_GPIO_H:
            RCC->RCC_AHB1ENR  |=BIT_7_MASK;
            RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_I2C_1:
			RCC->RCC_APB1ENR  |=BIT_21_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_I2C_2:
			RCC->RCC_APB1ENR  |= BIT_22_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

	    case PERIPHRAL_I2C_3:
	    	RCC->RCC_APB1ENR  |=BIT_23_MASK;
	    	RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_OTG_FS:
			RCC->RCC_AHB2ENR  |=BIT_7_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_PWR_INTFC:
			RCC->RCC_APB1ENR  |=BIT_28_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_SDIO:
			RCC->RCC_APB2ENR  |=BIT_11_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_SPI_1:
			RCC->RCC_APB2ENR  |= BIT_12_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_SPI_2:
			RCC->RCC_APB1ENR  |=BIT_14_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_SPI_3:
			RCC->RCC_APB1ENR  |=BIT_15_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_SPI_4:
			RCC->RCC_APB2ENR  |=BIT_13_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_TIMER_1:
			RCC->RCC_APB2ENR  |=BIT_0_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_TIMER_2:
			RCC->RCC_APB1ENR  |=BIT_0_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_TIMER_3:
			RCC->RCC_APB1ENR |=BIT_1_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_TIMER_4:
			RCC->RCC_APB1ENR  |=BIT_2_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_TIMER_5:
			RCC->RCC_APB1ENR  |=BIT_3_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_TIMER_9:
			RCC->RCC_APB2ENR  |=BIT_16_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_TIMER_10:
			RCC->RCC_APB2ENR  |=BIT_17_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_TIMER_11:
			RCC->RCC_APB2ENR  |=BIT_18_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_WWDG:
			RCC->RCC_APB1ENR  |=BIT_10_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_USART_1:
			RCC->RCC_APB2ENR  |= BIT_4_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_USART_2:
			RCC->RCC_APB1ENR  |=BIT_17_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		case PERIPHRAL_USART_6:
			RCC->RCC_APB2ENR  |= BIT_5_MASK;
			RCC_GetPeriError = E_Peripheral_clk_Enabled;
		break;

		default:RCC_GetPeriError = E_Peripheral_clk_Disabled;;
		break;


	}
	return RCC_GetPeriError;

}

E_ErrorStatus_t RCC_DisablePeripheral(PERIPHRAL PeriphralId)
{
    E_ErrorStatus_t RCC_GetPeriError = E_Peripheral_clk_Enabled;

    switch (PeriphralId)
    {

    case PERIPHRAL_DMA_1:
        RCC->RCC_AHB1ENR &= ~BIT_21_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_DMA_2:
        RCC->RCC_AHB1ENR &= ~BIT_22_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_ADC_1:
        RCC->RCC_APB2ENR &= ~BIT_8_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_CRC:
        RCC->RCC_AHB1ENR &= ~BIT_11_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_SYSCFG:
        RCC->RCC_APB2ENR &= ~BIT_14_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_GPIO_A:
        RCC->RCC_AHB1ENR &= ~BIT_0_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_GPIO_B:
        RCC->RCC_AHB1ENR &= ~BIT_1_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_GPIO_C:
        RCC->RCC_AHB1ENR &= ~BIT_2_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_GPIO_D:
        RCC->RCC_AHB1ENR &= ~BIT_3_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_GPIO_E:
        RCC->RCC_AHB1ENR &= ~BIT_4_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_GPIO_H:
        RCC->RCC_AHB1ENR &= ~BIT_7_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_I2C_1:
        RCC->RCC_APB1ENR &= ~BIT_21_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_I2C_2:
        RCC->RCC_APB1ENR &= ~BIT_22_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_I2C_3:
        RCC->RCC_APB1ENR &= ~BIT_23_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_OTG_FS:
        RCC->RCC_AHB2ENR &= ~BIT_7_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_PWR_INTFC:
        RCC->RCC_APB1ENR &= ~BIT_28_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_SDIO:
        RCC->RCC_APB2ENR &= ~BIT_11_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_SPI_1:
        RCC->RCC_APB2ENR &= ~BIT_12_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_SPI_2:
        RCC->RCC_APB1ENR &= ~BIT_14_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_SPI_3:
        RCC->RCC_APB1ENR &= ~BIT_15_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_SPI_4:
        RCC->RCC_APB2ENR &= ~BIT_13_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_TIMER_1:
        RCC->RCC_APB2ENR &= ~BIT_0_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_TIMER_2:
        RCC->RCC_APB1ENR &= ~BIT_0_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_TIMER_3:
        RCC->RCC_APB1ENR &= ~BIT_1_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_TIMER_4:
        RCC->RCC_APB1ENR &= ~BIT_2_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_TIMER_5:
        RCC->RCC_APB1ENR &= ~BIT_3_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_TIMER_9:
        RCC->RCC_APB2ENR &= ~BIT_16_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_TIMER_10:
        RCC->RCC_APB2ENR &= ~BIT_17_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_TIMER_11:
        RCC->RCC_APB2ENR &= ~BIT_18_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_WWDG:
        RCC->RCC_APB1ENR &= ~BIT_10_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_USART_1:
        RCC->RCC_APB2ENR &= ~BIT_4_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_USART_2:
        RCC->RCC_APB1ENR &= ~BIT_17_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    case PERIPHRAL_USART_6:
        RCC->RCC_APB2ENR &= ~BIT_5_MASK;
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;

    default:
        RCC_GetPeriError = E_Peripheral_clk_Disabled;
        break;
    }

    return RCC_GetPeriError;
}



