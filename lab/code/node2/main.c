#include "node2_USART.h"
#include "node2_CAN.h"
#include <util/delay.h>
#include "node2_input_com.h"
#include "node2_pwm.h"
#include "node2_adc.h"
#include "node2_motor.h"
#include "node2_dac.h"
#include "node2_controller.h"


int main(){

    USART_Init(MYUBRR);
    can_init();
    pwm_init();
    adc_init();


    

    while(1){

    }
    return 0;
}