#include "mcp2515.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include "stdint.h"
#include "SPI_COM_Driver.h"

uint8_t read(uint8_t address){
	
	PORTB &= ~(1 << PB4); //Lowering the CS pin 
	
	SPI_write(0x03); //Read instruction from the SPI instruction set 
	SPI_write(address); //Entering the address 
	uint8_t data = SPI_read();  //retrieving the data from address	
	PORTB |= (1 << PB4); //Raising the CS pin  
		
	return data; 
}

void write(uint8_t address, uint8_t data){
	
	PORTB &= ~(1 << PB4); //Lowering the CS pin 
	
	SPI_write(0x02); //Write instruction from the SPI instruction set 
	SPI_write(address); 
	SPI_write(data); 
	
	PORTB |= (1 << PB4); 
}

