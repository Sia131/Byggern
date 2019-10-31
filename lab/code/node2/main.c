#include "node2_USART.h"
#include "node2_CAN.h"
#include <util/delay.h>
#include "node2_input_com.h"
#include "node2_pwm.h"
#include "node2_adc.h"


int main(){
    USART_Init(MYUBRR);
    can_init();
    pwm_init();
    adc_init();
    while(1){
        joystick_to_servo();
       uint16_t adc = adc_read();
        printf("%d   \r\n" , adc);
    }
    return 0;
}