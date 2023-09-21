#pragma once

void uart_init( unsigned int ubrr );
void uart_transmit( unsigned char data );
unsigned char uart_receiver( void );
void uart_print( void);
void uart_tester(void);
