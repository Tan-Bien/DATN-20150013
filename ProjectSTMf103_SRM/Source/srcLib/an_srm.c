/**
  ******************************************************************************
  * @file    an_srm.h
  * @author  Nguyen Van An
  * @version V1.0.0
  * @date    Nov-2019
  * @brief   This file contains all the functions prototypes for the SRM
  *          library.
  *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "an_srm.h"
#include <math.h>

//Timer
uint16_t PrescalerTim3 = 0;
uint16_t const PWM_Period = (uint16_t) (Tim3_Clock / fswitch) - 1; //Timer 2 3
//Constant
float const pi = 3.1415926;
float const trf_cst23 = 0.81649658092;
float const trf_cst12 = 0.70710678118;
float const trf_cst13 = 0.5773502692;
float const trf_cst2pi3 = 120;//2*pi/3;
//Hall
__IO extern uint8_t Hall_Sector;
__IO extern float Hall_Fre, Hall_Calib_Fre;
// theta
extern float theta, theta2;
//sin cos
uint8_t sin_sector = 0;
float sinarr[256] = 
/*										{0.00000,	0.01227,	0.02454,	0.03681,	0.04907,	0.06132,	0.07356,	0.08580, //1 8
										 0.09802,	0.11022,	0.12241,	0.13458,	0.14673,	0.15886,	0.17096,	0.18304,
										 0.19509,	0.20711,	0.21910,	0.23106,	0.24298,	0.25487,	0.26671,	0.27852,
										 0.29028,	0.30201,	0.31368,	0.32531,	0.33689,	0.34842,	0.35990,	0.37132,
										 0.38268,	0.39399,	0.40524,	0.41643,	0.42756,	0.43862,	0.44961,	0.46054,
										 0.47140,	0.48218,	0.49290,	0.50354,	0.51410,	0.52459,	0.53500,	0.54532,
										 0.55557,	0.56573,	0.57581,	0.58580,	0.59570,	0.60551,	0.61523,	0.62486,
										 0.63439,	0.64383,	0.65317,	0.66242,	0.67156,	0.68060,	0.68954,	0.69838,

										 0.70711,	0.71573,	0.72425,	0.73265,	0.74095,	0.74914,	0.75721,	0.76517, //9-16
										 0.77301,	0.78074,	0.78835,	0.79584,	0.80321,	0.81046,	0.81758, 0.82459,
										 0.83147,	0.83822,	0.84485,	0.85136,	0.85773,	0.86397,	0.87009,	0.87607,
										 0.88192,	0.88764,	0.89322,	0.89867,	0.90399,	0.90917,	0.91421,	0.91911,
										 0.92388,	0.92851,	0.93299,	0.93734,	0.94154,	0.94561,	0.94953,	0.95331,
										 0.95694,	0.96043,	0.96378,	0.96698,	0.97003,	0.97294,	0.97570,	0.97832,
										 0.98079,	0.98311,	0.98528,	0.98730,	0.98918,	0.99090,	0.99248,	0.99391,
										 0.99518,	0.99631,	0.99729,	0.99812,	0.99880,	0.99932,	0.99970,	0.99992,

										 1.00000,	0.99992,	0.99970,	0.99932,	0.99880,	0.99812,	0.99729, 0.99631, //17 - 24
										 0.99518,	0.99391,	0.99248,	0.99090,	0.98918,	0.98730,	0.98528,	0.98311,
										 0.98079,	0.97832,	0.97570,	0.97294,	0.97003,	0.96698,	0.96378,	0.96043,
										 0.95694,	0.95331,	0.94953,	0.94561,	0.94154,	0.93734,	0.93299,	0.92851,
										 0.92388,	0.91911,	0.91421,	0.90917,	0.90399,	0.89867,	0.89322,	0.88764,
										 0.88192,	0.87607,	0.87009,	0.86397,	0.85773,	0.85136,	0.84485,	0.83822,
										 0.83147,	0.82459,	0.81758,	0.81046,	0.80321,	0.79584,	0.78835,	0.78074,
										 0.77301,	0.76517,	0.75721,	0.74914,	0.74095,	0.73265,	0.72425,	0.71573,

										 0.70711,	0.69838,	0.68954,	0.68060,	0.67156,	0.66242,	0.65317,	0.64383, //25-32
										 0.63439,	0.62486,	0.61523,	0.60551,	0.59570,	0.58580,	0.57581,	0.56573,
										 0.55557,	0.54532,	0.53500,	0.52459,	0.51410,	0.50354,	0.49290,	0.48218,
										 0.47140,	0.46054,	0.44961,	0.43862,	0.42756,	0.41643,	0.40524,	0.39399,
										 0.38268,	0.37132,	0.35990,	0.34842,	0.33689,	0.32531,	0.31368,	0.30201,
										 0.29028,	0.27852,	0.26671,	0.25487,	0.24298,	0.23106,	0.21910,	0.20711,
										 0.19509,	0.18304,	0.17096,	0.15886,	0.14673,	0.13458,	0.12241,	0.11022,
										 0.09802,	0.08580,	0.07356,	0.06132,	0.04907,	0.03681,	0.02454,	0.01227};*/
										 
										{0.00000,	0.00616,	0.01232,	0.01848,	0.02464,	0.03080,	0.03695,	0.04311,
										 0.04926,	0.05541,	0.06156,	0.06771,	0.07385,	0.07999,	0.08613,	0.09227,
										 0.09840,	0.10453,	0.11065,	0.11677,	0.12289,	0.12900,	0.13511,	0.14121,
										 0.14730,	0.15339,	0.15948,	0.16555,	0.17163,	0.17769,	0.18375,	0.18980,
										 0.19585,	0.20188,	0.20791,	0.21393,	0.21995,	0.22595,	0.23195,	0.23794,
										 0.24391,	0.24988,	0.25584,	0.26179,	0.26773,	0.27366,	0.27958, 	0.28549,
										 0.29139,	0.29728,	0.30315,	0.30902,	0.31487,	0.32071,	0.32654,	0.33235,
										 0.33816,	0.34395,	0.34973,	0.35549,	0.36124,	0.36698,	0.37270,	0.37841,

									     0.38411,	0.38979,	0.39545,	0.40110,	0.40674,	0.41236,	0.41796,	0.42355,
										 0.42912,	0.43468,	0.44022,	0.44574,	0.45124,	0.45673,	0.46220,	0.46766,
										 0.47309,	0.47851,	0.48391,	0.48929,	0.49466,	0.50000,	0.50533,	0.51063,
										 0.51592,	0.52118,	0.52643,	0.53166,	0.53687,	0.54205,	0.54722,	0.55236,
										 0.55749,	0.56259,	0.56767,	0.57274,	0.57777,	0.58279,	0.58779,	0.59276,
										 0.59771,	0.60263,	0.60754,	0.61242,	0.61728,	0.62211,	0.62692,	0.63171,
										 0.63647,	0.64121,    0.64593,	0.65062,	0.65528,	0.65992,	0.66454,	0.66913,
										 0.67370,	0.67824,	0.68275,	0.68724,	0.69170,	0.69613,	0.70054,	0.70493,

										 0.70928,	0.71361,	0.71791,	0.72219,	0.72643,	0.73065,	0.73484,	0.73901,
										 0.74314,	0.74725,	0.75133,	0.75538,	0.75940,	0.76340,	0.76736,	0.77130,
										 0.77520,	0.77908,	0.78293,	0.78674,	0.79053,	0.79429,	0.79802,	0.80171,
										 0.80538,	0.80902,	0.81262,	0.81620,	0.81974,	0.82325,	0.82673,	0.83018,
										 0.83360,	0.83699,	0.84034,	0.84367,	0.84696,	0.85022,	0.85344,	0.85664,
										 0.85980,	0.86293,	0.86603,	0.86909,	0.87212,	0.87512,	0.87808,	0.88101,
										 0.88391,	0.88677,	0.88960,	0.89240,	0.89516,	0.89789,	0.90059,	0.90325,
										 0.90587,   0.90847,	0.91102,	0.91355,	0.91603,	0.91849,	0.92091,	0.92329,

										 0.92564,	0.92795,	0.93023,	0.93247,	0.93468,	0.93685,	0.93899,	0.94109,
										 0.94315,	0.94518,	0.94718,	0.94913,	0.95106,	0.95294,	0.95479,	0.95660,
										 0.95838,	0.96012,	0.96183,	0.96349,	0.96512,	0.96672,	0.96828,	0.96980,
										 0.97128,	0.97273,	0.97414,	0.97551,	0.97685,	0.97815,	0.97941,	0.98063,
										 0.98182,	0.98297,	0.98409,	0.98516,	0.98620,	0.98720,	0.98817,	0.98909,
										 0.98998,	0.99083,	0.99164,	0.99242,	0.99316,	0.99386,	0.99452,	0.99515,
										 0.99573,	0.99628,	0.99680,	0.99727,	0.99771,	0.99810,	0.99846,	0.99879,
										 0.99907,   0.99932,	0.99953,	0.99970,	0.99983,	0.99992,	0.99998,	1.00000};

