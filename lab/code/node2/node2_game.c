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
    controller_difficulty(0);
    MESSAGE can_message;
    MESSAGE return_message;
    USER_DATA user_data;
    uint8_t timer4 = 0;
    uint8_t difficulty = 0;    
    while(1) {
        can_receive(&can_message);

        if (can_message.id == 0){/*do nothing*/ }
        
        if (can_message.id == 10){ //Play game
            if (timer4 == 0){
                timer4_start();
                timer4 = 1;
            }
            put_can_message_into_user_data(&can_message, &user_data);
            joystick_to_servo(user_data.x_analog);
            controller_set_reference(user_data.left_analog);
            solenoid_update_shot(user_data.joystick_button);

            if (lost_game() == 1){
                timer4_stop();
                timer4 = 0;
                can_message.id = 0; //IDLE  
                return_message.id = 1;
                return_message.length = 1;
                return_message.data[0] =  solenoid_get_shot();
                can_write(&return_message);
                solenoid_clear_shot();
                play_mario();
                printf("%d \r\n",adc_read());
                

            }
            continue;
        }
        if (can_message.id == 30){ //msg containing difficulty
            can_message.id == 0; //IDLE
            printf("difficulty");
            difficulty = can_message.data[0];
            controller_difficulty(difficulty);
            continue;   
        }
        if (can_message.id == 40) { // play mario
            can_message.id == 0; //IDLE
            printf("mario\n\n");
            play_mario();
            continue;
        }
        if (can_message.id == 50) { // play underworld
            can_message.id == 0; //IDLE
            play_underworld();
            continue;
        }
    }
 }

 