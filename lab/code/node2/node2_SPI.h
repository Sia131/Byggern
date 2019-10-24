#ifndef NODE2_SPI_H
#define NODE2_SPI_H

//#include <avr/io.h>
#include "node2_USART.h"


void spi_init();

void spi_transmitt(uint8_t cData);

uint8_t spi_receive();

uint8_t spi_master_transmitt(char data);

#endif
