/**
  ******************************************************************************
  * @file    an_srm.h
  * @author  Nguyen Van An
  * @version V1.0.0
  * @date    Nov-2019
  * @brief   This file contains all the functions prototypes for the SRM
  *          library.
  *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AN_SRM_H
#define __AN_SRM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"

//USB
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include <math.h>
#include <string.h>
#include <stdio.h>


#define Sys_Clock 72000000
#define Sys_tick 1000
#define theta_period 0.001
#define Tim3_Clock 1000000
#define fswitch 500
#define USB_Set_Flag 20000

#define VelocityCheckingFator 1.7
#define hertz2degree 360
#define Hall_PreScaler 720
#define HallOR_Prescaler 180
#define Hall_Period 0xFFFF
//#define Hall_Tim_Fre SystemCoreClock/Hall_PreScaler

#define Hall_Port GPIOB
#define Hall_Tim TIM4
#define Hall_IRQn TIM4_IRQn
#define Hall_Polarity_Falling TIM_ICPolarity_Falling
#define Hall_Polarity_Rising TIM_ICPolarity_Rising

#define Hall_Pin_U GPIO_Pin_8
#define Hall_Pin_V GPIO_Pin_7
#define Hall_Pin_W GPIO_Pin_6

#define Hall_Channel_U TIM_Channel_3
#define Hall_Channel_V TIM_Channel_2
#define Hall_Channel_W TIM_Channel_1
#define Hall_IT_W TIM_IT_CC1
#define Hall_IT_V TIM_IT_CC2
#define Hall_IT_U TIM_IT_CC3
#define Hall_Channel_OR TIM_Channel_1
#define Hall_IT_Velocity TIM_IT_CC1
#define Hall_IT_Sector TIM_IT_CC2

#define Fet_Tim TIM3
#define FetL_Port GPIOA
#define FetL_PinW 1
#define FetL_PinV 2
#define FetL_PinU 3

//ADC & DMA
#define ADC_Sensor ADC1
#define DMA_Channel DMA1_Channel1
#define Sensor_ChannelU ADC_Channel_0
#define Sensor_ChannelV ADC_Channel_4
#define Sensor_ChannelW ADC_Channel_5
#define Sensor_num 3
#define ADC_Port GPIOA
#define ADC_Woffset 3120 //.4
#define ADC_Voffset 3122 //.5
#define ADC_Uoffset 3133 //.2
//Kalman variance
#define mea_eV 0.05 //R
#define mea_eW 0.1 //R
#define mea_eU 0.05 //R
#define est_e 0.004 //gia tri khoi tao
#define q_e 0.001 //Q

//Current control
#define deltaI 0.2
#define kpw 0.0149
#define kiw 0.0093
#define omega_sample 10 //so chu ky de trich mau w
#define Lac 0.007
#define rpole 8
#define iqmax 3.5f

//enum
typedef enum {PhaseW = 2, PhaseV = 3, PhaseU = 4} PhaseName; //Vang - Duong - La - Quay chieu thuan kim dong ho
typedef enum {Disable = 0, Enable = !Disable} PhaseState;	
					
typedef enum {Reset = 0, Set = !Reset} FlagVar;
typedef enum {CreatingIRQ = 0, Initiate = 1, Regular = 2} ControlStateVar;
static __IO uint32_t TimingDelay;

//kalman struct
typedef struct 
				{
					  float _err_measure;
						float _err_estimate;
						float const _q;
						float _current_estimate;
						float _last_estimate;
						float _kalman_gain;
				} Kalman_Struct;
// Timer 3 2
static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
static TIM_OCInitTypeDef  TIM_OCInitStructure;
//Timer 1 IC
static TIM_ICInitTypeDef  TIM_ICInitStructure;

//GPIO
static GPIO_InitTypeDef GPIO_InitStructure;

static uint16_t CCR1_Val = 0*333;
static uint16_t CCR2_Val = 0*249;
static uint16_t CCR3_Val = 0*166;
static uint16_t CCR4_Val = 0*83;


//DMA
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
static ADC_InitTypeDef ADC_InitStructure;
static DMA_InitTypeDef DMA_InitStructure;

//USB
extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
extern __IO  uint32_t length ;
extern uint8_t Send_Buffer[64];
extern uint32_t packet_sent;
extern uint32_t packet_receive;
extern uint8_t USB_Flag;
extern uint8_t An[];
extern uint16_t an, a, b, c, d, e, f, g, h;
extern uint8_t state;

void ADC_Config(void);
void Current_Theta(void);
float cosdeg(float x);
void Data_ReceiveUSB(void);
void Data_TransmissionUSB(void);
void Delay(__IO uint32_t nTime);
void DMA_Config(void);
void dqo2uvw(float id, float iq, float io, float *iu, float* iv, float* iw);
void uvw2dqo(float iu, float iv, float iw, float *id, float* iq, float* io);
float absolute(float x);
void GPIO_Configuration(void);
void Hall_Tim_Init(void);
void Hall_Tim_ORInit(void);
void Hys_Current(void);
float KalmanSimple(Kalman_Struct *kstruct, float mea);
void PWM_OC1(TIM_TypeDef* TIMx,float duty);
void PWM_OC2(TIM_TypeDef* TIMx,float duty);
void PWM_OC3(TIM_TypeDef* TIMx,float duty);
void PWM_OC4(TIM_TypeDef* TIMx,float duty);
void RCC_Configuration(void);
void TimingDelay_Decrement(void);
void Tim3_Init(void);
void Tim2_Init(void);
void SetupMotor(void);
void SetupMotor_SinglePhase(void);
void Send_Data(float a, float b);
void Send_Data2(float a, float b, float c, float d, float e, float f, float g, float h);
float sindeg(float x);
void SwitchPhase(PhaseName Phase, PhaseState NewState);
void SwitchSingle(PhaseName Phase, PhaseState NewState);
void delay_ms(uint16_t delay); //bo
void delay_us(uint32_t delay); //bo



/*

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))
*/

#ifdef __cplusplus
}
#endif

#endif /* __AN_SRM_H */

/******************* (C) COPYRIGHT 2019 Nguyen Van An *****END OF FILE****/
