#include "sound.h"
#include <util/delay.h>

void sound_init(){
    /*set the DDR register on OC1B as output
    PE3 = OC1B */
    DDRE |= (1 << PE3);

    /*clear OC3A on compare match set OC3A at BOTTOM
    non-inverting */
    TCCR3A = (1 << COM3A0);

    /*Mode 14 -Fast PWM
    */
    //TCCR3A |= (1 << WGM31);
    TCCR3B |= (1 << WGM33) | (1 << WGM32);

    /*select clock speed
    Prescale = 8 */
    TCCR3B |= (1 << CS31) | ( 1 << CS30);

}

/*the range of the sound should be between 380Hz to 5kHz*/
void sound_set_tone(float freq){
    //float period = 1 / freq;
    float freq_mcu = 16000000;
    int value = (freq_mcu/(2*64*freq)) - 1;
    ICR3 = value;
    //OCR3A = ICR3/2;
}



