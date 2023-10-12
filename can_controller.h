#pragma once 

#include "stdint.h"
#include "SPI_COM_Driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint16_t ID;
	uint8_t length;
	char data[8];
} message_type;


void can_init(uint8_t mode); 
void can_send(message_type* message); 
int can_recieve(message_type* message); 




