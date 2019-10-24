#ifndef NODE2_CAN_H
#define NODE2_CAN_H

//#include <avr/io.h>
//#include "mcp2515.h"
#include "node2_mcp.h"

static uint8_t received;


typedef struct MESSAGE{
    uint8_t id;
    uint8_t length;
    uint8_t data[8]; // 0->8 bytes
}MESSAGE;

typedef enum CAN_ID{
    INPUT_COM,
    CONTROLLER_SETTING,
    REQUEST_GOALS,
    TRANSFERRED_GOALS,
    BLUETOOOTH_MSG
}CAN_ID;

static uint8_t received;

void can_init();

void can_intr_init();

void can_write(const MESSAGE *msg);

void can_receive(MESSAGE *msg);

#endif