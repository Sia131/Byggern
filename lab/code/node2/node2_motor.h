#ifndef NDOE2_MOTOR_H
#define NDOE2_MOTOR_H
#include "node2_dac.h"
#include "node2_input_com.h"



#define MOTOR_CONFIG            PORTH
#define MOTOR_ENC               PINK

#define DIR                     PH1
#define SEL                     PH3
#define EN                      PH4
#define OE                      PH5
#define RST                     PH6

/*initalizes MJ1 port and MJ2 port*/
void motor_init();

/*enables motor*/
void motor_enable();

/*disables motor */
void motor_disable();

/*sets the direction of the motor*/
void motor_set_direction(int dir);

/*sets the actuator input value to motor*/
void motor_set_u(uint8_t value, int dir);

/*reads the encoder value*/
uint16_t motor_read_encoder();

/*resets the encoder*/
void motor_reset_encoder();

/*remaps slider from 0 to 100, over to -255 to 255*/
uint8_t right_slider_remapping(USER_DATA *user_data);

void joystick_to_u(USER_DATA *user_data);




#endif