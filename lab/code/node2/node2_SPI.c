#include "node2_SPI.h"

/*SPI node2*/
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_SS PB7
#define SPI_SCK PB1

void spi_init(){
    /* Set MOSI, CLK and SS as output*/
    DDRB = (1 << SPI_SS)|(1 << SPI_MOSI)|(1 << SPI_SCK);

	/*Self slave select (microcontroller)*/
	DDRB |= (1 << PB0);

    /*Set MISO as input */
	DDRB &= ~(1 << SPI_MISO);

    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);

    PORTB |= (1 << SPI_SS);
}

void spi_transmitt(uint8_t cData){
    /* Start transmission */
    SPDR = cData; 
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
}

uint8_t spi_receive(){
    SPDR = 0xff;
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)));
    /* Return data register */
    return SPDR;
}

uint8_t spi_master_transmitt(char data){
	/*Start transmission*/
	SPDR = cData;
	/*Wait for transmission complete*/
	while (!(SPSR & (1 << SPIF)));
	//printf("SPItrans!");

	return SPDR;
}