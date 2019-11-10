#include "node2_USART.h"
#include "node2_CAN.h"
#include <util/delay.h>
#include "node2_input_com.h"
#include "node2_pwm.h"
#include "node2_adc.h"
#include "node2_motor.h"
#include "node2_dac.h"
#include "node2_controller.h"
#include "sound.h"
#include <util/delay.h>
#include "node2_solenoid.h"
#include "node2_melody.h"
 
 void game_play(){
    solenoid_init();
    int difficulty = 0;
    controller_difficulty(difficulty);
    while(1){
            //init can parsing
            MESSAGE can_message;
            USER_DATA user_data;
            can_receive(&can_message);

            if (can_message.id == 0){ //msg containing difficulty
                printf("difficulty");
                difficulty = can_message.data[0];
                controller_difficulty(difficulty);
                continue;   
            } 
            if (can_message.id == 1){ // userdata
                input_com_receive_data(&user_data);
                solenoid_update_shot(user_data.joystick_button);
                joystick_to_servo(user_data.x_analog);
                controller_set_reference(user_data.right_analog);
                controller_update();
                printf("x: %d", user_data.x_analog);
                printf("right: %d", user_data.right_analog); //only givingo ut 0


                continue;
            }
            if (can_message.id == 2) { // play song
                printf("song");
                play_mario();
                continue;
            }
            /*
            if (0){//(game_over()){ //this is a function that needs to be made: take in value from IR
                solenoid_clear_shot();
                //can_send message that game is over
            }*/

           }
}
       
 