#include "SPI.h"
#include <avr/io.h>
#include "defines.h"
#include "UART.h"

void SPI_MasterInit()
{
    /*Set MOSI, SCK, and slave select output*/
    DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);

    /*Self slave select (microcontroller)*/
    #ifdef __AVR_ATmega2560__
        DDRB |= (1 << PB0);
    #endif

    /*Set MISO input*/
    DDRB &= ~(1 << SPI_MISO);
    /*Enable SPI, Master, set clock rate fck/16*/
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); 
}

uint8_t SPI_MasterTransmit(char cData)
{ 
    /*Start transmission*/
    SPDR = cData;
    /*Wait for transmission complete*/
    while (!(SPSR & (1 << SPIF)));
    //printf("SPItrans!");

    return SPDR;
}