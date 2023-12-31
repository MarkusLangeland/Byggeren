#include "can_controller.h"
#include "mcp2515.h"
#include "can_config.h"
#include <util/delay.h>


// void can_config_setup() {
// 	uint8_t bit_time = 	sync + proqSeg + ps1 + ps2;
// 	//uint16_t BRP = 
// }


void can_init(){
	//checks if we initialize
	while (mcp2515_init()){
	}
	printf("[mcp2515] initialized\n\r");
	
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, CONFIG<<5);
	
	//Config all the CNFx registers for the MCP2515
	uint8_t BRP = 4;
		
	mcp2515_write(MCP_CNF1, (BRP-1));
	mcp2515_write(MCP_CNF2, ((1 << 7) | ((ps1-1) << 3) | (proqSeg-1) ));
	//mcp2515_write(MCP_CNF3, (ps2-1));
	//mcp2515_write(MCP_CNF1, 3);
	//mcp2515_write(MCP_CNF2, (1 << 7) | (6 << 3));
	mcp2515_write(MCP_CNF3, 5);
	
	//set to mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, NORMAL<<5); 
	//printf("CAN control register: %u\n", mcp2515_read(MCP_CANCTRL));
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


bool can_has_message() {
	return mcp2515_read(MCP_CANINTF) & MCP_RX0IF || mcp2515_read(MCP_CANINTF) & MCP_RX1IF;
}

void can_recieve(message_type* message){
	if(message == NULL){
		// panic
	}
		if (mcp2515_read(MCP_CANINTF) & MCP_RX0IF){
			message->ID = (mcp2515_read(MCP_RXB0SIDL) >> 5) + (mcp2515_read(MCP_RXB0SIDH) << 3);
			
			message->length = mcp2515_read(MCP_RXB0DLC);
			
			for (int i = 0; i < message->length; ++i){
				message->data[i] = mcp2515_read(MCP_RXB0D0 + i);
			}
			return;
		}
		
		if (mcp2515_read(MCP_CANINTF) & MCP_RX1IF){
			message->ID = (mcp2515_read(MCP_RXB1SIDL) >> 5) + (mcp2515_read(MCP_RXB1SIDH) << 3);
			
			message->length = mcp2515_read(MCP_RXB1DLC);
			
			for (int i = 0; i < message->length; ++i){
				message->data[i] = mcp2515_read(MCP_RXB1D0 + i);
			}
			return;
		}
}

