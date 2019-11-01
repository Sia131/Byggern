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


uint16_t motor_read_encoder(){
    MOTOR_CONFIG &= ~(1 << OE);
    MOTOR_CONFIG &= ~(1 << SEL);
    _delay_us(20);
    int16_t enoder = (MOTOR_ENC << 8);
    MOTOR_CONFIG |= (1 << SEL);
    _delay_us(20);
    enoder |= MOTOR_ENC;
    MOTOR_CONFIG |= (1 << OE);
}

void motor_set_u(uint8_t value, int dir){
    motor_set_direction(dir);
    dac_send_analogue(value);
}


uint8_t right_slider_remapping(USER_DATA *user_data){
    int slider = user_data->right_analog;
    if (slider > 50){
        slider = slider - 50;
        return (uint8_t)(5.1 * slider);
    }
    else{
        slider = slider - 50;
        slider = slider * (-1);
        return (uint8_t)(5.1 * slider);
    }
}


void joystick_to_u(USER_DATA *user_data){
    int slider = user_data->right_analog;
    uint8_t new_slider = right_slider_remapping(user_data);
    if (slider > 50){
        motor_set_u(new_slider, 1);
    }
    else{
        motor_set_u(new_slider, -1);
    }
}
