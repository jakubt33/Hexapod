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


void init_Bluetooth()
{
  //w³¹czenie zegara portu
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  //struktura inicjalizacyjna portu
  GPIO_InitTypeDef  GPIO_InitStructure;

  //Pin PB10 - linia nadawcza USART3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;                   //piny które chcemy skonfigurowaæ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;               //tryb wyjœæ portu - wyjœcie push-pull
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //szybkoœæ wyjœcia
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //Pin PB11 - linia odbiorcza USART3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;                   //piny które chcemy skonfigurowaæ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               	//tryb wyjœæ portu - wyjœcie push-pull
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //szybkoœæ wyjœcia
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //w³¹czenie zegara USARTa
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate=9600;                   	 //Prêdkoæ transmisji - 9600BAUD
  USART_InitStructure.USART_Mode= USART_Mode_Tx | USART_Mode_Rx;  //Tryb pracy - w³¹czony odbiornik oraz nadajnik
  USART_InitStructure.USART_Parity=USART_Parity_No;              //Bity parzystosci - brak
  USART_InitStructure.USART_StopBits=USART_StopBits_1;           //Bity stopu - 1
  USART_InitStructure.USART_WordLength=USART_WordLength_8b;      //D³ugosc ramki - 8 bitów
  USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //Sprzêtowa kontrola przep³ywu - brak
  USART_Init(USART3,&USART_InitStructure);

    //Uruchomienie USART3
    USART_Cmd(USART3,ENABLE);

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  	//connection established indicator
	GPIO_InitTypeDef GPIO_InitStructur;
	GPIO_StructInit (& GPIO_InitStructur);
	GPIO_InitStructur.GPIO_Pin = CONNECTIONPIN ;
	GPIO_InitStructur.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructur.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(BTPORT, &GPIO_InitStructur);
}


void init_TIM2()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // w³¹cza zegar dla peryferium TIM2

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // dzielnik 1
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up; // licznik w górê
	TIM_InitStruct.TIM_Period = 10*3; // okres licznika 10 us, 2stopnie serwo
	TIM_InitStruct.TIM_Prescaler = 32; // preskaler 56  = 46Hz
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct); // inicjalizuje TIM2

	TIM_ClearFlag( TIM2, TIM_FLAG_Update ); // czyœci flagê aktualizacji TIM2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // w³¹cza przerwanie aktualizacji TIM2
	TIM_Cmd(TIM2, ENABLE); // w³¹cza timer TIM2

	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn; // wybór linii przerwania
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; // w³¹czenie linii
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; // priorytet
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0; // podgrupa
	NVIC_Init(&NVIC_InitStruct); // inicjalizacja linii przerwania
}

void init_Clock()
{
	ErrorStatus HSEStartUpStatus;
	// Reset ustawien RCC
	RCC_DeInit();
	// Wlacz HSE
	RCC_HSEConfig(RCC_HSE_ON);
	// Czekaj za HSE bedzie gotowy
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	 	// zwloka dla pamieci Flash
		FLASH_SetLatency(FLASH_Latency_2);

		// HCLK = SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		  // PCLK2 = HCLK
		  RCC_PCLK2Config(RCC_HCLK_Div1);

		  // PCLK1 = HCLK/2
		  RCC_PCLK1Config(RCC_HCLK_Div2);

		  // PLLCLK = 8Hz *  = 72 MHz
		  RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_4);

		  // Wlacz PLL
		  RCC_PLLCmd(ENABLE);
		  // Czekaj az PLL poprawnie sie uruchomi
		  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		  // PLL bedzie zrodlem sygnalu zegarowego


		  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		  // Czekaj az PLL bedzie sygnalem zegarowym systemu
		  while(RCC_GetSYSCLKSource() != 0x08);
	  }

}

void set_SupplyVoltage(volatile float MaxVoltage)
{
	float ADC_MaxVoltage = MaxVoltage/4.42;
	float ADC_MinVoltage = 1.54; //maxvoltage 8,4

	float ADC_Diffrence = (ADC_MaxVoltage - ADC_MinVoltage)*0.2;
	float x4_5 = ADC_MaxVoltage - ADC_Diffrence;
	float x3_5 = x4_5 - ADC_Diffrence;
	float x2_5 = x3_5 - ADC_Diffrence;
	float x1_5 = x2_5 - ADC_Diffrence;
	float xCritical = x1_5 - ADC_Diffrence;

	Batt_4_5_value = x4_5*256/3.3;
	Batt_3_5_value = x3_5*256/3.3;
	Batt_2_5_value = x2_5*256/3.3;
	Batt_1_5_value = x1_5*256/3.3;
	Batt_critical_value = xCritical*256/3.3;
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

void init_Servo()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //enable clock on serwo port

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit (& GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  SERWO1 | SERWO2 | SERWO3 | SERWO4 | SERWO5 | SERWO6| SERWO7 | SERWO8 | SERWO9 | SERWO10 | SERWO11 | SERWO12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void init_ADC()
{
	set_SupplyVoltage(8.3);

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

void delay_ms(volatile int LocalCounter)
{
	LocalCounter*=6000;
	while(LocalCounter--);
}

void delay_us(volatile int LocalCounter)
{
	while(LocalCounter--);
}


#endif /* INIT_H_ */
