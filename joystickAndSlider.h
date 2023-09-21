/*
 * IncFile1.h
 *
 * Created: 19.09.2023 18:18:26
 *  Author: nissantk
 */ 
#pragma once
#include <stdio.h>
#ifndef INCFILE1_H_
#define INCFILE1_H_

#define Offset 25
#define Treshold 8

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL,
	} Direction;


typedef struct {
	int8_t JoyX;
	int8_t JoyY;
	uint8_t rightSlider;
	uint8_t leftSlider;
	} userInput;

userInput getUserInput(uint8_t* adc);

Direction getDirection(uint8_t* adc);


#endif /* INCFILE1_H_ */
