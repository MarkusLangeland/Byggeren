#include "stdint.h"
#include "SPI_COM_Driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>

void SPI_init(void)
{
	//Set output MOSI, SCK
	DDRB |= (1<<PB5) | (1<<PB7) | (1<<PB4);
	
	//Set input MISO, RXD1, TXD1
	DDRB &= /*~(1 << PB2) & ~(1 << PB3) &*/ ~(1<<PB6);  
	
	//Set SPI, Master, set clock rate fck/16 
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0); 
	//Set SPI mode to 0 | ((CPOL || CPHA) && 0)
	
	//Forcing SS to be low when activated 
}

void SS_on(void){ //Slave select on
	PORTB &= ~(1 << PB4); 
}

void SS_off(void){ //Slave select off
	PORTB |= (1 << PB4);
}

uint8_t SPI_write(uint8_t cData){
	SPDR = cData;
	
	while(!(SPSR & (1<<SPIF)))
	{
	};  
	
	return SPDR;
}

uint8_t SPI_read(void) {
	SPI_write(0); 
	
	return SPDR;  
}

