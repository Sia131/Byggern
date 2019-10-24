#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdio.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void UART_Init(unsigned int ubrr);

void UART_Transmit(unsigned char data);

char UART_Receive();

int put_char(char data, FILE* file);

int get_char(FILE* file);

#endif
