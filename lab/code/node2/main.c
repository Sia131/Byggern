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
    controller_init(4,0,4);
    controller_set_reference(0);
    USER_DATA user_data; 



    

    while(1){
        
        input_com_receive_data(&user_data);
        controller_set_reference(user_data.x_analog);
        controller_update();
    
    }
    
    return 0;
}