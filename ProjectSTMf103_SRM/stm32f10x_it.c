/**
  ******************************************************************************
  * @file    RCC/RCC_ClockConfig/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"
#include "an_srm.h"
//#include "an_srm.h"



//USB


extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
extern __IO  uint32_t length ;
extern uint8_t Send_Buffer[64];
extern uint32_t packet_sent;
extern uint32_t packet_receive;

extern uint8_t USB_Flag;

//const
extern float const pi;
//Ctrl
extern ControlStateVar CtrlState;
extern FlagVar omega_flag;

__IO uint16_t IC_Hall_Value1 = 0, IC_Hall_Value2 = 0;
__IO uint8_t CaptureFlag = 0;	// Co bao ngat de xu ly toc do
__IO uint32_t Capture = 0;
__IO float Hall_Fre = 0, Hall_Calib_Fre = 0;
__IO float Hall_rpm = 0;
__IO FlagVar Hall_IT_Sector_Flag = Reset;

__IO uint8_t Hall_Sector = 100;
__IO uint16_t Port_B;

uint32_t const Hall_Tim_Fre = Sys_Clock / Hall_PreScaler;
uint32_t const HallOR_Tim_Fre = Sys_Clock / HallOR_Prescaler;
//theta
float theta2 = 0, theta = 0;
extern uint8_t theta_update_flag;
extern uint8_t Hall_IC_flag;
uint8_t Mec_Index = 111;

float arrCalibFactor[48] = 
													/* {0.3800, 1.1663, 1.5752, 0.7284, 1.0404, 0.9971, 
														1.1816, 0.7165, 1.5033, 0.7209, 1.1826, 0.9361, 
														1.0500, 0.8030, 1.6392, 0.6852, 0.9895, 1.0852, 
														1.2340, 0.6525, 1.4331, 0.9362, 0.8748, 1.0117, 

														1.2595, 0.7004, 1.3695, 0.9118, 0.8695, 1.0887, 
														1.3580, 0.5724, 1.4318, 1.0854, 0.7790, 0.9516, 
														1.5180, 0.6178, 1.3315, 0.9716, 0.8468, 1.0582, 
														0.7716, 1.9181, 0.7786, 0.5791, 1.5507, 2.3527}; //1.9847 */					

/*													
														{0.355, 1.174, 1.584, 0.728, 1.048, 1.001, 
														1.185, 0.717, 1.515, 0.721, 1.183, 0.941, 
														1.051, 0.801, 1.645, 0.686, 0.983, 1.084, 
														1.234, 0.648, 1.436, 0.933, 0.872, 1.012, 

														1.253, 0.698, 1.361, 0.907, 0.865, 1.094, 
														1.348, 0.569, 1.424, 1.089, 0.772, 0.954, 
														1.507, 0.613, 1.319, 0.975, 0.837, 1.065, 
														0.765, 1.963, 0.771, 0.578, 1.558, 2.017};*/

												 	 {0.3392,	1.1839,	1.5795,	0.7267,	1.0439,	0.9881,
														1.1899,	0.7147,	1.5103,	0.7173,	1.1892,	0.9268,
														1.0547,	0.8022,	1.6457,	0.6810,	0.9952,	1.0758,
														1.2393,	0.6523,	1.4404, 0.9300,	0.8801,	1.0039,
														1.2668,	0.6993,	1.3742,	0.9082,	0.8738,	1.0811,
														1.3650,	0.5719,	1.4354,	1.0836,	0.7801,	0.9480,
														1.5296,	0.6142,	1.3337,	0.9806,	0.8381,	1.0566,
														0.7636,	2.0204,	0.7472,	0.5738,	1.5767,	2.1650};
