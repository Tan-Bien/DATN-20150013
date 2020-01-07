/**
  ******************************************************************************
  * @file    RCC/RCC_ClockConfig/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body.
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "an_srm.h"
#include "GPIO_STM32F10x.h"


//IC

//USB
extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
extern __IO  uint32_t length ;
uint8_t Send_Buffer[64];
uint32_t packet_sent=1;
uint32_t packet_receive=1;

uint8_t USB_Flag;
uint8_t An[100] = "NguNguoiRoi12345678HaHa!\r\n";
uint16_t an = 0, a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8;


/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */
//#define ADC1_DR_Address    ((uint32_t)0x4001244C)
//ADC_InitTypeDef ADC_InitStructure;
//DMA_InitTypeDef DMA_InitStructure;
__IO uint16_t ADCConvertedValue[3] = {0, 0, 0};
float Ucurrent = 0, Vcurrent = 0, Wcurrent = 0;

//Hall
__IO extern uint8_t Hall_Sector;
__IO extern float Hall_Fre, Hall_Calib_Fre, Hall_rpm;
__IO uint8_t Hall_IC_flag = 10;
__IO extern FlagVar Hall_IT_Sector_Flag;


//theta:
__IO uint8_t theta_update_flag = 10;
extern float theta, theta2;


//Control
ControlStateVar CtrlState = CreatingIRQ;
float idref = 0, iqref = 0, ioref = 0;
float iuref = 0, ivref = 0, iwref = 0;
 float idfb = 0, iqfb = 0, iofb = 0;
__IO float iufb = 0, ivfb = 0, iwfb = 0;
//float fl = 0;
FlagVar omega_flag = Reset;
float omega_ref = 2.5;
float ek1 = 0, ek = 0;
float Te_ref = 0;

//const
extern float const pi;
extern float const trf_cst23;
extern float const trf_cst12;
extern float const trf_cst2pi3;

//Kalman
extern Kalman_Struct iustruct, iwstruct, ivstruct;

/** @addtogroup RCC_ClockConfig
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DELAY_COUNT    0x3FFFF


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

RCC_ClocksTypeDef RCC_ClockFreq;
ErrorStatus HSEStartUpStatus;

	uint8_t B6 = 2, B8 = 2, B7 = 2;
	uint8_t state = 10;
/* Private function prototypes -----------------------------------------------*/
void NVIC_Configuration(void);


void SetSysClock(void);
#ifdef SYSCLK_HSE
  void SetSysClockToHSE(void);
#elif defined SYSCLK_FREQ_24MHz
  void SetSysClockTo24(void);
#elif defined SYSCLK_FREQ_36MHz
  void SetSysClockTo36(void);
#elif defined SYSCLK_FREQ_48MHz
  void SetSysClockTo48(void);
#elif defined SYSCLK_FREQ_56MHz
  void SetSysClockTo56(void);  
#elif defined SYSCLK_FREQ_72MHz
  void SetSysClockTo72(void);
#endif

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	


