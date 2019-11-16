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

    printf("main");
    //game_play();

    MESSAGE can_message;
    USER_DATA user_data;

    controller_init(3,0,12);
    //timer4_start();
    
    while(1){
        //controller_set_reference(-50);
        //controller_update();
        //_delay_ms(10);
        motor_enable();
        dac_send_analogue(0);

    }
    return 0;
}
