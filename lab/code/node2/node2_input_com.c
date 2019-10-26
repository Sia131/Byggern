#include "node2_input_com.h"



void put_can_message_into_user_data(MESSAGE *can_message, USER_DATA *user_data){
    user_data->x_analog             = can_message->data[0];
    user_data->y_analog             = can_message->data[1];
    user_data->left_analog          = can_message->data[2];
    user_data->right_analog         = can_message->data[3];
    user_data->joystick_button      = can_message->data[4];
}

void input_com_receive_data(USER_DATA *user_data){
    MESSAGE can_message;
    can_receive(&can_message);
    put_can_message_into_user_data(&can_message, user_data);
}
