#include "dac.h"

void dac_init() {
	
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_DACC << PMC_PCR_PID_Pos); 
	PMC->PMC_PCER1 |= 1 << (ID_DACC - 32); 
	
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1; //Selecting channel 1
	DACC->DACC_MR |= DACC_MR_WORD_HALF; //16 bit data
	DACC->DACC_MR |= DACC_MR_STARTUP_0; //SEts the startup time to 1024 clock cycles before starting conversion.
	
	DACC->DACC_CHER = DACC_CHER_CH1; //Enable channel 1 
}

void dac_write(uint16_t value) {
	DACC-> DACC_CDR = value; 
	
	bool isConversionComplete = DACC->DACC_ISR & DACC_ISR_EOC; 
	while (!(isConversionComplete));
}