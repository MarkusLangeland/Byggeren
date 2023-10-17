#include "mcp2515.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include "stdint.h"
#include "SPI_COM_Driver.h"

bool mcp2515_init(){

	SPI_init();
	mcp2515_reset();
	
	uint8_t value = mcp2515_read(MCP_CANSTAT);
	
	
	if((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset!\n");
		return true;
	}
	
	return false;
}

uint8_t mcp2515_read(uint8_t address){
	
	SS_off();
	SS_on(); //Lowering CS pin
	
	SPI_write(MCP_READ); //Read instruction from the SPI instruction set 
	SPI_write(address); //Entering the address 
	uint8_t data = SPI_read();  //retrieving the data from address	
	SS_off();

		
	return data; 
}

void mcp2515_write(uint8_t address, uint8_t data){
	
	SS_off();
	SS_on(); //Lowering CS pin
	
	SPI_write(MCP_WRITE); //Write instruction from the SPI instruction set 
	SPI_write(address); 
	SPI_write(data); 
	
	SS_off();
	
}

void mcp2515_reset(void){
	SS_off();
	SS_on(); //Lowering the CS pin
	
	
	SPI_write(MCP_RESET); 
	
	SS_off(); //Raising the CS pin
}

void mcp2515_request_to_send(void){
	
	SS_off();
	SS_on(); //Lowering CS pin
	
	SPI_write(MCP_RTS_TX0);//litt usikker på denne
	
	SS_off(); //Raising CS pin
}

uint8_t mcp2515_read_status(void){
	
	SS_off();
	SS_on(); //Lowering CS pin

	SPI_write(MCP_READ_STATUS); 
	uint8_t status = SPI_read(); 
	
	SS_off(); //Raising CS pin
	
	return status; 
}


void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	
SS_off();
SS_on();
	
	SPI_write(MCP_BITMOD); 
	SPI_write(address);
	SPI_write(mask);
	SPI_write(data);
	
	SS_off(); //Raising CS pin

}
