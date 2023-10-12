#include "can_controller.h"
#include "mcp2515.h"
#include <util/delay.h>

void can_init(uint8_t mode){
	
	mcp2515_init(); 

	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, mode); 
	
	mcp2515_write(MCP_RXB0CTRL, MCP_RXM0 | MCP_RXM1); //rollover if we have overflow problems
}

void can_send(message_type* message){
	 mcp2515_write(MCP_TXB0SIDH, message->ID / 8);
	 mcp2515_write(MCP_TXB0SIDL, (message->ID % 8) << 5);
	 mcp2515_write(MCP_TXB0DLC, message->length);
	
	
	for (uint8_t i = 0; i < message->length; ++i) {
		mcp2515_write(MCP_TXB0D0 + i, message->data[i]); 
	}
	
	mcp2515_request_to_send(); 
}

int can_recieve(message_type* message){
	
	if (mcp2515_read(MCP_CANINTF) & MCP_RX1IF){
		message->ID = (mcp2515_read(MCP_RXB0SIDL) >> 5) + (mcp2515_read(MCP_RXB0SIDH) << 3); 
		
		message->data = mcp2515_read(MCP_RXB0DLC); 
		
		for (int i = 0; i < message->length; ++i){
			message->data[i] = mcp2515_read(MCP_RXB0D0 + i);
		}
	}
	
	else if (mcp2515_read(MCP_CANINTF) & MCP_RX1IF){
		message->ID = (mcp2515_read(MCP_RXB1SIDL) >> 5) + (mcp2515_read(MCP_RXB1SIDH) << 3);
			
		message->data = mcp2515_read(MCP_RXB1DLC);
		
		for (int i = 0; i < message->length; ++i){
			message->data[i] = mcp2515_read(MCP_RXB1D0 + i);
		}
	}
	else {
			return 1; 
		}
		
	return 0;
}

