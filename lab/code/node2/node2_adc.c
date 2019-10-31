#include "node2_adc.h"

void adc_init(){
    /*set ADC2 as input*/
    /*Pin A2 on shield */
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
    //ADMUX |= (1 <<ADLAR);
}



uint16_t adc_read(){
    /*start conversion */
    ADCSRA |= (1 << ADSC);
    while(!(ADCSRA & (1 <<ADIF))){}
    //printf("ddd");
    //double adc = ADCH;
    return ADC;
}


