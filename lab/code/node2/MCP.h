#ifndef MCP_H
#define MCP_H

#include <stdio.h>
#include <stdint.h>
#include "MCP2515.h"

/****************************************
MCP module, Controller Area Netword 
(CAN) controller module

Controller that can implement the CAN 
specification, version 2.0B. 

Utilizes the SPI module (as specified
in SPI.h) for the implementation. 
 
The functions implemented are: 
	
	MCP_cs(uint8_t i)
	
		Slave Select function
		
		Deselect for i == 0, else select. 
		
	MCP_read(uint8_t adr)
	
		Reads the value of the adr 
		address. Returns the 
		value found in the value 
		found in the address. 
		
	MCP_write(uint8_t adr, uint8_t data)
	
		Writes the data value to the 
		adr address. 
		
	MCP_request_to_send()
	
		Transmitts the Request to Send 
		command. 
		
	MCP_read_status()
	
		Reads the status register. 
		Returns the value found.
		
	MCP_bit_modify(uint8_t adr, 
	uint8_t mask, uint8_t data)
	
		Modifies the value at the adress
		adr with the value data. Only 
		modifies the bits set in the 
		mask variable, leaves the rest 
		as they were. 
		
	MCP_reset()
	
		Transmitts the reset command, 
		resets the MCP. 

****************************************/

void MCP_cs(uint8_t i);

uint8_t MCP_read(uint8_t adr);


void MCP_write(uint8_t adr, uint8_t data);


void MCP_request_to_send();


uint8_t MCP_read_status();


void MCP_bit_modify(uint8_t adr, uint8_t mask, uint8_t data);


void MCP_reset();

#endif