//Control
extern ControlStateVar CtrlState;
extern float idref, iqref, ioref;
extern float iuref, ivref, iwref;
extern float iufb, ivfb, iwfb;
extern float idfb, iqfb, iofb;
extern FlagVar omega_flag;

//extern uint8_t Hall_Sector;
extern FlagVar Hall_IT_Sector_Flag;
extern __IO uint16_t ADCConvertedValue[3];

//Kalman
Kalman_Struct iustruct = {mea_eU, est_e, q_e}, ivstruct = {mea_eV, est_e, q_e}, iwstruct = {mea_eW, est_e, q_e};

void ADC_Config()
{
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = Sensor_num;
  ADC_Init(ADC_Sensor, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC_Sensor, Sensor_ChannelW, 1, ADC_SampleTime_71Cycles5);
  ADC_RegularChannelConfig(ADC_Sensor, Sensor_ChannelV, 2, ADC_SampleTime_71Cycles5);	
  ADC_RegularChannelConfig(ADC_Sensor, Sensor_ChannelU, 3, ADC_SampleTime_71Cycles5);
	
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC_Sensor, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC_Sensor, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC_Sensor);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC_Sensor));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC_Sensor);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC_Sensor));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC_Sensor, ENABLE);
}
//
void Current_Theta(void)
{
	theta += Hall_Calib_Fre*8*(2*180)*theta_period; //rms to degree
//	theta += 40*(360)*theta_period; 	
	if (theta >= 360) {theta -= 360;}
	dqo2uvw(idref, iqref, ioref, &iuref, &ivref, &iwref);
	
//	theta2 += Hall_Calib_Fre*(8*2*pi)*theta_period; 
//	if (theta2 >= 360) { theta2 -= 360;  iofb = 0;}
	
	iwfb = 	((float) ADC_Woffset - KalmanSimple(&iwstruct, (float) ADCConvertedValue[0]))*82.5/4095;
	ivfb = 	((float) ADC_Voffset - KalmanSimple(&ivstruct, (float) ADCConvertedValue[1]))*82.5/4095;
	iufb =  ((float) ADC_Uoffset - KalmanSimple(&iustruct, (float) ADCConvertedValue[2]))*82.5/4095;
	uvw2dqo(iufb, ivfb, iwfb, &idfb, &iqfb, &iofb);

//	Hys_Current();
	//	theta_update_flag = 0;
}
//
float cosdeg(float x)
{
/*	if (x < 0) {x += 360;}
	if (x <= 180.0)
	{
		sin_sector = (uint8_t) (128+x*64.0/45.0); // /180.f*256.f chon vung
		if(x<=90) {return sinarr[sin_sector];}
		else {return -sinarr[sin_sector];}
	}
	else
	{
		sin_sector = (uint8_t) (128+(x-180.0)*64.0/45.0);
		if (x>=270) {return sinarr[sin_sector];}
		else {return -sinarr[sin_sector];}
	}	
*/
	
//cos -> sin
	x+=90;
	if(x<0) x+= 360;
	else if(x > 360) x -= 360;
	
	if ( x <= 180)
	{
		if(x<=90) 
			{	sin_sector = (uint8_t) x*51.0/18.0;} // 255/90 chon vung			
		else
			{sin_sector = (uint8_t) (180-x)*51.0/18.0;} //góc bù
		return sinarr[sin_sector];
	}
	else
	{
		x-= 180; // tính qua góc doi dinh
		if(x<=90) 
			{	sin_sector = (uint8_t) x*51.0/18.0;} // 255/90 chon vung			
		else
			{sin_sector = (uint8_t) (180-x)*51.0/18.0;} //góc bù
		return -sinarr[sin_sector];		
	}	
}
//
void Data_ReceiveUSB(void)
{
		if (bDeviceState == CONFIGURED)
    {
      CDC_Receive_DATA();
      //Check to see if we have data yet
      if (Receive_length  != 0)
      {
				if (Receive_Buffer[0] == '0') state = 0;
				else if (Receive_Buffer[0] == '1') state = 1;
			}
       Receive_length = 0;
		}
}
void Data_TransmissionUSB(void)
{
        if  ((packet_sent == 1) &&  (state == 1 ))
				{
					//Send_Data(sin(a), sin(b));
					Send_Data2(4*sin(a/20), 4*sin(b/20), 4*sin(c/20), 4*sin(d/20), 4*sin(e/20), 4*sin(f/20), 4*sin(g/20), 4*sin(h/20));
					GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12)));	
					a++; b++; c++; d++; e++; f++; g++; h++;
				}
