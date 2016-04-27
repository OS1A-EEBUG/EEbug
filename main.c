#define F_CPU 4e6
#include <avr/io.h>
#include <bug.h>
#include <stdint.h>
#include <util/delay.h>

void follow_line()
{
	uint16 left, right;
	do {
		left = adc_read(PIN_L_LIGHT);
		right = adc_read(PIN_R_LIGHT);
		left = 1024 - left;
		right = 1024 - right;
		pwm_set(PIN_R_MOTOR, right >> 3);
		pwm_set(PIN_L_MOTOR, left  >> 3);
	} while (left > 256 && right > 256);
}

void spiral()
{
	uint8_t left = DUTY_CYCLE_MASK, right = DUTY_CYCLE_MASK;
	// full steam ahead :P
	pwm_set(PIN_R_MOTOR, right);
	pwm_set(PIN_L_MOTOR, left);
	for (int i = 0; i < 3; i++) _delay_ms(100);
	while (left > 10) {
		left -= 2;
		right -= 1;
		pwm_set(PIN_R_MOTOR, right);
		pwm_set(PIN_L_MOTOR, left);
		_delay_ms(20);
	}
	pwm_set(PIN_R_MOTOR, 0);
	pwm_set(PIN_L_MOTOR, 0);
}

int main()
{
	io_init();
	adc_init();
	pwm_init();
	follow_line();
	spiral();
	return 0;
}
