/*
 * GccApplication2.c
 *
 * Created: 31.08.2023 15:51:52
 * Author : markuslf
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "uart.h"
#include <stdio.h>
#include "SRAM.h"


#define IO_OUTPUT 1
#define BAUD 9600
#define UBRR 4915200UL / 16 / BAUD - 1 

void xmem_init(void){
	MCUCR |= (1 << SRE); 
	SFIOR |= (1 << XMM2); 
	SFIOR |= (0 << (XMM1 && XMM0)); 
}

uint16_t BASE_ADDRESS = 0x0;


uint8_t xmem_read(uint16_t addr){
		
	volatile char *ext_mem = (char *) BASE_ADDRESS; 
	uint8_t ret_val=ext_mem[addr]; 
	return ret_val;  
}

void xmem_write(uint8_t data, uint16_t addr){
	volatile char *ext_mem = (char *) BASE_ADDRESS; 
	ext_mem[addr] = data; 
}

int main(void)
{
	
	//DDRA |= (IO_OUTPUT << PINA);
	//PORTA |= (1 << ); 
	//kommunisere med UART, øving 1
	uart_init(UBRR); 
	
	//initierer å kommunisere med external memory, som her er SRAM, øving 2
	xmem_init();
	
	//uint8_t dummy = xmem_read(0x1800);
	/*
	while (true)
	{
	
		//uint8_t dummy = xmem_read(0x1fff);  
		xmem_write(0xff, 0x1); 
	}
	*/
	//tester SRAM, øving 2, vellykket
	while (true )
	{
		SRAM_test();
	}
		
	/*
	while(true) {
		PINE1 |= (1 << 0); 
		
		if (PINE1 == 1) {
			PINE1 |= (0 << 0);
		}
		else {
			PINE1 |= (1 << 0);

		}
		
		_delay_ms(1000)
	}
	
	
	*/
	/*
	//printf("geu");
	
	uart_init(UBRR);
	
	
	//exercise 1, sjekker testfunksjonen til del1
	while (true) {
		uart_tester();
	}
	

    /* EXERCISE 1, sjekker pinsene + signal
	while (true) 
    {
		
		PORTA |= (1 << PINA0);
		_delay_ms(100);
		PORTA &= (0 << PINA0);
		_delay_ms(100);
		
		
    }*/

	
	//Exercise 2 
	

	
}