//        CDC_Send_DATA ((unsigned char*)Receive_Buffer,Receive_length);
//				An[18] = 0;
//				An[19] = 10;
//				An[20] = 13;
		//	CDC_Send_DATA(An, 21);

				an = strlen((const char*)An);	
}
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
//
void DMA_Config(void)
{
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADCConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 3;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA_Channel, &DMA_InitStructure);
		 
  DMA_Cmd(DMA_Channel, ENABLE);  /* Enable DMA1 channel1 */
}
// 
void dqo2uvw(float id, float iq, float io, float *iu, float* iv, float* iw)
{
			*iu = trf_cst23*( id*(float)cosdeg(theta-0*trf_cst2pi3) 
										- iq*(float)sindeg(theta-0*trf_cst2pi3) + io*trf_cst12);
		*iv = trf_cst23*( id*(float)cosdeg(theta-1*trf_cst2pi3)
										- iq*(float)sindeg(theta-1*trf_cst2pi3) + io*trf_cst12);
		*iw = trf_cst23*( id*(float)cosdeg(theta-2*trf_cst2pi3)
										- iq*(float)sindeg(theta-2*trf_cst2pi3) + io*trf_cst12);
		
		/*
		*iu = trf_cst23*( id*(float)cos(theta-0*trf_cst2pi3) 
										- iq*(float)sin(theta-0*trf_cst2pi3) + io*trf_cst12);
		*iv = trf_cst23*( id*(float)cos(theta-1*trf_cst2pi3)
										- iq*(float)sin(theta-1*trf_cst2pi3) + io*trf_cst12);
		*iw = trf_cst23*( id*(float)cos(theta-2*trf_cst2pi3)
										- iq*(float)sin(theta-2*trf_cst2pi3) + io*trf_cst12);*/
}
//
void uvw2dqo(float iu, float iv, float iw, float *id, float* iq, float* io)
{
			*id =  trf_cst23*( iu*(float)cosdeg(theta-0*trf_cst2pi3)
										+ iv*(float)cosdeg(theta-1*trf_cst2pi3) + iw*(float)cosdeg(theta-2*trf_cst2pi3));
		*iq = -trf_cst23*( iu*(float)sindeg(theta-0*trf_cst2pi3)
										+ iv*(float)sindeg(theta-1*trf_cst2pi3) + iw*(float)sindeg(theta-2*trf_cst2pi3));	
		*io =  trf_cst13*( iu + iv + iw);
		/*
		*id =  trf_cst23*( iu*(float)cos(theta-0*trf_cst2pi3)
										+ iv*(float)cos(theta-1*trf_cst2pi3) + iw*(float)cos(theta-2*trf_cst2pi3));
		*iq = -trf_cst23*( iu*(float)sin(theta-0*trf_cst2pi3)
										+ iv*(float)sin(theta-1*trf_cst2pi3) + iw*(float)sin(theta-2*trf_cst2pi3));	
		*io =  trf_cst12*( iu*trf_cst23 + iv*trf_cst23 + iw*trf_cst23);		*/
}
//
float absolute(float x)
{
	return (x >= 0)? (x):(-x);
}
//
void GPIO_Configuration(void)
{

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7; //Timer 2 channel 1 - 4, MOSFET
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//Timer 3 Channel 3, 4, MOSFET
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	//IC
  GPIO_InitStructure.GPIO_Pin =  Hall_Pin_U | Hall_Pin_V | Hall_Pin_W;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(Hall_Port, &GPIO_InitStructure);
	
	//	GPIO - led
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//ADC
  GPIO_InitStructure.GPIO_Pin = Sensor_ChannelU | Sensor_ChannelV | Sensor_ChannelW;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(ADC_Port, &GPIO_InitStructure);
}


