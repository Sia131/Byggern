#include "node2_pwm.h"
#include "node2_input_com.h"


void pwm_init(){
    /*set the DDR register on OC1B as output
    PE3 = OC1B 
    PB6 on arduino
    pin 6 on I/O board */
    DDRB |= (1 << PB6);

    /*clear OC3A on compare match set OC3A at BOTTOM
    non-inverting */
    TCCR1A = (1 << COM1B1);

    /*Mode 14 -Fast PWM
    */
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);

    /*select clock speed
    Prescale = 8 */
    TCCR1B |= (1 << CS11);

    ICR1 = 39999;

    pwm_set_angle(90);
}

void pwm_set_ms(double ms){
    if (ms < 0.9) {ms = 0.9;}
    if(ms > 2.4) {ms = 2.4;}
    OCR1B = (ms/20)*ICR1;
}

void pwm_set_angle(double angle){
    double ms = (angle*667)/100000 + 0.9;
    pwm_set_ms(ms); 
}


void joystick_to_servo(){
    USER_DATA user_data;
    input_com_receive_data(&user_data);
    double angle = 1.8*(user_data.x_analog);
    pwm_set_angle(angle);
    
}