#include "mcp2515.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include "stdint.h"
#include "SPI_COM_Driver.h"

uint8_t mcp2515_init(){
	uint8_t value; 
	SPI_init();
	mcp2515_reset(); 
	
	value = mcp2515_read(MCP_CANSTAT); 
	
	if((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset!\n"); 
		return 1; 
	} 
	
	return 0; 
}

uint8_t mcp2515_read(uint8_t address){
	
	PORTB &= ~(1 << PB4); //Lowering the CS pin 
	
	SPI_write(0x03); //Read instruction from the SPI instruction set 
	SPI_write(address); //Entering the address 
	uint8_t data = SPI_read();  //retrieving the data from address	
	PORTB |= (1 << PB4); //Raising the CS pin  
		
	return data; 
}

void mcp2515_write(uint8_t address, uint8_t data){
	
	PORTB &= ~(1 << PB4); //Lowering the CS pin 
	
	SPI_write(0x02); //Write instruction from the SPI instruction set 
	SPI_write(address); 
	SPI_write(data); 
	
	PORTB |= (1 << PB4); //Raising the CS pin
}

void mcp2515_reset(void){
	PORTB &= ~(1 << PB4); //Lowering the CS pin
	
	SPI_write(MCP_RESET); 
	
	PORTB |= (1 << PB4); //Raising the CS pin
}

void mcp2515_request_to_send(void){
	PORTB &= ~(1 << PB4); //Lowering the CS pin
	
	SPI_write(MCP_RTS_TX0);
	
	PORTB |= (1 << PB4); //Raising the CS pin
}

uint8_t mcp2515_read_status(void){
	
	PORTB &= ~(1 << PB4); //Lowering the CS pin

	SPI_write(MCP_READ_STATUS); 
	uint8_t read_status = SPI_read(); 
	
	PORTB |= (1 << PB4); //Raising the CS pin
	
	return read_status; 
}


void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	
	PORTB |= (1 << PB4); //Raising the CS pin
	PORTB &= ~(1 << PB4); //Lowering the CS pin
	
	SPI_write(MCP_BITMOD); 
	SPI_write(address);
	SPI_write(mask);
	SPI_write(data);

	
	PORTB |= (1 << PB4); //Raising the CS pin

}
