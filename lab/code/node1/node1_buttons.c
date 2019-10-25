#include "node1_buttons.h"
#include <avr/io.h>



void buttons_init(){
    DDRB &= ~(1 << JOYSTICK_BTN);
    DDRB &= ~(1 << SLIDER_LEFT_BTN);
    DDRB &= ~(1 << SLIDER_RIGHT_BTN);
}

void get_buttons(BUTTONS *button){
    button->joystick_button = (PINB & 0b00000001);
    button->slider_left_button = ((PINB & 0b00000010) >> 1);
    button-> slider_right_button = ((PINB & 0b00000100) >> 2);
}



