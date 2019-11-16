#ifndef NODDE2_CONTROLLER_H
#define NODDE2_CONTROLLER_H

#include "node2_motor.h"
#include "node2_input_com.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#define SCALING_FACTOR 129
#define MAX_INT INT16_MAX
#define MAX_LONG INT32_MAX
#define MAX_I_TERM (MAX_LONG)/2

typedef struct CONTROLLER_DATA{
    int16_t r;
    int16_t prev_error;
    int32_t sumE;
    int16_t K_p;
    int16_t K_i;
    int16_t K_d;
    int16_t maxE;
    int32_t maxSumE;
}CONTROLLER_DATA;

static CONTROLLER_DATA ctrl;

/*Initializes the controlelr with PID constants*/
void controller_init(int16_t K_p,int16_t K_i,int16_t K_d);

/*sets the reference of the controller */
void controller_set_reference(int16_t r);

/*return the refernece value */
int16_t controller_get_reference();

/*resets the integrator*/
void reset_integrator();

/*updates the controller */
void controller_update();

/* sets the difficulty and initializes the controller */
void controller_difficulty(uint8_t difficulty);

void timer4_init();

void timer4_set_period(uint16_t ms);

void timer4_start();

void timer4_stop();

uint8_t get_received();

#endif