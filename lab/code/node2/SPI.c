#include "SPI.h"
#include <avr/io.h>
#include "UART.h"


/*SPI*/
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_SS PB7
#define SPI_SCK PB1

void SPI_MasterInit()
{
    /*Set MOSI, SCK, and slave select output*/
    DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);

    /*Self slave select (microcontroller)*/
    // __AVR_ATmega2560__
	DDRB |= (1 << PB0);


    /*Set MISO input*/
    DDRB &= ~(1 << SPI_MISO);
    /*Enable SPI, Master, set clock rate fck/16*/
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); 
}

void spi_transmitt(uint8_t cData) {
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while (!(SPSR & (1 << SPIF)));
}

uint8_t spi_receive() {
	SPDR = 0xff;
	/* Wait for reception complete */
	while (!(SPSR & (1 << SPIF)));
	/* Return data register */
	return SPDR;
}

