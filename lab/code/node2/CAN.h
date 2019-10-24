#ifndef CAN_H
#define CAN_H

#include <stdint.h>

/*************************************
Controll Area Network (CAN) module

Implements the struct CAN messages 
and enum CAN ID. Same as the code 
in Node 1 and 2. 

The functions implemented are:

	CAN_init()
	
		Initializes the CAN module
		and sets it in normal 
		mode. 
		
	CAN_intr_init()
	
		Initializes the CAN 
		interrupt for node 1 
		and 2. 
		
	CAN_send(const CAN_message* msg)
	
		Sends the CAN message msg
		over the CAN bus. 
		
	CAN_receive(CAN_message* msg)
	
		Reads the current message 
		in the MCP, if there is 
		one. 

*************************************/

typedef struct CAN_message
{
    uint8_t id;
    uint8_t length;
    uint8_t data[8]; //0-8 bytes

} CAN_message;

typedef enum CAN_ID 
{ 
	INPUT_COM, 
	CONTROLLER_SETTINGS, 
	REQUEST_GOALS, 
	TRANSFERRED_GOALS, 
	BLUETOOTH_MSG 
} CAN_ID;

static uint8_t received;


void CAN_init();


void CAN_intr_init();


void CAN_send(const CAN_message* msg);


void CAN_receive(CAN_message* msg);

#endif