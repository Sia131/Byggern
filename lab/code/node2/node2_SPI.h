#ifndef NODE2_SPI_H
#define NODE2_SPI_H

//#include <avr/io.h>
#include "node2_USART.h"

/*SPI node2*/
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_SS PB7
#define SPI_SCK PB1


void spi_init();

void spi_transmitt(uint8_t cData);

uint8_t spi_receive();

uint8_t spi_master_transmitt(char cdata);

#endif
