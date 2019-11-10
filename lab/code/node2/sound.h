
#include <avr/io.h>
#include <avr/interrupt.h>
#include "node2_USART.h"

#ifndef SOUND_H_
#define SOUND_H_

void sound_init();

void sound_set_tone(float freq);



#endif