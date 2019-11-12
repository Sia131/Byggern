#include "node1_input_com.h"


void put_all_data_into_user_data(USER_DATA* user_data){
    JOYSTICK joystick;
    get_joystick_values(&joystick);

    SLIDER slider;
    get_slider_position(&slider);

    BUTTONS buttons;
    get_buttons(&buttons);

    user_data->x_analog          = joystick.x_analog;
    user_data->y_analog          = joystick.y_analog;
    user_data->left_analog       = slider.left_analog; 
    user_data->right_analog      = slider.right_analog;
    user_data->joystick_button   = buttons.joystick_button;
}

void put_user_data_into_can_message(MESSAGE *can_message, USER_DATA* user_data){
    can_message->data[0]       = user_data->x_analog;
    can_message->data[1]       = user_data->y_analog;
    can_message->data[2]       = user_data->left_analog;
    can_message->data[3]       = user_data->right_analog;
    can_message->data[4]       = user_data->joystick_button;
}

void input_com_send_data(){
    MESSAGE message;
    message.id = 1;
    message.length = 5;
    USER_DATA user_data;

    /*put all data into the struct, then put all struct values into the can message*/
    put_all_data_into_user_data(&user_data);
    put_user_data_into_can_message(&message, &user_data);
    /*send the message over the can buss*/
    can_write(&message);
    //jeg hørte man ikke skulle overflowe canbussen og derfor skulle ha litt delay så setter inn det hørte
    _delay_ms(20);
}

