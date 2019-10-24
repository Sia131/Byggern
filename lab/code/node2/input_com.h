#ifndef INPUT_COM_H
#define INPUT_COM_H

#include "CAN.h"

/******************************
Input Communication module

Implements communication of 
user input values from
node 1 to node 2. 

Uses the variables 
USER_DATA user_data and 
CAN_message input_message.

The functions implemented are:

	input_com_init()
	
		Initializes the 
		variables user_data
		and input_message.

	input_com_send()
	
		Sends a can message
		containing the user 
		input data. Returns a
		USER_DATA struct 
		with the sent values. 
		
	input_com_recieve()
	
		Reads and converts a
		CAN message into and
		returns	a USER_DATA 
		struct.

******************************/

typedef struct USER_DATA 
{ 
    int8_t  pos_X;
    int8_t  pos_Y;
    uint8_t sli_left;
    uint8_t sli_right;
    uint8_t but;
} USER_DATA;

static USER_DATA user_data;
static CAN_message input_message;


void input_com_init();

USER_DATA input_com_recieve();

#ifdef __AVR_ATmega162__
USER_DATA input_com_send();
#endif


#endif