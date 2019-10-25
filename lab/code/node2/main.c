#include "node2_USART.h"
#include "node2_CAN.h"
#include <util/delay.h>



int main(){
    USART_Init(MYUBRR);
    
    can_init();
    MESSAGE message = {
        2, 
        5,
        "asdfg",
    };

    MESSAGE receive;
    
    can_write(&message);
    _delay_ms(1);

    can_receive(&receive);

    printf("id   %d\r\n", receive.id);
    printf("length   %d\r\n", receive.length);
    printf("data   %d\r\n", receive.data);
    

   //spi_init();

    while(1){

    }
    return 0;
}