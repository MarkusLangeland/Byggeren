#include "can_config.h"
#include "mcp2515.h"

// void can_config_setup(void){ //This has been initialized in can_init func (CAN BE REMOVED)
// 	
// 	uint8_t bit_time = 	sync + proqSeg + ps1 + ps2;
// 	uint8_t BRP = 16;  
// 	
// 	mcp2515_write(MCP_CNF1, (BRP-1));	
// 	mcp2515_write(MCP_CNF2, (((ps1-1) >> 3) | (proqSeg-1)));
// 	mcp2515_write(MCP_CNF3, (ps2-1));
// }
// 
