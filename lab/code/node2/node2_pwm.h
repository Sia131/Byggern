#ifndef NODE2_PWM_H
#define NODE2_PWM_H
#include <avr/io.h>
#include <avr/interrupt.h>

static unsigned int pwm_period = 0x9C40; //40.000

void pwm_init();

void pwm_set_angle(double angle);

void pwm_set_ms(double ms);


#endif