//
void Hall_Tim_Init(void)
{
  TIM_TimeBaseStructure.TIM_Prescaler = Hall_PreScaler;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = Hall_Period;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(Hall_Tim, &TIM_TimeBaseStructure);
	
	
  TIM_ICInitStructure.TIM_Channel =  Hall_Channel_U;
  TIM_ICInitStructure.TIM_ICPolarity = Hall_Polarity_Rising;//Hall_Polarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(Hall_Tim, &TIM_ICInitStructure);
	
  TIM_ICInitStructure.TIM_Channel =  Hall_Channel_V;	
  TIM_ICInit(Hall_Tim, &TIM_ICInitStructure);
	
  TIM_ICInitStructure.TIM_Channel =  Hall_Channel_W;	
  TIM_ICInit(Hall_Tim, &TIM_ICInitStructure);	
	
	  /* TIM enable counter */
  TIM_Cmd(Hall_Tim, ENABLE);
	
	  /* Enable the CC2,3,4 W V U Interrupt Request */
  TIM_ITConfig(Hall_Tim, Hall_IT_U | Hall_IT_V | Hall_IT_W, ENABLE); //| Hall_IT_U
}
//
void Hall_Tim_ORInit(void)
{
		///HALLL
  TIM_TimeBaseStructure.TIM_Prescaler = HallOR_Prescaler; 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_TimeBaseStructure.TIM_Period = Hall_Period; 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
  TIM_TimeBaseInit(Hall_Tim, &TIM_TimeBaseStructure); 

  TIM_SelectHallSensor(Hall_Tim, ENABLE); 
  TIM_SelectInputTrigger(Hall_Tim, TIM_TS_TI1F_ED); //Edge detector
	TIM_SelectSlaveMode(Hall_Tim, TIM_SlaveMode_Reset); 
//  TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);

  TIM_ICInitStructure.TIM_Channel = Hall_Channel_OR; 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; 
  // listen to T1, the  HallSensorEvent 
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_TRC;
  // Div:1, every edge 
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  // noise filter: 1111 => 72000kHz / factor (==1) / 32 / 8 -> 281kHz 
  // input noise filter (reference manual page 322) 
  TIM_ICInitStructure.TIM_ICFilter = 0x0; 
  TIM_ICInit(Hall_Tim, &TIM_ICInitStructure); 

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
  TIM_OCInitStructure.TIM_Pulse = 1; // 1 is no delay; 2000 = 7ms
  TIM_OC2Init(Hall_Tim, &TIM_OCInitStructure); 
  TIM_ClearFlag(Hall_Tim, TIM_FLAG_CC2); 
	TIM_ITConfig(Hall_Tim, Hall_IT_Velocity | Hall_IT_Sector, ENABLE);
  TIM_Cmd(Hall_Tim, ENABLE); 

	TIM_SelectOutputTrigger(Hall_Tim, TIM_TRGOSource_OC2Ref); //Cho TIM1 neu dung voi BLDC
}
//
void Hys_Current()
{ //SwitchSingle()
	if ((iufb + deltaI) < iuref) {SwitchPhase(PhaseU, Enable);} 				//the desired value domain of current  
	else if ((iufb - deltaI) > iuref) {SwitchPhase(PhaseU, Disable);} //is between iref +- deltaI
	
	if ((ivfb + deltaI) < ivref) {SwitchPhase(PhaseV, Enable);} //turn on when to be below
	else if ((ivfb - deltaI) > ivref) {SwitchPhase(PhaseV, Disable);} //turn off when to be above

	if ((iwfb + deltaI) < iwref) {SwitchPhase(PhaseW, Enable);}
	else if ((iwfb - deltaI) > iwref) {SwitchPhase(PhaseW, Disable);}	
}
//
float KalmanSimple(Kalman_Struct *kstruct, float mea)
{
  kstruct->_kalman_gain 			= kstruct->_err_estimate/(kstruct->_err_estimate + kstruct->_err_measure);
  kstruct->_current_estimate 	= kstruct->_last_estimate + kstruct->_kalman_gain * (mea - kstruct->_last_estimate);
  kstruct->_err_estimate	 		=  (1.0 - kstruct->_kalman_gain)*kstruct->_err_estimate
																	+ kstruct->_q*absolute(kstruct->_last_estimate - kstruct->_current_estimate);
  kstruct->_last_estimate 		= kstruct->_current_estimate;

  return kstruct->_current_estimate;
}
//
void PWM_OC1(TIM_TypeDef* TIMx,float duty)
{
	if (duty == 0) 
		{
			TIMx->CCR1 = 0;
		}
	else if (duty == 100)
		{
			TIMx->CCR1 = PWM_Period + 2;
		}
	else
	{
	TIMx->CCR1 = (uint16_t) duty * (PWM_Period - 1) / 100;
	}
}
void PWM_OC2(TIM_TypeDef* TIMx,float duty)
{
	if (duty == 0) 
		{
			TIMx->CCR2 = 0;
		}
	else if (duty == 100)
		{
			TIMx->CCR2 = PWM_Period + 2;
		}
	else
	{
	TIMx->CCR2 = (uint16_t) duty * (PWM_Period - 1) / 100;
	}
}
void PWM_OC3(TIM_TypeDef* TIMx,float duty)
{
	if (duty == 0) 
		{
			TIMx->CCR3 = 0;
		}
	else if (duty == 100)
		{
			TIMx->CCR3= PWM_Period + 2;
		}
	else
	{
	TIMx->CCR3 = (uint16_t) duty * (PWM_Period - 1) / 100;
	}
}
void PWM_OC4(TIM_TypeDef* TIMx,float duty)
{
	if (duty == 0) 
		{
			TIMx->CCR4 = 0;
		}
	else if (duty == 100)
		{
			TIMx->CCR4 = PWM_Period + 2;
		}
	else
	{
	TIMx->CCR4 = (uint16_t) duty * (PWM_Period - 1) / 100;
	}
}

