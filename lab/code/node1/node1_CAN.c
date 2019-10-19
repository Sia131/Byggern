#include "node1_CAN.h"

//#include "node1_USART.h"
//#include "mcp2515.h"
//#include <avr/io.h>
//#include <stdio.h>

#define MCP_TXB0SIDH    0x31
#define MCP_TXB0SIDL    0x32
#define MCP_TXB0DLC     0x35
#define MCP_TXB0D0      0x36

#define MCP_RXB0SIDH    0x61
#define MCP_RXB0SIDL    0x62
#define MCP_RXB0DLC     0x65
#define MCP_RXB0D0      0x66


void can_init(){
    mcp_reset();
    received = 0;
    // set loopback mode
    mcp_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
}

void can_write( const MESSAGE* msg){ // still missing support for multiple buffer inputs
    
    while (mcp_read(MCP_TXB0CTRL) & (1 << 3)) {_delay_ms(1);}
    //load transmit buffers
    mcp_write(MCP_TXB0SIDH, msg->id >> 3);
    mcp_write(MCP_TXB0SIDL, msg->id << 5); //last 3 bit
    mcp_write(MCP_TXB0DLC, msg->length & 0x0F);

    for (int i=0; i < msg->length; ++i){

        mcp_write(MCP_TXB0D0 + i, (msg->data)[i]);
    }

    //ready to transmitt, highest priority
    mcp_bit_modify(MCP_TXB0D0, 0x0B, 0xFF);
}

void can_receive(MESSAGE *msg){
    if ( (mcp_read(MCP_CANINTF) & 1)|| received){
        msg->id = mcp_read(MCP_RXB0SIDH) << 3;
        msg->id |= mcp_read(MCP_RXB0SIDL) >> 5;

        //Read length
        msg->length = mcp_read(MCP_RXB0DLC) & 0x0F;

        //Read data
        for (int i=0;i < msg->length; i++){
            msg->data[i] = mcp_read(0x66 + i);
        }
    //Clear CANINTF. RX0IF after reset
    mcp_bit_modify(MCP_CANINTF, 0x01, 0);
    received = 0;
    }
}

/*
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
}*/