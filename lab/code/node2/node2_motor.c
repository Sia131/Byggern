#include "node2_motor.h"
#include <util/delay.h>




void motor_init(){
    TWI_Master_Initialise();
    /*ADC8-15 (MJ2) as inputs*/
    DDRK = 0;

    /*Set MJ1 pins as output*/ 
    DDRH |= (1 << DIR);
    DDRH |= (1 << SEL);
    DDRH |= (1 << EN);
    DDRH |= (1 << OE);
    DDRH |= (1 << RST);
    DDRH |= (1 << EN);

    motor_reset_encoder();
    motor_enable();
    motor_set_u(0);
}

void motor_enable(){
    MOTOR_CONFIG |= (1 << EN);
}


void motor_disable(){
    MOTOR_CONFIG &= ~(1 << EN);
}

void motor_set_direction(int dir){
    if (dir >= 0){
        MOTOR_CONFIG |= (1 << DIR);
    }
    else{
        MOTOR_CONFIG &= ~(1 << DIR);
    }
}

void motor_reset_encoder(){
    MOTOR_CONFIG &= ~(1 << RST);
    _delay_us(20);
    MOTOR_CONFIG |= (1 << RST);
}


int16_t motor_read_encoder(){
    MOTOR_CONFIG &= ~(1 << OE);
    MOTOR_CONFIG &= ~(1 << SEL);
    _delay_us(20);
    int16_t encoder = (MOTOR_ENC << 8);
    MOTOR_CONFIG |= (1 << SEL);
    _delay_us(20);
    encoder |= MOTOR_ENC;
    MOTOR_CONFIG |= (1 << OE);

    return (-encoder);
}

void motor_set_u(int16_t value){
    printf("value1 %d\r\n", value);
    value = value/129;
    uint8_t new_value;
    printf("value2 %d\r\n", value);
    if (value < -10){
        motor_set_direction(-1);
        value = -value;
        new_value = value;
    }
    else if(value > 10){
        motor_set_direction(1);
        new_value = value;
    }
    else{
        new_value = 0;
    }
    printf("speed %d\r\n", new_value);
    dac_send_analogue(new_value);
}

