/*
 * CFile1.c
 *
 * Created: 19.09.2023 17:48:52
 *  Author: nissantk
 */ 
#include "joystickAndSlider.h"
#include "adc.h"
#include <stdio.h>



userInput getUserInput(uint8_t* adc) {
	int8_t x = (adc_read(0) - 128) / 1.28;
	if (x > Offset) {
		x -= Offset*(100-x)/(100-Offset);
	} else {
		x -= Offset*(-100-x)/(-100-Offset);
	}
	
	int8_t y = (adc_read(1)-128) / 1.28;		
	if (y > Offset) {
		y -= Offset*(100-y)/(100-Offset);
		} else {
		y -= Offset*(-100-y)/(-100-Offset);
	}
	
	uint8_t rightSlider = adc_read(2) /2.55;
	uint8_t leftSlider = adc_read(3)/2.55;

	userInput input = {y, x, rightSlider, leftSlider};			
	return input;
}

Direction getDirection(uint8_t* adc) {
	userInput input = getUserInput(adc);	
		//printf("%d ", input.JoyX);
		//printf("%d ", input.JoyY);
		
	if ((input.JoyY > Treshold && (abs(input.JoyX) < abs(input.JoyY))) ) {
		//printf("UP!");
		return UP;
		} else if ((input.JoyY < -Treshold) && (abs(input.JoyX) <= abs(input.JoyY))) {
		//printf("DOWN!");
		return DOWN;
		} else if (input.JoyX > Treshold && (abs(input.JoyX) >= abs(input.JoyY))) {
		//printf("RIGHT!");
		return RIGHT;
		} else if (input.JoyX < -Treshold && (abs(input.JoyX) > abs(input.JoyY))) {
		//printf("LEFT!");
		return LEFT;
		} else {
			//printf("CENTER!");
			return NEUTRAL;
		} 
	}; 
