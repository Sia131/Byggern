#include "node2_USART.h"
#include "node2_CAN.h"
#include <util/delay.h>
#include "node2_input_com.h"


int main(){
    USART_Init(MYUBRR);
    can_init();
    
    USER_DATA user_data; 
    input_com_receive_data(&user_data);
    printf("joystick_button %d\r\n",user_data.x_analog);

    while(1){
    }
    return 0;
}