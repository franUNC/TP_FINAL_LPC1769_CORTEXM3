/*
===============================================================================
 Name        : TP_FINAL_Cabrera_Caramuti.c
 Author      : FranCabrera, IvoCaramuti
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "LPC17xx.h"
#include "initialconfig.h"


int ADC0Value = 0;
int main(void) {

	initialConfigurations();


    while(1) {

    }
    return 0 ;

}

/*
 * START
 */
void EINT0_IRQHandler(void){
	LPC_GPIO0->FIOSET |= (START_LED);
	LPC_GPIO0->FIOCLR |= (STOP_LED);
	LPC_GPIO0->FIOCLR |= (TARE_LED);
	LPC_SC->EXTINT |= (START_LED);
}

/*
 * STOP
 */
void EINT1_IRQHandler(void){
	LPC_GPIO0->FIOCLR |= (START_LED);
	LPC_GPIO0->FIOSET |= (STOP_LED);
	LPC_GPIO0->FIOCLR |= (TARE_LED);
	LPC_SC->EXTINT |= (STOP_LED);
}

/*
 * TARE
 */
void EINT2_IRQHandler(void){
	LPC_GPIO0->FIOCLR |= (START_LED);
	LPC_GPIO0->FIOCLR |= (STOP_LED);
	LPC_GPIO0->FIOSET |= (TARE_LED);
	LPC_SC->EXTINT |= (TARE_LED);

}


void ADC_IRQHandler(void){
	ADC0Value = ((LPC_ADC->ADDR0)>>4) & 0xFFF;
	LPC_ADC->ADGDR &= LPC_ADC->ADGDR;
}

