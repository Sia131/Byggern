#include "node2_adc.h"

void aadc_init(){
    /*set ADC2 as input*/
    DDRF &= ~(1 << PF2);

    /*AVCC with external capacitor ar AREF  pin */
    ADMUX |= ( 1 << REFS0);

    /*pick ADC2*/
    ADMUX |= (1 << MUX1);

    /*ADC control register */

    /*enable ADC */ 
    ADCSRA |= (1 << ADEN);

    /*Prescaler*/
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

    /* Left shift the ADC data */
    ADLAR = 1
}



int adc_read(){
    /*start conversion */
    ADCSRA |= (1 << ADCS);

    while(!(ADCSRA & (1 <<ADIF))){}
    return (ADCH);
}


