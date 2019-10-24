#include "MCP.h"
#include "SPI.h"
#include <avr/io.h>
#include <stdint.h>
#include "defines.h"


void MCP_cs(uint8_t i)
{
    if (i)
    {
        PORTB |= (1 << SPI_SS); 
    }
    else
    {
        PORTB &= ~(1 << SPI_SS); 
    }
}

uint8_t MCP_read(uint8_t adr)
{
    MCP_cs(0);

    SPI_MasterTransmit(MCP_READ);
    SPI_MasterTransmit(adr);

    //Listen on SO
    uint8_t data = SPI_MasterTransmit(0);

    MCP_cs(1);

    return data;
}


void MCP_write(uint8_t adr, uint8_t data)
{
    MCP_cs(0);

    SPI_MasterTransmit(MCP_WRITE);
    SPI_MasterTransmit(adr);
    SPI_MasterTransmit(data);

    MCP_cs(1);
}


void MCP_request_to_send()
{
    MCP_cs(0);

    //Only using buffer 0
    SPI_MasterTransmit(MCP_RTS_TX0); 

    MCP_cs(1);
}


uint8_t MCP_read_status()
{
    MCP_cs(0);
    
    SPI_MasterTransmit(MCP_READ_STATUS);

    uint8_t status = SPI_MasterTransmit(0);
    
    MCP_cs(1);

    return status;
}


void MCP_bit_modify(uint8_t adr, uint8_t mask, uint8_t data)
{
    MCP_cs(0);

    SPI_MasterTransmit(MCP_BITMOD);
    SPI_MasterTransmit(adr);
    SPI_MasterTransmit(mask);
    SPI_MasterTransmit(data);

    MCP_cs(1);
}


void MCP_reset()
{
    MCP_cs(0);

    SPI_MasterTransmit(MCP_RESET);

    MCP_cs(1);
}