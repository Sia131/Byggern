#ifndef NODE2_DAC_H
#define NODE2_DAC_H

#include "TWI_Master.h"
#include <stdint.h>
#include "node2_USART.h"



/*sending a value of 0-5V signal coressponding to 0-255 bit signal
*/
void dac_send_analogue(uint8_t value);


#endif