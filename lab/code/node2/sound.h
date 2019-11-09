
#include <avr/io.h>
#include <avr/interrupt.h>
#include "node2_USART.h"

#ifndef SOUND_H_
#define SOUND_H_

void music_delay(uint16_t delay);

void sound_init();

void sound_set_tone(float freq);

//void sound_play_xp();


#endif