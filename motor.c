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
	
	PIOD->PIO_PER |= (MOTOR_EN | MOTOR_DIR | MOTOR_SEL | MOTOR_NOT_RST | MOTOR_NOT_OE); //Configuring Enable register
	PIOD->PIO_OER |= (MOTOR_EN | MOTOR_DIR | MOTOR_SEL | MOTOR_NOT_RST | MOTOR_NOT_OE); //Configuring output enable register	
	
	PIOC->PIO_PER |= 0b111111110;
	PIOC->PIO_OER |= 0b111111110;
}

uint16_t motor_encoder(){
	
	PIOD->PIO_CODR = (MOTOR_NOT_OE); //Setting output enable low 
	PIOD->PIO_CODR = (MOTOR_SEL); //Setting Select low
	
	//add 20 ms delay
	
	PIOD->PIO_CODR = (MOTOR_NOT_RST); //maybe have a reset here?  
	PIOD->PIO_SODR = (MOTOR_NOT_RST); //maybe have a reset here? 
	
	uint8_t high_byte = (PIOD->PIO_PDSR & 0b01111111); 
	
	PIOD->PIO_SODR = (MOTOR_SEL); 
	
	//add 20 ms delay
		
	uint8_t low_byte = (PIOD->PIO_PDSR & 0b01111111); 
	
	PIOD->PIO_SODR = (MOTOR_NOT_OE); 
	
	
	uint16_t encoder_value = (high_byte << 8) | low_byte; 
	
	return encoder_value; 
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
