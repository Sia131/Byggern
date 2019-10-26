#include "node1_buttons.h"
#include <avr/io.h>



void buttons_init(){
    DDRB &= ~(1 << JOYSTICK_BTN);
    DDRB &= ~(1 << SLIDER_LEFT_BTN);
    DDRB &= ~(1 << SLIDER_RIGHT_BTN);
}

void get_buttons(BUTTONS *button){
    buttons_init();
    button->joystick_button = (PINB & 0b00000001) >> JOYSTICK_BTN;
    button->slider_left_button = ((PINB & 0b00000010) >> SLIDER_LEFT_BTN);
    button->slider_right_button = ((PINB & 0b00000100) >> SLIDER_RIGHT_BTN);
}