int main(void)
{

	// RCC set up external clock
  SetSysClock();
  RCC_GetClocksFreq(&RCC_ClockFreq);
  RCC_ClockSecuritySystemCmd(ENABLE);
     
  /* NVIC configuration ------------------------------------------------------*/
  NVIC_Configuration();

  if (SysTick_Config(SystemCoreClock / Sys_tick))
  { 
    /* Capture error */ 
    while (1);
  }
//end
	//Clock to periph
  RCC_Configuration();
	
  /* GPIO Configuration */
  GPIO_Configuration();
	Tim3_Init();
//	Tim2_Init();
	GPIO_PinConfigure(FetL_Port, FetL_PinW, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
	GPIO_PinConfigure(FetL_Port, FetL_PinV, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
	GPIO_PinConfigure(FetL_Port, FetL_PinU, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
	
	GPIO_PinWrite(FetL_Port, FetL_PinU, 1);
	GPIO_PinWrite(FetL_Port, FetL_PinV, 1);
	GPIO_PinWrite(FetL_Port, FetL_PinW, 1);	
	
	GPIO_PinWrite(GPIOB, 12, 0);
//	GPIO_PinConfigure(GPIOB, 13, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
//	GPIO_PinWrite(GPIOB, 13, 1);
	
	
	Hall_Tim_ORInit();
	ADC_Config();
	DMA_Config();
 
//	Hall_Tim_Init(); //in the case using three independent Inpuc Caputre of Hall Timer

//	SwitchPhase(PhaseV, Enable);

//	Delay(2000);
//	theta = theta2;
	
  Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();


	SetupMotor();
	idref = 0; iqref =2.449;  ioref = 3.464;// 3.674; 5.196;
	iufb = 1; iwfb = 1; ivfb = 1; iofb = 1; iqfb = 1; idfb = 0;
	theta2 = 0;
	while(1)
	{
		if (theta_update_flag)
		{	
			Current_Theta();
/*			iufb++;
			if (iufb >= 360) iufb -= 360;
			iuref = sindeg(theta);
			ivref = cosdeg(theta);*/
			
//			uvw2dqo(iuref, ivref, iwref, &idfb, &iqfb, &iofb);

/*			iwfb =  KalmanSimple(&iwstruct, (float) ADCConvertedValue[0]);
			ivfb =  KalmanSimple(&ivstruct, (float) ADCConvertedValue[1]);
			iufb =  KalmanSimple(&iustruct, (float) ADCConvertedValue[2]);	*/	
						if ((CtrlState == Initiate) && (Hall_IT_Sector_Flag == Set) )
						{
							SwitchPhase(PhaseU, Disable);						SwitchPhase(PhaseV, Disable);						SwitchPhase(PhaseW, Disable);						
	//						SetupMotor_SinglePhase();
							Hall_IT_Sector_Flag = Reset; } 
						else if (CtrlState == Regular) {Hys_Current();}
			theta_update_flag = 0;			
		}

				//	for (int i = 0; i < 1; i++);	
//		B6 = 1*GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
//		B8 = 2*GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);
//		B7 = 3*GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);
		if (USB_Flag == 1)
		{
			CtrlState = Regular;
		//	SwitchPhase(PhaseU, Enable);
//			Data_ReceiveUSB();
//			Data_TransmissionUSB();
//			USB_Flag = 0;
			
		}
		if ( (CtrlState == Regular) && (omega_flag == Set) )
		{
		//	if(Hall_rpm > 5) break;
			ek = omega_ref - Hall_rpm;
			Te_ref = Te_ref + 0.5*kpw*(ek-ek1)+kiw*ek1*0.001;
			
							if (Te_ref < 0.0001) {Te_ref = 0.0001;}
				ek1 = sqrt(Te_ref/(rpole*Lac));
			(ek1 < iqmax) ? (iqref = ek1):(iqref = iqmax);		
			ioref = 2*trf_cst12*iqref;	
	/*		if (Te_ref >= 0)
			{
				if (Te_ref < 0.05) {Te_ref = 0.05;}
				ek1 = sqrt(Te_ref/(rpole*Lac));
			(ek1 < iqmax) ? (iqref = ek1):(iqref = iqmax);		
			ioref = 2*trf_cst12*iqref;				
			}
			else
			{
				if (Te_ref > -0.05) {Te_ref = -0.05;}
				ek1 = -sqrt(-Te_ref/(rpole*Lac));
			(-ek1 < iqmax) ? (iqref = ek1):(iqref = -iqmax);		
			ioref = -2*trf_cst12*iqref;				
			}		 */
	//		(ek1 < iqmax) ? (iqref = ek1):(iqref = iqmax);
	//		ioref = 2*trf_cst12*iqref;
			ek1 = ek;
		}
	}

/*  GPIO_PinConfigure(GPIOB, 12, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
		GPIO_PinWrite(GPIOB, 12, 0);
    delay_us(500);

		GPIO_PinWrite(GPIOB, 12, 1);
    delay_us(500); */
	/*
	
	float duty = 0;
		PWM_OC3(TIM2,duty);
		PWM_OC4(TIM2,duty);
		PWM_OC1(TIM3,duty);
		PWM_OC2(TIM3,duty);
		PWM_OC3(TIM3,duty);
		PWM_OC4(TIM3,duty);
		
	uint32_t waitms = 500;
	for (int i = 0; i < 5; i++)
	{
		PWM_OC3(TIM3,100);		//Off
		PWM_OC4(TIM3,100);
		PWM_OC3(TIM2,5);		//PhA
		PWM_OC4(TIM2,5);
		Delay(waitms);
		
		PWM_OC3(TIM2,100);		
		PWM_OC4(TIM2,100);
		PWM_OC1(TIM3,5);		//PhB
		PWM_OC2(TIM3,5);
		Delay(waitms);
		
		PWM_OC1(TIM3,100);		
		PWM_OC2(TIM3,100);
		PWM_OC3(TIM3,5);		//PhC
		PWM_OC4(TIM3,5);
		Delay(waitms);
	}
	*/
	
}

/**
  * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1
  *         prescalers.
  * @param  None
  * @retval None
  */
void SetSysClock(void)
{    
/* The System clock configuration functions defined below assume that:
        - For Low, Medium and High density devices an external 8MHz crystal is
          used to drive the System clock.
        - For Connectivity line devices an external 25MHz crystal is used to drive
          the System clock.
     If you are using different crystal you have to adapt those functions accordingly.*/

#if defined SYSCLK_HSE
  SetSysClockToHSE();
#elif defined SYSCLK_FREQ_24MHz
  SetSysClockTo24();  
#elif defined SYSCLK_FREQ_36MHz
  SetSysClockTo36();
#elif defined SYSCLK_FREQ_48MHz
  SetSysClockTo48();
#elif defined SYSCLK_FREQ_56MHz
  SetSysClockTo56(); 
#elif defined SYSCLK_FREQ_72MHz
  SetSysClockTo72();
#endif
 
 /* If none of the define above is enabled, the HSI is used as System clock
    source (default after reset) */ 
}

/**
  * @brief  Selects HSE as System clock source and configure HCLK, PCLK2
  *         and PCLK1 prescalers. 
  * @param  None
  * @retval None
  */
void SetSysClockToHSE(void)
{
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
#if !defined STM32F10X_LD_VL && !defined STM32F10X_MD_VL && !defined STM32F10X_HD_VL
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

#ifndef STM32F10X_CL
    /* Flash 0 wait state */
    FLASH_SetLatency(FLASH_Latency_0);
#else
    if (HSE_Value <= 24000000)
	{
      /* Flash 0 wait state */
      FLASH_SetLatency(FLASH_Latency_0);
	}
	else
	{
      /* Flash 1 wait state */
      FLASH_SetLatency(FLASH_Latency_1);
	}

#endif /* STM32F10X_CL */
#endif /* STM32F10X_LD_VL && STM32F10X_MD_VL */
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK */
    RCC_PCLK1Config(RCC_HCLK_Div1);

    /* Select HSE as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x04)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */    

    /* Go to infinite loop */
    while (1)
    {
    }
  }
}

/**
  * @brief  Sets System clock frequency to 24MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @param  None
  * @retval None
  */
void SetSysClockTo24(void)
{
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
#if !defined STM32F10X_LD_VL && !defined STM32F10X_MD_VL && !defined STM32F10X_HD_VL
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 0 wait state */
    FLASH_SetLatency(FLASH_Latency_0);
#endif /* STM32F10X_LD_VL && STM32F10X_MD_VL */
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK */
    RCC_PCLK1Config(RCC_HCLK_Div1);

#ifdef STM32F10X_CL
    /* Configure PLLs *********************************************************/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    RCC_PLL2Config(RCC_PLL2Mul_8);

    /* Enable PLL2 */
    RCC_PLL2Cmd(ENABLE);

    /* Wait till PLL2 is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
    {}

    /* PLL configuration: PLLCLK = (PLL2 / 10) * 6 = 24 MHz */ 
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div10);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6);
#elif defined STM32F10X_LD_VL || defined STM32F10X_MD_VL || defined STM32F10X_HD_VL 
    /* PLLCLK = (8MHz/2) * 6 = 24 MHz */
    RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE, RCC_PREDIV1_Div2);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6);
