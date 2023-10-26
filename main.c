#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "uart.h"
#include "xmem.h"
#include "sram.h"
#include "adc.h"
#include "stdint.h"
#include "joystickAndSlider.h"
#include "oled.h"
#include "font.h"
#include "SPI_COM_Driver.h"
#include "mcp2515.h"
#include "can_controller.h"
#include "menu.h"
#include "can_config.h"

#define IO_OUTPUT 1
#define BAUD 9600
#define UBRR 4915200UL / 16 / BAUD - 1 

int main(void)
{
	uart_init(UBRR);
	xmem_init(); 
	oled_init(); 
	printf("\n\r");
	can_init();
	
	
	volatile uint8_t* node2 = (uint8_t*)0x13ff;
	
	
	while(true){
		_delay_ms(3000);
		userInput input = getUserInput(node2);	
		message_type msg = {111, 8, {input.JoyX, 0, 0, 0, input.JoyY}};
		can_send(&msg);	
	}
	 	
	//menu_init();
	//testing loopback mode
// 	message_type message = {
// 		1365,
// 		8,
// 		{'a','b','n','m','k','s','g','f'}
// 	};
// 	
// 		while(true){
// 			
// 		
// 	/*	can_send(&message);*/
// 		
// 		message_type messageRecieved;	
// 		// 		while(!can_has_message()) {
// 		// 		}
// 		
// 				_delay_ms(100);
// 				
// 				can_recieve(&messageRecieved);
// 				printf("Received with ID %u of size %u: \n\r", messageRecieved.ID, messageRecieved.length);
// 				for (uint8_t i = 0; i < messageRecieved.length; i++) {
// 					printf("%c, ", messageRecieved.data[i]);
// 				}
// 				printf("\n\r");
// 				
// 		}
		
		while(true){
			 
		}
}

void printUART(uint8_t address) { 

	uint8_t value = mcp2515_read(address);
	
	// Print the value in binary representation
	for (int i = 7; i >= 0; i--) {
		printf("%u", (value >> i) & 1);
	}

	printf("\n\r");  // Move to the next line after printing the binary value
}