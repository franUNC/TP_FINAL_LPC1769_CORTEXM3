#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"
#include "initialconfig.h"
#include "lpc17xx_uart.h"
#include "macros.h"


static void configEINT(void);
static void configPIN(void);
static void configADC(void);
static void configTIMER(void);
static void configUART(void);

int initialConfigurations(void){

	configEINT();
	configPIN();
	configADC();
	configTIMER();
	configUART();

	return 0;
}

static void configEINT(void){
	LPC_PINCON->PINSEL4 = 0x00;
	LPC_PINCON->PINSEL4 |= ((1 << 20));
	LPC_PINCON->PINSEL4 |= ((1 << 22));
	LPC_PINCON->PINSEL4 |= ((1 << 24));
	LPC_GPIO2->FIODIR1 |= (7<<2);
	LPC_SC->EXTMODE |= (7);
	LPC_SC->EXTPOLAR &= ~(7);
	LPC_SC->EXTINT |= (7);
	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT2_IRQn);
}

static void configPIN(void){
	LPC_PINCON->PINSEL0 &= ~(7);
	LPC_PINCON->PINMODE0 |= (42);
	LPC_GPIO0->FIODIR0 |= (7);
}

static void configADC(void){
	LPC_PINCON->PINSEL1 |= (1<<14);
	LPC_PINCON->PINMODE1 |= (1<<15);

	ADC_Init(LPC_ADC, 100000);
	//ADC_BurstCmd(LPC_ADC, DISABLE);
	ADC_StartCmd(LPC_ADC, ADC_START_ON_MAT01);
	ADC_ChannelCmd(LPC_ADC, 0, ENABLE);
	ADC_EdgeStartConfig(LPC_ADC, 0);
	ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);
}

static void configTIMER(void){
	LPC_PINCON->PINSEL3 |= (15<<24);

	TIM_TIMERCFG_Type configTim;
	configTim.PrescaleOption = TIM_PRESCALE_TICKVAL;
	configTim.PrescaleValue = 999;

	TIM_MATCHCFG_Type configMatch;
	configMatch.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
	configMatch.IntOnMatch = DISABLE;
	configMatch.MatchChannel = 1;
	configMatch.MatchValue = 6000;
	configMatch.ResetOnMatch = ENABLE;
	configMatch.StopOnMatch = DISABLE;

	TIM_ConfigMatch(LPC_TIM0, &configMatch);
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &configTim);
	TIM_Cmd(LPC_TIM0, ENABLE);
	NVIC_EnableIRQ(TIMER0_IRQn);

}

static void configUART(void){
	LPC_PINCON->PINSEL4 |= 2;

	UART_CFG_Type configUART;
	configUART.Baud_rate = 9600;
	configUART.Databits = UART_DATABIT_8;
	configUART.Parity = UART_PARITY_NONE;
	configUART.Stopbits = UART_STOPBIT_1;

	UART_Init(LPC_UART1, &configUART);
	UART_TxCmd(LPC_UART1, ENABLE);
}
