#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>

#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= 1<<pin
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir, pin) portdir |= 1<<pin

int main(void)
{
	set_output(DDRB, PB1);
	while (1) {
		output_high(PORTB, PB1);
		_delay_ms(200);
		output_low(PORTB, PB1);
		_delay_ms(200);
	}
}

// hi, mom!