//
void RCC_Configuration(void)
{
	//ADC
	  RCC_ADCCLKConfig(RCC_PCLK2_Div6); //12MHz
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO | RCC_APB2Periph_ADC1, ENABLE); //ADC
}
//
void SetupMotor(void)
{
	if(CtrlState == CreatingIRQ) //Status when power is turned on
	{
		Delay(1000); //Wait to get Hall_Sector's value	
		switch (Hall_Sector)
		{
			case 0:
				SwitchPhase(PhaseV, Enable);		
				break;
			case 1:
				SwitchPhase(PhaseV, Enable);
				SwitchPhase(PhaseW, Enable);
				break;
			case 2:
				SwitchPhase(PhaseW, Enable);
				break;
			case 3:
				SwitchPhase(PhaseW, Enable);
				SwitchPhase(PhaseU, Enable);
				break;
			case 4:
				SwitchPhase(PhaseU, Enable);
				break;
			case 5:
				SwitchPhase(PhaseU, Enable);
				SwitchPhase(PhaseV, Enable);
				break;
			default:
				SwitchPhase(PhaseU, Disable);
				SwitchPhase(PhaseV, Disable);
				SwitchPhase(PhaseW, Disable);
				break;				
		}
		CtrlState = Initiate;
	}
}
//
void SetupMotor_SinglePhase()
{
	uint8_t sector = 0;
	if (Hall_IT_Sector_Flag != Reset) //Using updated Hall_Sector
	{
		sector = Hall_Sector;	
		Hall_IT_Sector_Flag = Reset;
	}
	else //Using old Hall_Sector
	{
		(Hall_Sector + 1 == 6) ? (sector = 0) : (sector = Hall_Sector + 1) ;
		sector = Hall_Sector+1; 
	}
	switch (sector)
		{
			case 0:
				SwitchPhase(PhaseU, Disable);
				SwitchPhase(PhaseV, Enable);
				break;
			case 1:
				SwitchPhase(PhaseV, Disable);
				SwitchPhase(PhaseW, Enable);
				break;
			case 2:
				SwitchPhase(PhaseV, Disable);
				SwitchPhase(PhaseW, Enable);
				break;
			case 3:
				SwitchPhase(PhaseW, Disable);
				SwitchPhase(PhaseU, Enable);
				break;
			case 4:
				SwitchPhase(PhaseW, Disable);
				SwitchPhase(PhaseU, Enable);
				break;
			case 5:
				SwitchPhase(PhaseU, Disable);
				SwitchPhase(PhaseV, Enable);
				break;
			default:
				SwitchPhase(PhaseU, Disable);
				SwitchPhase(PhaseV, Disable);
				SwitchPhase(PhaseW, Disable);
				break;				
		}
}
//
void Send_Data(float a, float b)
{
		sprintf((char*)An, "%5.2f|%5.2f\r\n", a, b);				
		CDC_Send_DATA(An, 13);
}
void Send_Data2(float a, float b, float c, float d, float e, float f, float g, float h)
{
		sprintf((char*)An, "%5.2f|%5.2f|%5.2f|%5.2f|%5.2f|%5.2f|%5.2f|%5.2f\r\n", a, b, c, d, e, f, g, h);				
		CDC_Send_DATA(An, (uint8_t) strlen((const char*)An)); //49
}
//
float sindeg(float x)
{
/*	
	if (x < 0) {x += 360;}
	if(x <= 180.0)
	{
		sin_sector = (uint8_t) x*64.0/45.0; // /180.f*256.f chon vung
		return sinarr[sin_sector];
	}
	else
	{
		sin_sector = (uint8_t) (x-180.0)*64.0/45.0;
		return -sinarr[sin_sector];
	}
*/
	if(x<0) x += 360;
	if ( x <= 180)
	{
		if(x<=90) 
			{	sin_sector = (uint8_t) x*51.0/18.0;} // 255/90 chon vung			
		else
			{sin_sector = (uint8_t) (180-x)*51.0/18.0;} //góc bù
		return sinarr[sin_sector];
	}
	else
	{
		x-= 180; // tính qua góc doi dinh
		if(x<=90) 
			{	sin_sector = (uint8_t) x*51.0/18.0;} // 255/90 chon vung			
		else
			{sin_sector = (uint8_t) (180-x)*51.0/18.0;} //góc bù
		return -sinarr[sin_sector];		
	}
}
//
void SwitchPhase(PhaseName Phase, PhaseState NewState)
{
	if (Phase == PhaseU)
	{
		if (NewState == Disable)
		{
				PWM_OC4(Fet_Tim,0);
				GPIO_PinWrite(FetL_Port, FetL_PinU, 1);
		}
		else
		{
				PWM_OC4(Fet_Tim,5);
				GPIO_PinWrite(FetL_Port, FetL_PinU, 0);
		}
	}
	
	else if (Phase == PhaseV)
	{
		if (NewState == Disable)
		{
				PWM_OC3(Fet_Tim,0);
				GPIO_PinWrite(FetL_Port, FetL_PinV, 1);
		}
		else
		{
				PWM_OC3(Fet_Tim,5);
				GPIO_PinWrite(FetL_Port, FetL_PinV, 0);
		}
	}
	else if (Phase == PhaseW)
	{	
		if (NewState == Disable)
		{
				PWM_OC2(Fet_Tim,0);
				GPIO_PinWrite(FetL_Port, FetL_PinW, 1);
		}
		else
		{
				PWM_OC2(Fet_Tim,5);
				GPIO_PinWrite(FetL_Port, FetL_PinW, 0);
		}
	}
}
//
void SwitchSingle(PhaseName Phase, PhaseState NewState)
{
	if (Phase == PhaseU)
	{
		PWM_OC4(Fet_Tim,5);
		if (NewState == Disable)
		{
				GPIO_PinWrite(FetL_Port, FetL_PinU, 1);
		}
		else
		{
				GPIO_PinWrite(FetL_Port, FetL_PinU, 0);
		}
	}
	else if (Phase == PhaseV)
	{
				PWM_OC3(Fet_Tim,5);		
		if (NewState == Disable)
		{
				GPIO_PinWrite(FetL_Port, FetL_PinV, 1);
		}
		else
		{
				GPIO_PinWrite(FetL_Port, FetL_PinV, 0);
		}
	}
	else if (Phase == PhaseW)
	{	
				PWM_OC2(Fet_Tim,5);		
		if (NewState == Disable)
		{
				GPIO_PinWrite(FetL_Port, FetL_PinW, 1);
		}
		else
		{
				GPIO_PinWrite(FetL_Port, FetL_PinW, 0);
		}
	}
}
//
void Tim3_Init(void)
{
	PrescalerTim3 = (uint16_t) (Sys_Clock / (Tim3_Clock)) - 1;
	
  TIM_TimeBaseStructure.TIM_Period = PWM_Period;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerTim3;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM3, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
	
}

