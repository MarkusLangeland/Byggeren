#include "motor.h"

#define MOTOR_EN PIO_PD9
#define MOTOR_DIR PIO_PD10
#define MOTOR_SEL PIO_PD2
#define MOTOR_NOT_OE PIO_PD0
#define MOTOR_NOT_RST PIO_PD1

#define ENCODER_D01 PIO_PC1
#define ENCODER_D02 PIO_PC2
#define ENCODER_D03 PIO_PC3
#define ENCODER_D04 PIO_PC4
#define ENCODER_D05 PIO_PC5
#define ENCODER_D06 PIO_PC6
#define ENCODER_D07 PIO_PC7

void motor_init(){
	//dac_init(); 
	//PMC->PMC_PCR = (1 << 28) + (1 << 12) + 13;
	
	PIOD->PIO_PER |= (MOTOR_EN | MOTOR_DIR | MOTOR_SEL | MOTOR_NOT_RST | MOTOR_NOT_OE); //Configuring Enable register
	PIOD->PIO_OER |= (MOTOR_EN | MOTOR_DIR | MOTOR_SEL | MOTOR_NOT_RST | MOTOR_NOT_OE); //Configuring output enable register	
	
	//PIOC->PIO_WPMR = ('P' << 24) + ('I' << 16) + ('O' << 8) + 0;
	 
	PIOC->PIO_PER |= 0b111111110;
	PIOC->PIO_ODR |= 0b111111110;
	
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER0 |= 1 << (ID_PIOC);
	
}

#define ENCODER_DATA_MASK (0xFF << 1)
#define DO0_IDX 1 

int16_t motor_encoder(){
	
	PIOD->PIO_CODR |= (MOTOR_NOT_OE); //Setting output enable low 
	PIOD->PIO_CODR |= (MOTOR_SEL); //Setting Select low
	
	delay_us(50);
	//add 20 ms delay
	
	//PIOD->PIO_CODR = (MOTOR_NOT_RST); //maybe have a reset here?  
	//PIOD->PIO_SODR = (MOTOR_NOT_RST); //maybe have a reset here? 
	
	uint16_t high_byte = (PIOC->PIO_PDSR & 0b111111110) >> 1; 
	
	PIOD->PIO_SODR = (MOTOR_SEL); 
	
	delay_us(50); 
	//add 20 ms delay
		
	uint16_t low_byte = (PIOC->PIO_PDSR & 0b111111110) >> 1; 
	
		
	PIOD->PIO_CODR = (MOTOR_NOT_RST); //maybe have a reset here?
	PIOD->PIO_SODR = (MOTOR_NOT_RST); //maybe have a reset here?
		
	PIOD->PIO_SODR = (MOTOR_NOT_OE); 
	
	
	uint16_t encoder_value = (high_byte << 8) | low_byte; 
	
	int16_t signed_value = *(int16_t *)&encoder_value; 
	
	return (int)signed_value/14.0; 
}

void motor_speed(uint16_t value) {
	dac_write(value); 
}

void motor_enable(int state){
	//PIOD->PIO_PER = (MOTOR_EN);
	//PIOD->PIO_OER = (MOTOR_EN);
	switch (state) {
		case 0:
			PIOD->PIO_CODR = (MOTOR_EN);
			break;
		case 1:
			PIOD->PIO_SODR = (MOTOR_EN);
			break;
	}	
}

void motor_direction(direction data) {
	switch(data){
		case RIGHT: 
			PIOD->PIO_SODR = (MOTOR_DIR); 
			break;
		case LEFT: 
			PIOD->PIO_CODR = (MOTOR_DIR);  
			break;
	}
}


void init2() {
	PIOD->PIO_PER |= (MOTOR_EN);
	PIOD->PIO_OER |= (MOTOR_EN);
	PIOD->PIO_SODR = (MOTOR_EN);
	
	PIOD->PIO_PER |= (MOTOR_DIR);
	PIOD->PIO_OER |= (MOTOR_DIR);
}


//void testcase(direction dir){
	//switch(dir) {
		//case LEFT:
			//PIOD->PIO_CODR = (MOTOR_DIR);
			//break;
		//case RIGHT:
			//PIOD->PIO_SODR = (MOTOR_DIR);
			//break;
	//}
//}
