#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "uart.h"

#define IO_OUTPUT 1
#define BAUD 9600
#define UBRR F_CPU / 16 / BAUD - 1

// lage firkantsignal
int main(void)
{
	DDRA |= (IO_OUTPUT << PINA);

	uart_init(UBRR);
	uart_transmit('D');

	/* Replace with your application code */
	while (true)
	{

		PORTA |= (1 << PINA0);
		_delay_ms(100);
		PORTA &= (0 << PINA0);
		_delay_ms(100);


	}
}
