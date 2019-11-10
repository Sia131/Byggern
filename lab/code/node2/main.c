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

    //play_underworld();

    game_play();
    return 0;
}
