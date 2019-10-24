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

The functions implemented are: 
	
	SPI_init()
	
		Initializes the SPI module, the pins
		and the NRF_SPI_REG struct as defined. 
		
	SPI_MasterTransmit(char cData)
	
		SPI Master Transmit function, implements 
		the SPI transmit function.
		
		Sends the 8-bit value cData.
		
		Returns an 8-bit result value.
		
*******************************************************/

void SPI_MasterInit();

uint8_t SPI_MasterTransmit(char cData);



#endif