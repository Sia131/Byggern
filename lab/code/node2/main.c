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
#include "node2_game.h"


int main(){
    
    
    USART_Init(MYUBRR);
    can_init();
    pwm_init();
    adc_init();
    sound_init();
    solenoid_init();

    printf("main \r\n");
    game_play();
    controller_init(4,0,8);
    timer4_start();

    while (1)
    {
        
        USER_DATA user_data;
        input_com_receive_data(&user_data);
        controller_set_reference(user_data.x_analog);
        //controller_update();
        //printf("%d \r\n", user_data.x_analog);
        
        joystick_to_servo(0);
        
    }
    
    
    
    
    return 0;
}
