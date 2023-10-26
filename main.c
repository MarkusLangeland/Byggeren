#include "sam.h"
#include "stdint.h"
#include "printf-stdarg.h"
#include "can_config.h"

#define LED1 PIO_PA19
#define LED2 PIO_PA20

void led(){
	PIOA->PIO_PER |= (LED1 | LED2); 
	PIOA->PIO_OER |= (LED1 | LED2); 
	PIOA->PIO_SODR |= (LED1 | LED2);
}

int main(void)
{
    /* Initialize the SAM system */
	
	configure_uart();
    
	SystemInit();
	led();

	uint32_t can_br = 0;
	can_br |= (ps2 - 1) | ((ps1-1) << 4) | ((proqSeg - 1) << 8) | ((brp_node2 - 1) << 16);
	can_init_def_tx_rx_mb(can_br);
	
	CAN_MESSAGE test;
	
    /* Replace with your application code */
    while (1) 
    {
		can_receive(&test, 2);
    }
}
