#ifndef NODE2_ADC_H
#define NODE2_ADC_H

#include "node2_USART.h"
#include <util/delay.h>
#include <stdio.h>

void adc_init();

uint16_t adc_read();


#endif