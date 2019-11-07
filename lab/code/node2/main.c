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



int main(){
    
    USART_Init(MYUBRR);
    can_init();
    pwm_init();
    adc_init();
    //controller_init(4,0,4);
    //controller_set_reference(0);
    solenoid_init();

    //solenoid_activate();




    //USER_DATA user_data; 

    //sound_init();

    //sound_set_tone(15);
    //_delay_ms(500);
    //sound_set_tone(1);
    //_delay_ms(500);
    //sound_set_tone(5);

    //sound_set_tone(11);

    //sound_play_xp();

    while(1){
        /*
        input_com_receive_data(&user_data);
        controller_set_reference(user_data.x_analog);
        controller_update();
       */
      
    }
    return 0;
}
