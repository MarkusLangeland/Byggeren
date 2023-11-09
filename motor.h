#pragma once 
#include "sam.h"
#include "dac.h"
#include <stdbool.h>
#include "sleep.h"

typedef enum {
	RIGHT,
	LEFT
} direction;



void init2();
void motor_init();
void motor_direction(direction data);
void motor_speed(uint16_t value);
void motor_enable(int state);
void testcase(direction dir);
int16_t motor_encoder(); 
