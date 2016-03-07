#include <avr/io.h>
#include <stdint.h>
#include "bug.h"

void adc_init()
{
	// Use 1.1V reference
	// clear other two relevant pins
	ADMUX &= ~0x20;
	// and set the one we want.
	ADMUX |= 1 << 7;
}

void _adc_block_until_conversion()
{
	// hardware will set this to zero
	// at some point. Wait until it does.
	while (ADCSRA & 1 << 6);
	return;
}

uint16_t adc_read(uint8_t pin)
{
	int ret;
	// set ADMUX so we read in the right pin
	switch (pin) {
		case PIN_R_LIGHT:
			ADMUX |= 1;
			break;
		case PIN_L_LIGHT:
			ADMUX |= 3;
			break;
	}

	// enable the ADC
	ADCSRA |= 1 << 7;
	// start the conversion
	ADCSRA |= 1 << 6;
	_adc_block_until_conversion();
	ret = (ADCH & 3) | ADCL;
	
	// clean-up time; disable the ADC and remap ADMUX to nonsense
	ADCSRA &= ~(1 << 7);
	ADMUX &= ~3;
	return ret;
}
