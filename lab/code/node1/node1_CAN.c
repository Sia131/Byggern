#include "node1_CAN.h"
#include "node1_USART.h"
#include <avr/delay.h>
#include <avr/interrupt.h>


void can_intr_init(){
    DDRE &= ~(1 << PD2);
}


void can_init(){
    mcp_reset();
    received = 0;
    // set loopback mode
    mcp_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
}

void can_write(MESSAGE* message){ // still missing support for multiple buffer inputs
    unsigned int ID = message->id;
    char* data = message->data;
    uint8_t length = message->length;
    while (mcp_read(MCP_TXB0CTRL) & (1 << 3)) {_delay_ms(1);}
    //load transmit buffers
    mcp_write(MCP_TXB0SIDH,ID >> 3);
    mcp_write(MCP_TXB0SIDL, ID << 5); //most likely all messages will be 8bit so this is unneccessary        
    mcp_write(MCP_TXB0DLC, length & 0x0F);
    for (int i=0; i < length;i++){
        mcp_write(MCP_TXB0Dm + i, data[i]) 
    }

    mcp_request_to_send();
}

void can_receive(MESSAGE* msg){
    if ( (mcp_read(MCP_CANINTF) & 1)|| received){
        msg->id = mcp_read(MCP_RXB0SIDH) << 3;
        msg->id |= mcp_read(MCP_RXB0SIDL) >> 5;
        msg->length = mcp_read(MCP_RXB0DLC) & 0x0F;
        for (int i=0;i < msg->length; i++){
            msg->data[i] = mcp_read(MCP_RXB0DM + i);
        }
    mcp_bit_modify(MCP_CANINTF, 0x01, 0);
    received = 0;
    }

}


void can_intr_init(){
    DDRD &= ~(1 << PD2);
    clei();
    MCUCR |= ( 1 << ISC01);
    GICR |= (1 << INT0);
    sei();
    
    //variable to we set to 0
    received = 0;
}

ISR(INT0_vect){
    //check for different stuff
    //set the same variable to true
}