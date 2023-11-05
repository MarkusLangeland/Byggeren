#pragma once 

#include "stdint.h"
#include "spi_com_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

enum MODES {
	NORMAL, 
	SLEEP,
	LOOPBACK,
	LISTENONLY,
	CONFIG,
};

typedef struct {
	uint16_t ID;
	uint8_t length;
	char data[8];
} message_type;


void can_init(); 
void can_send(message_type* message); 
void can_recieve(message_type* message); 
bool can_has_message();



