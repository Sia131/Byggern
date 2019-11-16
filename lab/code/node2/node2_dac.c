#include "node2_dac.h"
#include "util/delay.h"


void dac_send_analogue(uint8_t value){
    /*package with slave address at 01010000, output = DAC0, value */
    unsigned char package[3] = {80, 0x00, value};
    TWI_Start_Transceiver_With_Data(package,3);
    //_delay_ms(1);
}