#include "node2_USART.h"
#include "node2_CAN.h"
#include <util/delay.h>



int main(){
    USART_Init(MYUBRR);
    
    can_init();
    MESSAGE message = {
        2, 
        8,
        "abcdefgh",
    };
    

    while(1){
        can_write(&message);
        
    }
    return 0;
}