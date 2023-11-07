#include "delaycall.h" 

#define IRQ_SysTick_priority 0 
#define F_CPU 84000000

volatile uint32_t wait_ticks = 0; 

static void SysTick_init_us(int period) {
	// set SysTick reload value
	SysTick->LOAD = ((int)(period*84) & SysTick_LOAD_RELOAD_Msk)-1;

	// reset SysTick counter value
	SysTick->VAL = 0;

	// set SysTick interrupt priority
	NVIC_SetPriority(SysTick_IRQn, IRQ_SysTick_priority);

	// set SysTick timer to MCK, enable interrupt and timer
	SysTick->CTRL  = (1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;
}

void _delay_ms(uint32_t ms){
	// Load the SysTick counter value
	uint32_t count = ms * (SystemCoreClock / 1000);

	// Time the duration the SysTick counter counts down from the reload value to zero
	uint32_t startTick = SysTick->VAL;
	uint32_t ticks = 0;
	
	while(ticks < count){
		uint32_t currentTick = SysTick->VAL;
		
		// Check for the case where the SysTick has wrapped around
		if(currentTick <= startTick){
			ticks += startTick - currentTick;
			} else {
			// Handle the wrap-around by adding the difference from currentTick to the reload value
			ticks += startTick + (SysTick->LOAD - currentTick) + 1;
		}
		
		startTick = currentTick;
	}
}
