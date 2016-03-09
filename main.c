#define F_CPU 4e6
#include <avr/io.h>
#include <bug.h>
#include <stdint.h>
#include <util/delay.h>

void follow_line()
{
	// TODO	
}

void spiral()
{
	// TODO
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
