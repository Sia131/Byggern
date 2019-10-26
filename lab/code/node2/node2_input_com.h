#ifndef NODE2_INPUT_H
#define NODE2_INPUT_H
#include "node2_CAN.h"


typedef struct USER_DATA{
    uint8_t x_analog;
    uint8_t y_analog;
    uint8_t left_analog;
    uint8_t right_analog;
    uint8_t joystick_button;

}USER_DATA;

void put_can_message_into_user_data(MESSAGE *can_message, USER_DATA *user_data);

void input_com_receive_data( USER_DATA *user_data);


#endif
