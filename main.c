#include "sam.h"
#include "stdint.h"
#include "can_config.h"
#include "pwm.h"
#include "adc.h"
#include "motor.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "delaycall.h"

#define LED1 PIO_PA19
#define LED2 PIO_PA20


int score = 0;


void led(){
	PIOA->PIO_PER |= (LED1 | LED2); 
	PIOA->PIO_OER |= (LED1 | LED2); 
	PIOA->PIO_SODR |= (LED1 | LED2);
}

int main(void)
{
	//configure_uart();
	//SystemInit();
	//
	//
	//pwm_init();
	//pwm_set_servo_position(LEFT);
	//
    /* Initialize the SAM system */
	configure_uart();
    
	SystemInit();
	led();

	uint32_t can_br = 0;
	can_br |= (ps2 - 1) | ((ps1-1) << 4) | ((proqSeg - 1) << 8) | ((brp_node2 - 1) << 16);
	can_init_def_tx_rx_mb(can_br);
	
	CAN_MESSAGE message;
	
	pwm_init();
	int freq = 84000000; 
	adc_init();  
	
	//motor_init(); 	
	//motor_enable(true);
	//motor_direction(RIGHT);
	
	//init2();
	motor_init();
	motor_enable(1);
	dac_init();
	//dac_write(1500);
	
	int i = 0; 
    while (true) 
    {
		//run(&message);
		//pwm_set_frequency(freq, 5);
		
		//loose_game(); 
		//testcase(RIGHT);
		//motor_enable(0);
		//motor_direction(LEFT);
		
		i = i+1; 
		printf("hello %d", i);
		printf("\n\r");
		delay_sec(1);
    }
	
}

void delay_sec(int sec) {
	for(int i = 0; i < 1000*sec; i++) {
		printf(i);
	}
}


void count_score() {
	score++;
}

void lose_game(){
	uint16_t value = adc_read(); 
	
	if ((value < 1500) && (value != 0)){
		printf("You lost! \n\r");
	}
}


typedef struct {
	uint16_t ID;
	uint8_t length;
	char data[8];
} message_type;

//Funker ikke:
//void send_score_to_node1(int score) {
	//volatile uint8_t* node2 = (uint8_t*)0x13ff;
	//message_type msg = {111, 8, {0,0,0,0,0,0}};
	//can_send(&msg, 1);
//}


void run(CAN_MESSAGE * message) {
	uint8_t has_message = can_receive(message, 0);
	
	if (!has_message) {
		for (int i = 0; i < message->data_length; i++)
		{
			printf("%d ", message->data[i]);
		}
		printf("\n\r");
		
		float test = (float)((message->data[2]) / 10000.0);
		test = roundf(test*400)/40;
		
		pwm_set_duty_cycle(test);
		
		
		int TRESHOLD_HORISONTAL = 15;
		int horisontal = message->data[0];
		//int vertical = can_msg->data[4];
		
		if (horisontal < -TRESHOLD_HORISONTAL) {
			
			printf("LEFT!");
			dac_write(1700);
			if (horisontal < -95) {
				dac_write(2500);
			}
			motor_direction(LEFT);
			} else if(horisontal > TRESHOLD_HORISONTAL) {
			
			printf("RIGHT");
			dac_write(1700);
			if (horisontal > 95) {
				dac_write(2500);
			}
			motor_direction(RIGHT);
			} else{
			dac_write(0);
		}
		
		
		
	}
	
}