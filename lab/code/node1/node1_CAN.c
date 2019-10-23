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
    printf("CANSTAT1: %x\r\n", mcp_read(MCP_CANSTAT));

    _delay_ms(1);
    printf("CANSTAT2: %x\r\n", mcp_read(MCP_CANSTAT));

	// Sjøltesting
	uint8_t value = mcp_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 er ikke i konfigurasjonsmodus etter reset. CANSTAT: %x \r\n", value);
	}

    /*
    _delay_ms(1);

    received = 0;
    uint8_t mode = mcp_read(MCP_CANSTAT);
    printf("CANSTAT: %x\r\n", mcp_read(MCP_CANSTAT));
    if (mode & MODE_MASK != MODE_CONFIG){
        mcp_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
    }

    //can_intr_init();

    // set loopback mode
    mcp_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
    printf("CANSTAT: %x\r\n", mcp_read(MCP_CANSTAT));


    //normal mode
    //mcp_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
    */
}

void can_write( const MESSAGE* msg){ // still missing support for multiple buffer inputs
    
    //while (mcp_read(MCP_TXB0CTRL) & (1 << 3)) {_delay_ms(1);} 
    //load transmit buffers
    mcp_write(MCP_TXB0SIDH, msg->id >> 3);
    mcp_write(MCP_TXB0SIDL, msg->id << 5); //last 3 bit
    mcp_write(MCP_TXB0DLC, msg->length & 0x0F);

    for (int i=0; i < msg->length; ++i){

        mcp_write(MCP_TXB0D0 + i, (msg->data)[i]);
    }
    mcp_request_to_send();
    //ready to transmitt, highest priority
    //mcp_bit_modify(MCP_TXB0D0, 0x0B, 0xFF);
}

void can_receive(MESSAGE *msg){
    //if received
    if ( (mcp_read(MCP_CANINTF) & 1)|| received){
        
        //reset id
        msg->id = mcp_read(MCP_RXB0SIDH) << 3;
        msg->id |= mcp_read(MCP_RXB0SIDL) >> 5;

        //Read length
        msg->length = mcp_read(MCP_RXB0DLC) & 0x0F;

        //Read data
        for (int i=0;i < msg->length; i++){
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
    MCUCR |= ( 1 << ISC01);
    GICR |= (1 << INT0);
    sei();
    
    received = 0;

    //generate interrupt in interrupt pin when message is received
    mcp_bit_modify(MCP_CANINTE, 0x01, 0x00);
    mcp_bit_modify(MCP_CANINTE, 0x01, 0xFF);

    //reset interrupt
    mcp_bit_modify(MCP_CANINTF, 0x01, 0x00);

}

ISR(INT0_vect){
    //turn of all interrupts
    printf("hei");
    cli();

    //check if interrupt has occured
    if(mcp_read(MCP_CANINTF) & 1){
        received = 1;
    }

    //reset interrupt manually
    mcp_bit_modify(MCP_CANINTF, 0x01, 0x00);

}