#pragma once
#include "stdint.h"
#include "sam.h"

void _delay_ms(uint32_t ms);
static void SysTick_Init_us(int period);

