#ifndef NODE1_INPUT_COM_H
#define NODE1_INPUT_COM_H

#include "node1_buttons.h"
#include "node1_joystick.h"
#include "node1_slider.h"
#include "node1_CAN.h"


typedef struct USER_DATA{
    uint8_t x_analog;
    uint8_t y_analog;
    uint8_t left_analog;
    uint8_t right_analog;
    uint8_t joystick_button;

}USER_DATA;

void input_com_init();

/*put all that we need in node 2 to into USER_DATA */
void put_all_data_into_user_data(USER_DATA* user_data);

/*put all the data from USER_DATA into a CAN_MESSAGE*/
void put_user_data_into_can_message(MESSAGE *can_message, USER_DATA* user_data);


void input_com_send_data();


#endif