#else
    /* PLLCLK = 8MHz * 3 = 24 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_3);
#endif

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */    

    /* Go to infinite loop */
    while (1)
    {
    }
  }
}
#if !defined STM32F10X_LD_VL && !defined STM32F10X_MD_VL && !defined STM32F10X_HD_VL
/**
  * @brief  Sets System clock frequency to 36MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @param  None
  * @retval None
  */
void SetSysClockTo36(void)
{
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 1 wait state */
    FLASH_SetLatency(FLASH_Latency_1);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK */
    RCC_PCLK1Config(RCC_HCLK_Div1);

#ifdef STM32F10X_CL
    /* Configure PLLs *********************************************************/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    RCC_PLL2Config(RCC_PLL2Mul_8);

    /* Enable PLL2 */
    RCC_PLL2Cmd(ENABLE);

    /* Wait till PLL2 is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
    {}

    /* PLL configuration: PLLCLK = (PLL2 / 10) * 9 = 36 MHz */ 
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div10);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
#else
    /* PLLCLK = (8MHz / 2) * 9 = 36 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);
#endif

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */    

    /* Go to infinite loop */
    while (1)
    {
    }
  }
}

/**
  * @brief  Sets System clock frequency to 48MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @param  None
  * @retval None
  */
void SetSysClockTo48(void)
{
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 1 wait state */
    FLASH_SetLatency(FLASH_Latency_1);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

#ifdef STM32F10X_CL
    /* Configure PLLs *********************************************************/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    RCC_PLL2Config(RCC_PLL2Mul_8);

    /* Enable PLL2 */
    RCC_PLL2Cmd(ENABLE);

    /* Wait till PLL2 is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
    {}

    /* PLL configuration: PLLCLK = (PLL2 / 5) * 6 = 48 MHz */ 
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6);
#else
    /* PLLCLK = 8MHz * 6 = 48 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);
#endif

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */    

    /* Go to infinite loop */
    while (1)
    {
    }
  }
}

