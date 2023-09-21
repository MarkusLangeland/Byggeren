#include <avr/io.h>
#include "adc.h"
#include <util/delay.h>

#define BASE_ADDRESS_ADC 0x1400
#define NUMBER_OF_CHANNELS 4
#define F_CPU 4915200UL

typedef enum{
	ADC_A0,
	ADC_A1,
	ADC_UNUSED,
	ADC_POWER_DOWN,
	ADC_INHIBIT_CONVERSION,
	ADC_BIPOLAR,
	ADC_DIFFERENTIAL,
	ADC_CONVERT_SINGLE
} adc_config_t;

static volatile unsigned char* const adc_base_address = (unsigned char*)0x1400;

void adc_init(void) {
	static const uint8_t shared_channel_config = (1<<ADC_CONVERT_SINGLE)|(1<<ADC_INHIBIT_CONVERSION);
	
	for(uint8_t channel = 0; channel < 4; channel++){
		adc_base_address[channel] = shared_channel_config | channel;
	}
	
	DDRD |= 1<<DDD4;
	
	OCR3AL = 0;
	ICR3L = 1;
	TCCR3A |= (1<<COM3A1);
	TCCR3B |= (1<<CS30);
	
	TCCR3A |= (1<<WGM31);
	TCCR3B |= (1<<WGM33) | (1<<WGM32);
	
	DDRE &= ~(1<<DDE0);
}

uint8_t adc_read(uint8_t channel){
	uint8_t* adc_data[4];
	adc_base_address[channel] = (1<<ADC_CONVERT_SINGLE) | channel;
	_delay_ms(20);
	//while(!(PINE & 1<<PINE0))
	//{
		//PINE;
	//}
	
	adc_data[0] = adc_base_address[0];
	adc_data[1] = adc_base_address[0];
	adc_data[2] = adc_base_address[0];
	adc_data[3] = adc_base_address[0];
	
	
	if (channel == 0) {
		return adc_data[0];
	} else if (channel == 1) {
		return adc_data[1];
	} else if (channel == 2) {
		return adc_data[2];
	} else if (channel == 3) {
		return adc_data[3];
	}
	else {
		return -1;
	}
}
