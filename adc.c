#include "adc.h"


void adc_init() {
	
	ADC->ADC_MR = ADC_MR_FREERUN;// continouos measure in this mode 
	ADC-> ADC_CHER = ADC_CHER_CH0;  //enabling the channel we are gonna use 
	
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_ADC << PMC_PCR_PID_Pos); //Manage clocking 
	PMC->PMC_PCER1 |= 1 << (ID_ADC - 32); 
	
	ADC->ADC_CR = ADC_CR_START; 
}

uint16_t adc_read(){
	uint16_t value = ADC-> ADC_CDR[0];
	return value; 
}


