#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdio.h>


/************************************************************
Universal Asynchronous serial Receiver and Transmitter (UART)

Implements UART module for ATmega162 and ATmega 2560

There is support for Universal Synchronous and Asynchronous
serial Receiver and Transmitter, though this is not necessary
for this system. 

Uses 8 bit data, 2 stop bits, baudrate 9600 and normal 
transmission speed. 

The functions implemented are:

	UART_Init(unsigned int ubrr)
	
		Initializes the module for the settings described.
		The ubrr parameter is calculated based on the 
		baudrate and the CPU frequency, see defines.h
		
	UART_Transmit(unsigned char data)	
		
		Transmitts the parameter once the transmit buffer
		is empty. 
		
	UART_Receive()
	
		Waits for data to be recieved. Returns the value 
		recieved. 
		
	put_char(char data, FILE* file)
		
		Wrapper function for UART_Transmit, to be used with
		the printf function. Also implements transmitting
		'\r' when '\n' is transmitted, for easier formatting. 
		
	get_char(FILE* file)
	
		Wrapper function for UART_Receive,to be used with
		the printf function. Returns the return value 
		from UART_Receive.

************************************************************/

void UART_Init(unsigned int ubrr);

void UART_Transmit(unsigned char data);

char UART_Receive();

int put_char(char data, FILE* file);

int get_char(FILE* file);

#endif
