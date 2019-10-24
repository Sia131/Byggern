#ifndef NODE2_USART_H_
#define NODE2_USART_H_

#include <avr/io.h>
#include <stdio.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


void USART_Init(unsigned int ubrr);

void USART_Transmit(unsigned char data);

char USART_Receive();

int put_char(char data, FILE* file);

int get_char(FILE* file);


#endif /* NODE2_USART_H_ */