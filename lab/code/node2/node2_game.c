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
    controller_init(3,0,12);
    //int difficulty = 0;
    //controller_difficulty(difficulty);
    MESSAGE can_message;
    USER_DATA user_data;
    //uint8_t internal_state = 0; Maybe use this??

    while(1){
            can_receive(&can_message);

            if (can_message.id == 1){ // userdata
                put_can_message_into_user_data(&can_message, &user_data);
                printf("userdata received, x_analog = %d\n",user_data.x_analog);
                joystick_to_servo(user_data.x_analog);
                controller_set_reference(user_data.x_analog);
                controller_update();
                solenoid_update_shot(user_data.joystick_button);
                printf("right: %d  \r\n", user_data.joystick_button); 
                
                //if (IR_lys_set)
                  //  game_over(); 
                    // set can_message.id = 5 
                continue;
            }

            if (can_message.id == 4) { // play mario
                printf("song\n\n");
                play_mario();
                //continue;
            }
            if (can_message.id == 5) { // play underworld
                printf("song 2\n\n");
                play_underworld();
                //continue;
            }
            /*can_message.id = 5 { //game 
                play losing song
                send score
                solenoid_clear_shot
                can_mesaage.id = Nill; ?? aka/idle
            }*/
            /*
            if (0){//(game_over()){ //this is a function that needs to be made: take in value from IR
                solenoid_clear_shot();
                //can_send message that game is over
            }*/
            if (can_message.id == 3){ //msg containing difficulty
                printf("difficulty");
                int difficulty = can_message.data[0];
                controller_difficulty(difficulty);
                continue;   
            }
           }
}
       
 