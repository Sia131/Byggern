#include "CAN.h"
#include "MCP.h"
#include "MCP2515.h"
#include "defines.h"

#ifdef __AVR_ATmega2560__
    #include "../node2/pwm.h"
    #include "../node2/motor.h"
    #include "../node2/controller.h"
    #include "../node2/solenoid.h"
    #include "../node2/goal.h"
#endif

#ifdef __AVR_ATmega162__
    #include "../node1/node1.h"
#endif

#include "UART.h"

#include <util/delay.h>
#include <avr/interrupt.h>

#define MCP_TXB0SIDH	0x31
#define MCP_TXB0SIDL	0x32
#define MCP_TXB0DLC     0x35
#define MCP_TXB0D0  	0x36

#define MCP_RXB0SIDH	0x61
#define MCP_RXB0SIDL	0x62
#define MCP_RXB0DLC     0x65
#define MCP_RXB0D0  	0x66

static int controller_setting = 2;
static int using_bluetooth = 1;
static int not_initialized = 1;

void CAN_init()
{
    MCP_reset(); 

    received = 0;

    uint8_t mode = MCP_read(MCP_CANSTAT);
    if (mode & MODE_MASK != MODE_CONFIG)
    {
        MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
    }

    CAN_intr_init();    

    // loopback mode
    // MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
    // normal mode
    MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

}


void CAN_intr_init()
{
    #ifdef __AVR_ATmega2560__
        DDRD &= ~(1 << PD2);
    #endif

    cli();
    INTRREG  |= (1 << INTRSEL);
    INTRSET  |= (1 << INTRSC);
    sei();

    received = 0;
    
    //Receive interrupt
    MCP_bit_modify(MCP_CANINTE, 0x01, 0x00);
    MCP_bit_modify(MCP_CANINTE, 0x01, 0xFF);

    //Reset interrupt
    MCP_bit_modify(MCP_CANINTF, 0x01, 0x00);

   
    if (MCP_read(MCP_CANINTF) & 1)
    {
        received = 1;
    }
}

ISR(INTR_VECT)
{
    cli();
    if (MCP_read(MCP_CANINTF) & 1)
    {
        received = 1;
    }
    MCP_bit_modify(MCP_CANINTF, 0x01, 0x00);

    CAN_message m;
    CAN_receive(&m);

    //printf("ID: %d\n", m.id);

    if (m.id == INPUT_COM)
    {
        #ifdef __AVR_ATmega2560__
            if (not_initialized)
            {
                goal_init();
                not_initialized = 0;
            }
            
            int8_t ang;
            int pos;
            if (controller_setting == 0)
            {
                ang = (int8_t)m.data[1] - 10;
                pos = (int)((int8_t)m.data[0]) + 128;
                controller_set_reference(pos * 50);
            }
            else if (controller_setting == 1)
            {
                ang = (int8_t)((int)m.data[2] - 10 - 120);
                pos = m.data[3];
                controller_set_reference(pos * 50);
            }
            else if (controller_setting == 2)
            {
                ang = (int8_t)m.data[0] - 10;
                pos = m.data[3];
                controller_set_reference(pos * 50);
            }
            else if (controller_setting == 3)
            {
                ang = (int8_t)m.data[0] - 10;
                using_bluetooth = 1;
            }
            pwm_set_angle(ang); //-10 is offset for the servo
            
            
            if (m.data[4] && !(solenoid_get_shot()))
            {
                solenoid_shoot();
            }
            else if (!m.data[4])
            {
                solenoid_clear_shot();
            } 
        #endif
    }
    if (m.id == CONTROLLER_SETTINGS)
    {
        #ifdef __AVR_ATmega2560__
            controller_setting = m.data[0];
        #endif
    }
    
    if (m.id == TRANSFERRED_GOALS)
    {
        #ifdef __AVR_ATmega162__
            printf("receive\n");
            decrease_lives();
            
        #endif
    }
    
	if (m.id == BLUETOOTH_MSG)
	{
		
        #ifdef __AVR_ATmega2560__
            printf("Bluetooth! %d", m.data[0]);
            if (using_bluetooth)
            {
                controller_set_reference(m.data[0] * 50);
            }
        #endif
	}
}


void CAN_send(const CAN_message* msg)
{
    while (MCP_read(MCP_TXB0CTRL) & (1 << 3)) { _delay_ms(1); }

    MCP_write(MCP_TXB0SIDH, msg->id >> 3);
    MCP_write(MCP_TXB0SIDL, msg->id << 5);
    MCP_write(MCP_TXB0DLC, msg->length & 0x0F);

    for (int i = 0; i < msg->length; ++i)
    {
        MCP_write(MCP_TXB0D0 + i, (msg->data)[i]);
    }

    //Ready to transmit, highest priority
    MCP_bit_modify(MCP_TXB0CTRL, 0x0B, 0xFF);
}


void CAN_receive(CAN_message* msg)
{
    //If received
    if ((MCP_read(MCP_CANINTF) & 1) || received) 
    {
        //Read id
        msg->id  = MCP_read(MCP_RXB0SIDH) << 3;
        msg->id |= MCP_read(MCP_RXB0SIDL) >> 5;

        //Read length
        msg->length = MCP_read(MCP_RXB0DLC) & 0x0F;

        //Read data
        for (int i = 0; i < msg->length; ++i)
        {
            (msg->data)[i] = MCP_read(MCP_RXB0D0 + i);
        }

        //Clear CANINTF.RX0IF after read
        MCP_bit_modify(MCP_CANINTF, 0x01, 0);

        //Clear flags
        received = 0;
    }  
}