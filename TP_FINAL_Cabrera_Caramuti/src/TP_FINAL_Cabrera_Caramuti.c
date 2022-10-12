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
#include "loadcell.h"
#include "macros.h"


uint16_t weight = 0;
uint16_t tare = 0;

int main(void) {

	initialConfigurations();


    while(1) {
    	if((weight-tare) > 1000 || (2*weight < tare))//Ver esta condición cuando la tara es relativamente alta respecto a la minima
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
 * Cerrar el servo y bajar la tara
 */
void EINT1_IRQHandler(void){
	stop(&tare);
	LPC_SC->EXTINT |= (STOP_LED);
}

/*
 * TARE
 */
void EINT2_IRQHandler(void){
	tare = getTare(weight);
	LPC_SC->EXTINT |= (TARE_LED);
}


void ADC_IRQHandler(void){
	weight = getWeight();
}

