#ifndef BUG_H
#define BUG_H

#include <avr/io.h>
#include <stdint.h>

#define PIN_R_LIGHT PB2 // pin 7: ADC 1
#define PIN_R_MOTOR PB1 // pin 6
#define PIN_L_LIGHT PB3 // pin 2: ADC 3
#define PIN_L_MOTOR PB4 // pin 3

#define DUTY_CYCLE_MASK 0x7F // 0..128

extern void adc_init();
extern uint16_t adc_read(uint8_t);

extern void pwm_init(void);
extern void pwm_set(uint8_t, uint8_t);

#endif // !defined BUG_H
