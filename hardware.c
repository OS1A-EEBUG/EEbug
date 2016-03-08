#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "bug.h"

static volatile uint8_t _left_duty_cycle, _right_duty_cycle;
static volatile uint8_t _isr_duty_count = 0;

inline void adc_init()
{
	// Use 1.1V reference
	// clear other two relevant pins
	ADMUX &= ~0x20;
	// and set the one we want.
	ADMUX |= 1 << 7;
}

__attribute__((flatten)) void _adc_block_until_conversion()
{
	// hardware will set this to zero
	// at some point. Wait until it does.
	while (ADCSRA & 1 << 6);
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
	ret = (ADCH & 3) << 8 | ADCL;

	// clean-up time; disable the ADC and remap ADMUX to nonsense
	ADCSRA &= ~(1 << 7);
	ADMUX &= ~3;
	return ret;
}

ISR(TIMER0_OVF_vect) {

	_isr_duty_count++;
	// _isr_duty_count %= 128
	_isr_duty_count &= DUTY_CYCLE_MASK;

	if (_isr_duty_count < _left_duty_cycle) PORTB |= 1 << PIN_L_MOTOR;
	else PORTB &= ~(1 << PIN_L_MOTOR);
	if (_isr_duty_count < _right_duty_cycle) PORTB |= 1 << PIN_R_MOTOR;
	else PORTB &= ~(1 << PIN_R_MOTOR);

}

void pwm_init(void)
{
	cli();
	// turn off the timer while we're doing shit.
	GTCCR |= 1 << 7;
	// disconnect compare/match output registers
	// and ensure no fuckery w/r/t waveforms
	TCCR0A = 0x00;
	// no prescaling on the clock
	// (i.e. we get system clock output, not a scaled version)
	TCCR0B = 0x01;
	
	// interrupt on timer overflow
	TIMSK |= 2;
	// no interrupts on compare
	// (could change later if we need it faster)
	TIMSK &= ~(1<<4 | 1<<3);
	sei();
}

inline void pwm_set(uint8_t pin, uint8_t duty_cycle)
{
	switch (pin) {
		case PIN_R_MOTOR:
			_right_duty_cycle = duty_cycle & DUTY_CYCLE_MASK;
			break;
		case PIN_L_MOTOR:
			_left_duty_cycle = duty_cycle & DUTY_CYCLE_MASK;
			break;
	}
}
