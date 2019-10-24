#ifndef SPI_H
#define SPI_H

#include <stdint.h>

/*******************************************************
Serial Peripheral Interface (SPI) Master module

Implements the SPI master for the nRF51 series

Pins
	SPI				Slave Select, 	MOSI, 	MISO,	SCK
	Chip	 		16, 			21, 	22,		23
	Breakoutboard	16, 			15, 	14, 	13

Using 1MHz frequency
*/

void SPI_MasterInit();

void spi_transmitt(uint8_t cData);

uint8_t spi_receive();

#endif