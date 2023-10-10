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

#define IO_OUTPUT 1
#define BAUD 9600
#define UBRR 4915200UL / 16 / BAUD - 1 


int main(void)
{
	//DDRA |= (IO_OUTPUT << PINA);
	
	
	volatile uint8_t* adc = (uint8_t*)0x13ff;
	uart_init(UBRR);
	xmem_init(); 
	oled_init(); 
	SPI_init();
	
	while(true){
		SS_on();
		SPI_write('a');
		SS_off(); 
		
		printf("%d", SPI_read()); 
		//printf("hello world");
 	
	}
			
	//while (true) {
		//int userInput = main_menu(adc);
		//sub_menu(userInput, adc);	
	//}

	
// 	while (true)
// 	{
// 	//oled_write_data(); 
// 		//printf(".");
// 		//_delay_ms(10);
// 	}
	
	//_delay_ms(5000);
	//oled_screen_clear(); 
	// adc_init(); 
	
	
	//volatile uint8_t* adc = (uint8_t*)0x13ff;
	//while(true){
		//*adc = 69;
		//_delay_ms(100);
		//
		//
		//
		///*printf("%d ", "1");*/
		///*printf("%d ", adc_read(1));*/
		//getdirection(adc);
		//
//
		//
		//printf("\n\r");
	//}
}




//int main(void)
//{
	//xmem_init();
	//volatile uint8_t* adc = (uint8_t*)0x1400;
	//*adc = 69;
	//
	//while(true){
		////xmem_write(0x01, 0x1200);
		//xmem_read(0x1000);
	//}
		//
//}


int main_menu(uint8_t* adc) {
	int selected = 0;
	while (true) {
		Direction joyPos = getDirection(adc);
		switch (joyPos)
		{
			case DOWN:
			if (selected < 2) {
				selected = selected + 1;
			}
			_delay_ms(600);
			break;
			case UP:
			if (selected > 0) {
				selected = selected - 1;
			}
			_delay_ms(600);
			break;
			case RIGHT:
				return selected;
				break;
			
			case LEFT:
			break;
			default:
			printf("");
			break;
		}
		go_to_pos(0,0);
		oled_print_string("   Play");
		go_to_pos(1,0);
		oled_print_string("   Highscore");
		go_to_pos(2,0);
		oled_print_string("   Settings");
		switch(selected) {
			case 0:
			go_to_pos(0,0);
			oled_clear_line(0);
			oled_print_string("-> Play");
			break;
			case 1:
			go_to_pos(1,0);
			oled_clear_line(1);
			oled_print_string("-> Highscore");
			break;
			case 2:
			go_to_pos(2,0);
			oled_clear_line(2);
			oled_print_string("-> Settings");
			break;
			default:
			break;
		}
	}
	return -1;
}

void sub_menu(int userInput, uint8_t* adc) {
	switch (userInput) {
		case 0:
			oled_screen_clear();
			oled_print_string("Playing game");
			break;
		case 1:
			oled_screen_clear();
			go_to_pos(0,0);
			oled_print_string("High score: ");
			break;
		case 2:
			oled_screen_clear();
			go_to_pos(0,0);
			oled_print_string("Settings:");
			break;
	}
	while (true) {
		Direction joyPos = getDirection(adc);
		switch (joyPos)
		{
			case LEFT:
			oled_screen_clear();
			return;
			_delay_ms(600);
			break;
			//case UP:
			//if (selected > 0) {
				//selected = selected - 1;
			//}
			//_delay_ms(600);
			//break;
			//case RIGHT:
			//return selected;
			//break;
			//
			//case LEFT:
			//break;
			default:
			printf("");
			break;
		}
	}
}