#ifndef NODE2_SOLENOID_H
#define NODE2_SOLENOID_H

#include "node2_USART.h"
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>



void solenoid_deactivate();

void solenoid_activate();

void solenoid_init();

void solenoid_shoot();

int solenoid_get_shot();

void solenoid_clear_shot();

void solenoid_update_shot(uint8_t value);




#endif