float wCalibFactor[48] = 	
												 	 /*{0.4895, 1.5106, 1.2737, 0.8085, 1.1100, 1.0668, //0.5 1.4
														1.0698, 0.9055, 1.2637, 0.8406, 1.1659, 0.9859,
														1.0532, 1.0031, 1.2492, 0.7620, 1.1122, 1.1230,
														1.0357, 0.8393, 1.2863, 0.8975, 0.9587, 1.0959,
	
														1.0832, 0.8600, 1.2278, 0.8966, 0.9832, 1.1308,
														1.0386, 0.7647, 1.3362, 0.9333, 0.8598, 1.1038,
														1.1599, 0.7641, 1.2368, 0.9289, 0.9560, 1.1289,
														1.0667, 1.3826, 0.6931, 0.9258, 1.5987, 1.0310}; */

													 {0.4803,	1.4455,	1.2210,	0.7730,	1.0637,	1.0190, //0:
													  1.0313,	0.8667,	1.2126,	0.8029,	1.1193,	0.9412,
													  1.0156,	0.9629,	1.2003,	0.7294,	1.0710,	1.0762,
													  1.0003,	0.8072,	1.2375,	0.8592,	0.9238,	1.0497,
														 
													  1.0457,	0.8254,	1.1804,	0.8590,	0.9458,	1.0824,
													  1.0012,	0.7335,	1.2826,	0.8935,	0.8246,	1.0570,
													  1.1150,	0.7290,	1.1868,	0.8899,	0.9075,	1.0828,
														1.0248,	1.3421,	0.6720,	0.8890,	1.5495,	0.9827}; // 44:.6643
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup RCC_ClockConfig
  * @{
  */ 
uint16_t countSys = 0;
extern void TimingDelay_Decrement(void);
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
  /* This interrupt is generated when HSE clock fails */

  if (RCC_GetITStatus(RCC_IT_CSS) != RESET)
  {/* At this stage: HSE, PLL are disabled (but no change on PLL config) and HSI
       is selected as system clock source */

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Enable HSE Ready interrupt */
    RCC_ITConfig(RCC_IT_HSERDY, ENABLE);

#ifndef SYSCLK_HSE
 #ifdef STM32F10X_CL
    /* Enable PLL and PLL2 Ready interrupts */
    RCC_ITConfig(RCC_IT_PLLRDY | RCC_IT_PLL2RDY, ENABLE);
 #else
    /* Enable PLL Ready interrupt */
    RCC_ITConfig(RCC_IT_PLLRDY, ENABLE);
 #endif	/* STM32F10X_CL */
#endif /* SYSCLK_HSE */

    /* Clear Clock Security System interrupt pending bit */
    RCC_ClearITPendingBit(RCC_IT_CSS);

    /* Once HSE clock recover, the HSERDY interrupt is generated and in the RCC ISR
       routine the system clock will be reconfigured to its previous state (before
       HSE clock failure) */
  }
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	theta_update_flag = 1;
  TimingDelay_Decrement();
	countSys++;
	if (USB_Flag == 0)
	{
	if (countSys == USB_Set_Flag)
	{			
		USB_Flag = 1;
		countSys = 0;
	}
	}
	else
			if (countSys == omega_sample)
		{			
			omega_flag = Set;
			countSys = 0;
		} 
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles RCC interrupt request. 
  * @param  None
  * @retval None
  */
void RCC_IRQHandler(void)
{
  if(RCC_GetITStatus(RCC_IT_HSERDY) != RESET)
  { 
    /* Clear HSERDY interrupt pending bit */
    RCC_ClearITPendingBit(RCC_IT_HSERDY);

    /* Check if the HSE clock is still available */
    if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
    { 
#ifdef SYSCLK_HSE
      /* Select HSE as system clock source */
      RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
#else
 #ifdef STM32F10X_CL
      /* Enable PLL2 */
      RCC_PLL2Cmd(ENABLE);
 #else
      /* Enable PLL: once the PLL is ready the PLLRDY interrupt is generated */ 
      RCC_PLLCmd(ENABLE);
 #endif	/* STM32F10X_CL */
#endif /* SYSCLK_HSE */      
    }
  }

#ifdef STM32F10X_CL
  if(RCC_GetITStatus(RCC_IT_PLL2RDY) != RESET)
  { 
    /* Clear PLL2RDY interrupt pending bit */
    RCC_ClearITPendingBit(RCC_IT_PLL2RDY);

    /* Enable PLL: once the PLL is ready the PLLRDY interrupt is generated */ 
    RCC_PLLCmd(ENABLE);
  }
#endif /* STM32F10X_CL */   

  if(RCC_GetITStatus(RCC_IT_PLLRDY) != RESET)
  { 
    /* Clear PLLRDY interrupt pending bit */
    RCC_ClearITPendingBit(RCC_IT_PLLRDY);

    /* Check if the PLL is still locked */
    if (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET)
    { 
      /* Select PLL as system clock source */
      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    }
  }
}



/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{ 
//	if(TIM_GetITStatus(Hall_Tim, Hall_IT_W | Hall_IT_U |Hall_IT_V)

	//GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12)));	
/*  if(TIM_GetITStatus(Hall_Tim, Hall_IT_W) == SET) 
  {
		GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12)));

    TIM_ClearITPendingBit(Hall_Tim, Hall_IT_W);
		
	  if(CaptureFlag == 0)
    {
      IC_Hall_Value1 = TIM_GetCapture2(Hall_Tim); //Get the Input Capture value
      CaptureFlag = 1;
    }
		else if(CaptureFlag == 1)
    {
      IC_Hall_Value2 = TIM_GetCapture2(Hall_Tim);  //Get the Input Capture value
      
      if (IC_Hall_Value2 > IC_Hall_Value1) //Capture computation
      {
        Capture = (IC_Hall_Value2 - IC_Hall_Value1); 
      }
      else
      {
        Capture = ((0xFFFF - IC_Hall_Value1) + IC_Hall_Value2); 
      }
      Hall_Fre = (float) Hall_Tim_Fre / Capture; //Frequency computation 
	//		Hall_Fre = Hall_Fre / 8;
      CaptureFlag = 0;
    }
*/

	  if (TIM_GetITStatus(Hall_Tim, Hall_IT_Velocity) != RESET) 
		{ 
			TIM_ClearITPendingBit(Hall_Tim, Hall_IT_Velocity); 
			Hall_IC_flag = 1;
			//Identify what mechanical sector rotor stands 
			Capture = TIM4->CCR1;
			if ( (Hall_Sector == 5)  && ( (float) VelocityCheckingFator *Hall_Fre < (float) HallOR_Tim_Fre / (48*Capture)))
			{
				Mec_Index = 0;
			}
			else { Mec_Index ++;}
			Hall_Fre = (float) HallOR_Tim_Fre / (48*Capture);     // calculate motor  speed or else with CCR1 values
			Hall_Calib_Fre = Hall_Fre*arrCalibFactor[Mec_Index];
			Hall_rpm = Hall_Fre*wCalibFactor[Mec_Index];
		} 
		else if (TIM_GetITStatus(Hall_Tim, Hall_IT_Sector) != RESET) 
		{ 
//			GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12)));	
			TIM_ClearITPendingBit(Hall_Tim, Hall_IT_Sector); 
			Hall_IT_Sector_Flag = Set; // -> SetupMotor_SinglePhase()			
			Port_B = ((GPIO_ReadInputData(GPIOB) & 0x01C0) >> 6); //Pin B876
			switch (Port_B)
			{
				case 0:
					CaptureFlag = 9;
					break;
				case 1:
					Hall_Sector = 2; //U
					CaptureFlag = 1; // 4 W
					break;
				case 2:
					Hall_Sector = 0; //U
					CaptureFlag = 1;	// 2W
					break;
				case 3:
					Hall_Sector = 1; //U
					CaptureFlag = 1;	// 3W
					break;
				case 4:
					Hall_Sector = 4;//U
					CaptureFlag = 1;// 0W
					break;
				case 5:
					Hall_Sector = 3;//U
					CaptureFlag = 1;// 5W
					break;
				case 6:
					Hall_Sector = 5;//U
					CaptureFlag = 1;// 1W
					break;
				case 8:
					CaptureFlag = 11;
					break;
				default: 
					CaptureFlag = 15;
					break;
				}

			theta = 60*Hall_Sector;
//			theta2 = 60*Hall_Sector*pi/180;				
//			if (CtrlState == Initiate) 
//						{SetupMotor_SinglePhase();}
  }
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
