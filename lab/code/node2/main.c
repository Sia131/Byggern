#include "node2_USART.h"
#include "node2_CAN.h"
#include <util/delay.h>
#include "node2_input_com.h"
#include "node2_pwm.h"
#include "node2_adc.h"
#include "node2_motor.h"


int main(){
    USART_Init(MYUBRR);
    can_init();
    pwm_init();
    adc_init();
    motor_init();

    USER_DATA user_data;
    //uint8_t slider = right_slider_remapping(& user_data);

    while(1){
        input_com_receive_data(& user_data);
        /*
        //printf("%d   \r\n", user_data.x_analog);
        uint8_t slider = right_slider_remapping(& user_data);
        printf("slider before  %d   slider now   %d \r\n" ,user_data.right_analog,  slider);
        */
    joystick_to_u(& user_data);

    }
    return 0;
}