//
void Tim2_Init(void) //almost basic parameters are similar to timer 3
{
		PrescalerTim3 = (uint16_t) (Sys_Clock / Tim3_Clock) - 1;
	
  TIM_TimeBaseStructure.TIM_Period = PWM_Period;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerTim3;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC3Init(TIM2, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);


  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  TIM_OC4Init(TIM2, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	

  TIM_ARRPreloadConfig(TIM2, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}

//
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

//

/*
{
	if(x<0) x += 360;
	if ( x <= 180)
	{
		if(x<=90) 
			{	sin_sector = (uint8_t) x*51.0/18.0;} // 255/90 chon vung			
		else
			{sin_sector = (uint8_t) (180-x)*51.0/18.0;} //góc bù
		return arr[sin_sector];
	}
	else
	{
		x-= 180; // tính qua góc doi dinh
		if(x<=90) 
			{	sin_sector = (uint8_t) x*51.0/18.0;} // 255/90 chon vung			
		else
			{sin_sector = (uint8_t) (180-x)*51.0/18.0;} //góc bù
		return -arr[sin_sector];		
	}
}

{//cos -> sin
		x+=90;
	if(x<0) x+= 360;
	if(x > 360) x -= 360;
	
	if ( x <= 180)
	{
		if(x<=90) 
			{	sin_sector = (uint8_t) x*51.0/18.0;} // 255/90 chon vung			
		else
			{sin_sector = (uint8_t) (180-x)*51.0/18.0;} //góc bù
		return arr[sin_sector];
	}
	else
	{
		x-= 180; // tính qua góc doi dinh
		if(x<=90) 
			{	sin_sector = (uint8_t) x*51.0/18.0;} // 255/90 chon vung			
		else
			{sin_sector = (uint8_t) (180-x)*51.0/18.0;} //góc bù
		return -arr[sin_sector];		
	}	
}
*/

// bo
void delay_ms(uint16_t delay){
	SysTick->CTRL &= 5UL;                                       /* clear flag systick*/
	SysTick->VAL   = 0UL; 
	while(delay--){
		while(!(SysTick->CTRL >>16)&1UL);                         /* wait until flag is set*/
		SysTick->CTRL &= 5UL;                                     /* clear flag systick*/
	}
}

//bo
void delay_us(uint32_t delay){
	SysTick->CTRL &= 5UL;                                       /* clear flag systick*/
	SysTick->VAL   = 0UL; 
	while(delay--){
		while(!(SysTick->CTRL >>16)&1UL);                         /* wait until flag is set*/
		SysTick->CTRL &= 5UL;                                     /* clear flag systick*/
	}
}





/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
