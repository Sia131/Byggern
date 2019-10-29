#include "node2_USART.h"
#include "node2_CAN.h"
#include <util/delay.h>
#include "node2_input_com.h"
#include "node2_pwm.h"


int main(){
    USART_Init(MYUBRR);
    can_init();
    pwm_init();

    //pwm_set_ms(0.9);

    pwm_set_angle(180);

    int i = 0;
    while(1){
        _delay_ms(10);
        pwm_set_angle(i++);
    }
    return 0;
}