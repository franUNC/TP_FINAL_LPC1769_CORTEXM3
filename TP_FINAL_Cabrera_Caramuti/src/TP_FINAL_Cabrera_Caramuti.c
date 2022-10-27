/*
===============================================================================
 Name        : TP_FINAL_Cabrera_Caramuti.c
 Author      : FranCabrera, IvoCaramuti
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "stdio.h"
#include "LPC17xx.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#include "initialconfig.h"
#include "loadcell.h"
#include "macros.h"


uint16_t weight = 0;
uint16_t array[NUMSAMPLES];
uint16_t tare = 0;
uint8_t level = 7;

void sendData(void);
void finish(void);

int main(void) {

	initialConfigurations();

	for(int i=0; i<NUMSAMPLES; i++)
		array[i] = 0;

    while(1) {
    	if((weight-tare) > 910)
    		finish();
    	if(4*weight < tare)
    		stop(&tare);
    }
    return 0 ;

}

/*
 * START
 * Abrir el servo y empezar a cargar. Ir controlando la apertura del servo en función del peso actual y el peso final
 */
void EINT0_IRQHandler(void){
	start(tare);
	LPC_SC->EXTINT |= (START_LED);
}

/*
 * STOP
 *
 */
void EINT1_IRQHandler(void){
	stop(&tare);
	TIM_Cmd(LPC_TIM0, ENABLE);
	weight = 0;
	LPC_SC->EXTINT |= (STOP_LED);
}

/*
 * TARE
 */
void EINT2_IRQHandler(void){
	tare = getTare(weight);
	LPC_SC->EXTINT |= (TARE_LED);
}

uint8_t counter = 0;
void ADC_IRQHandler(void){

	array[counter] = getWeight();
	uint32_t average = 0;
	for(int i=0; i<NUMSAMPLES; i++)
		average+=array[i];
	counter++;
	if(counter == NUMSAMPLES)
		counter = 0;
	weight = average>>2;
	sendData();

}

void sendData(void){
	char weightToSend[6];
	sprintf(weightToSend,"W%4d\n",weight);
	UART_Send(LPC_UART1, (uint8_t*)weightToSend, sizeof(weightToSend), BLOCKING);
	char tareToSend[6];
	sprintf(tareToSend,"T%4d\n",tare);
	UART_Send(LPC_UART1, (uint8_t*)tareToSend, sizeof(tareToSend), BLOCKING);
	char levelToSend[6];
	sprintf(levelToSend,"L%4d\n",level);
	UART_Send(LPC_UART1, (uint8_t*)levelToSend, sizeof(levelToSend), BLOCKING);
}

/*
 * CERRAR SERVO
 */
void finish(void){
	TIM_Cmd(LPC_TIM0, DISABLE);
	while(tare!=0){

	}
}


