#ifndef NODE1_BUTTONS_H
#define NODE1_BUTTONS_H

#include "node1_memory_map.h"

#define JOYSTICK_BTN        PB0
#define SLIDER_LEFT_BTN     PB1
#define SLIDER_RIGHT_BTN    PB2


typedef struct BUTTONS{
    uint8_t joystick_button;
    uint8_t slider_left_button;
    uint8_t slider_right_button;
}BUTTONS;

void buttons_init();

void get_buttons(BUTTONS *button);

#endif





