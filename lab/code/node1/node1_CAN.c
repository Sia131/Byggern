#include "node1_CAN.h"
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>



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
    spi_init();
    mcp_reset();


	// tester om jeg er i configure mode
	uint8_t mode = mcp_read(MCP_CANSTAT);
	if ((mode & MODE_MASK) != MODE_CONFIG) {
		printf("MCP ikke i konf.mod. CANSTT: %x \r\n", mode);
	}

    can_intr_init();

    // set loopback mode
    //mcp_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);

    //normal mode
    mcp_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
    printf("CANSTAT: %x\r\n", mcp_read(MCP_CANSTAT));
}

void can_write(const MESSAGE* msg){ // still missing support for multiple buffer inputs
    //load transmit buffers
    mcp_write(MCP_TXB0SIDH, msg->id >> 3);
    mcp_write(MCP_TXB0SIDL, msg->id << 5); //last 3 bit
    mcp_write(MCP_TXB0DLC, msg->length & 0x0F);

    for (int i=0; i < msg->length; ++i){

        mcp_write(MCP_TXB0D0 + i, (msg->data)[i]);
    }
    //Set the TXB0CTRL.TXREQ bit to start transmission
    mcp_request_to_send();
    
}

void can_receive(MESSAGE *msg){
    if ( (mcp_read(MCP_CANINTF) & 0x01) || received){
        //reset id
        msg->id = mcp_read(MCP_RXB0SIDH) << 3;
        msg->id |= mcp_read(MCP_RXB0SIDL) >> 5;

        //Read length
        msg->length = mcp_read(MCP_RXB0DLC) & 0x0F;

        //Read data
        for (int i=0; i < msg->length; i++){
            msg->data[i] = mcp_read(MCP_RXB0D0 + i);
        }

        //Clear CANINTF. RX0IF after reset
        mcp_bit_modify(MCP_CANINTF, 0x01, 0);

        //clear flags
        received = 0;
    }
}

void can_intr_init(){
    DDRD &= ~(1 << PD2);
    cli();
    GICR |= (1 << INT0);
    MCUCR |= ( 1 << ISC01);
    sei();
    received = 0;
    //set the receive interrup on buffer 0, set all other interups to disabled
    mcp_bit_modify(MCP_CANINTE, 0xFF, 0x01);
}

ISR(INT0_vect){
    received = 1;
    mcp_bit_modify(MCP_CANINTF, 0x01, 0);

}

uint8_t get_received(){
    return received;
}

ISR(BADISR_vect){}