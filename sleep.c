#include "sleep.h" 

void delay_us(int us) {
	for(int i = 0; i < 5*us; i++) {
		__asm__("nop");
	}
}