/**
  * @brief  Sets System clock frequency to 56MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @param  None
  * @retval None
  */
void SetSysClockTo56(void)
{
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

#ifdef STM32F10X_CL
    /* Configure PLLs *********************************************************/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    RCC_PLL2Config(RCC_PLL2Mul_8);

    /* Enable PLL2 */
    RCC_PLL2Cmd(ENABLE);

    /* Wait till PLL2 is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
    {}

    /* PLL configuration: PLLCLK = (PLL2 / 5) * 7 = 56 MHz */ 
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_7);
#else
    /* PLLCLK = 8MHz * 7 = 56 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_7);
#endif

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */    

    /* Go to infinite loop */
    while (1)
    {
    }
  }
}

/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @param  None
  * @retval None
  */
void SetSysClockTo72(void)
{
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

#ifdef STM32F10X_CL
    /* Configure PLLs *********************************************************/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    RCC_PLL2Config(RCC_PLL2Mul_8);

    /* Enable PLL2 */
    RCC_PLL2Cmd(ENABLE);

    /* Wait till PLL2 is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
    {}

    /* PLL configuration: PLLCLK = (PLL2 / 5) * 9 = 72 MHz */ 
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
#else
    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
#endif

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */    

    /* Go to infinite loop */
    while (1)
    {
    }
  }
}

#endif /* STM32F10X_LD_VL && STM32F10X_MD_VL */

/**
  * @brief  Configures Vector Table base location.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable and configure RCC global IRQ channel */
  NVIC_InitStructure.NVIC_IRQChannel = RCC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  NVIC_InitStructure.NVIC_IRQChannel = Hall_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
