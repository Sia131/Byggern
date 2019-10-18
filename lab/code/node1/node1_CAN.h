#include <avr/io.h>
#include <stdint.h>
#include "node1_mcp.h"
#include "mcp2515.h"

#ifndef NODE1_CAN_H_
#define NODE1_CAN_H_
static uint8_t received;


typedef struct MESSAGE{
    uint8_t id;
    uint8_t length;
    uint8_t data[8];
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

void can_write(MESSAGE *message);

MESSAGE* can_receive();

#endif