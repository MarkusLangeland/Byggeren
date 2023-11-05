#include "sam.h"
#include "stdint.h"
#include "can_config.h"
#include "pwm.h"

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
    while (true) 
    {
			
			//pwm_set_frequency(freq, 5);
	
		uint8_t has_message = can_receive(&message, 0);
		pwm_set_duty_cycle((float)(message.data[0] + 100) / 200);


		if (!has_message) {
			for (int i = 0; i < message.data_length; i++)
			{
				printf("%d ", message.data[i]);
			}
			printf("\n\r");	
		}
    }
	
}

void count_score() {
	score++;
}



typedef struct {
	uint16_t ID;
	uint8_t length;
	char data[8];
} message_type;

//Funker ikke:
void send_score_to_node1(int score) {
	volatile uint8_t* node2 = (uint8_t*)0x13ff;
	while(true) {
		message_type msg = {111, 8, {0,0,0,0,0,0}};
		can_send(&msg);
	}
}
