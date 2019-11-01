#include "node2_USART.h"
#include "node2_CAN.h"
#include <util/delay.h>
#include "node2_input_com.h"
#include "node2_pwm.h"
#include "node2_adc.h"
#include "node2_motor.h"
#include "node2_controller.h"


int main(){
    USART_Init(MYUBRR);
    can_init();
    pwm_init();
    adc_init();
    //motor_init();
    //controller_init(4, 0, 4);
    //controller_set_reference(50);

    //int32_t value = -3333333;
    //uint8_t next = value;
    //printf("%d \r\n", next);


    while(1){
        uint16_t adc = adc_read();
        printf("%x  \r\n", adc);

        //joystick_to_servo();
        //controller_update();
        //controller_update();
    }
    return 0;
}