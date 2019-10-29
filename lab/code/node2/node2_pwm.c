#include "node2_pwm.h"


void pwm_init(){
    /*set the DDR register on OC3A as output
    PE3 = OC3A 
    Pin 5 on shield */
    //cli();
    DDRE |= (1 << PE3);

    /*clear OC3A on compare match set OC3A at BOTTOM
    non-inverting */
    TCCR3A = (1 << COM3A1);

    /*Mode 14 -Fast PWM
    */
    TCCR3A |= (1 << WGM31);
    TCCR3B |= (1 << WGM33) | (1 << WGM32);

    /*select clock speed
    Prescale = 8 */
    TCCR3B |= (1 << CS31);

    ICR3 = 39999;

    //sei();

    //counter sammenlignes kontnuerlig med counter (TCNT1)
    //pwm_set_ms(0);
}

void pwm_set_ms(double ms){
    if (ms < 0.9) {ms = 0.9;}
    if(ms > 2.4) {ms = 2.4;}
    OCR3A = (ms/20)*ICR3;
}

void pwm_set_angle(double angle){
    double ms = (angle*667)/100000 + 0.9;
    pwm_set_ms(ms); 
}

void joystick_to_servo(){
    
}