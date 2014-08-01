/*
 * init.h
 *
 *  Created on: Aug 1, 2014
 *      Author: Jakub Trzyna
 */

#ifndef INIT_H_
#define INIT_H_

volatile unsigned int Batt_4_5_value;
volatile unsigned int Batt_3_5_value;
volatile unsigned int Batt_2_5_value;
volatile unsigned int Batt_1_5_value;
volatile unsigned int Batt_critical_value;

void init_TIM2()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // w��cza zegar dla peryferium TIM2

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // dzielnik 1
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up; // licznik w g�r�
	TIM_InitStruct.TIM_Period = 222; // okres licznika 222us
	TIM_InitStruct.TIM_Prescaler = 7; // preskaler 8
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct); // inicjalizuje TIM2
	//wywo�anie przerwania z f=50hz, regulacja 90krok�w w kadym

	TIM_ClearFlag( TIM2, TIM_FLAG_Update ); // czy�ci flag� aktualizacji TIM2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // w��cza przerwanie aktualizacji TIM2
	TIM_Cmd(TIM2, ENABLE); // w��cza timer TIM2

	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn; // wyb�r linii przerwania
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; // w��czenie linii
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; // priorytet
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0; // podgrupa
	NVIC_Init(&NVIC_InitStruct); // inicjalizacja linii przerwania
}


void set_SupplyVoltage(volatile float MaxVoltage)
{
	float ADC_MaxVoltage = MaxVoltage/4.2;
	float ADC_MinVoltage = 0.71*ADC_MaxVoltage;

	float ADC_Diffrence = (ADC_MaxVoltage - ADC_MinVoltage)*0.2;
	float x4_5 = ADC_MaxVoltage - ADC_Diffrence;
	float x3_5 = x4_5 - ADC_Diffrence;
	float x2_5 = x3_5 - ADC_Diffrence;
	float x1_5 = x2_5 - ADC_Diffrence;
	float xCritical = x1_5 - ADC_Diffrence;

	Batt_4_5_value = x4_5*4096/3.3;
	Batt_3_5_value = x3_5*4096/3.3;
	Batt_2_5_value = x2_5*4096/3.3;
	Batt_1_5_value = x1_5*4096/3.3;
	Batt_critical_value = xCritical*4096/3.3;
}

void init_LED()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //enable clock on leds port

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit (& GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6| GPIO_Pin_8 |GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11 |GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void init_ADC()
{
	set_SupplyVoltage(12.6);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit (& GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //conf pin PA0 as intput, ADC mode
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_InitStructure);

	//conf adc channel
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_13Cycles5);

	//start converter
	ADC_Cmd(ADC1, ENABLE);

	//calibration
	ADC_ResetCalibration( ADC1 );
	while(ADC_GetResetCalibrationStatus( ADC1 ));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus (ADC1) == SET);

	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //start conversion
}


#endif /* INIT_H_ */
