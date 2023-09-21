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

#define IO_OUTPUT 1
#define BAUD 9600
#define UBRR 4915200UL / 16 / BAUD - 1 


int main(void)
{
	//DDRA |= (IO_OUTPUT << PINA);
	
	
	
	uart_init(UBRR);

	xmem_init(); 
	// adc_init(); 
	volatile uint8_t* adc = (uint8_t*)0x1400;
	while(true){
		*adc = 69;
		_delay_ms(100);
		
		
		
		//printf("%d ", "1");
		//printf("%d ", adc_read(1));
		getDirection(adc);
		

		
		printf("\n\r");
	}
}






