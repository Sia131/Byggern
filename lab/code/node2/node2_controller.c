#include "node2_controller.h"
#include <util/delay.h>

void controller_init(int16_t K_p,int16_t K_i,int16_t K_d){
    motor_init();
    ctrl.K_p = K_p;
    ctrl.K_i = K_i;
    ctrl.K_d = K_d;

    ctrl.r = 0;
    ctrl.sumE = 0;
    ctrl.prev_error = 0;

    ctrl.maxE = MAX_INT / (ctrl.K_p + 1);
    ctrl.maxSumE = MAX_I_TERM / (ctrl.K_i + 1);
/*
    for (int i =0; i < 400; i++){
        motor_set_u(-50);
        _delay_ms(1);
    } */
}

/*takes value from zero to hundred*/
void controller_set_reference(int16_t r){
    int16_t value = 85.94 * r;
    ctrl.r = value;
}

int16_t controller_get_reference(){
    return ctrl.r;
}

void reset_integrator(){
    ctrl.sumE = 0;
}


void controller_update(){
    int16_t error,p,d;
    int32_t i, u, temp;

    int16_t measurement =  motor_read_encoder();
    error = ctrl.r - measurement;
    //printf("%d \r\n", error);

    //proportional term
    if(error > ctrl.maxE){
        p = MAX_INT;
    }
    else if(error < -ctrl.maxE){
        p = - MAX_INT;
    }
    else {
        p = ctrl.K_p * error;
    }
    //intergral term 
    
    temp = ctrl.sumE + error;
    
    if (temp > ctrl.maxSumE){
        ctrl.sumE = ctrl.maxSumE;
        i = MAX_I_TERM;
    }
    else if(temp < -ctrl.maxSumE){
        ctrl.sumE = -ctrl.maxSumE;
        i = -MAX_I_TERM;
    }
    else{
        ctrl.sumE = temp;
        i = ctrl.K_i * ctrl.sumE;
    }
    
  
    d = ctrl.K_d * (error - ctrl.prev_error);
    ctrl.prev_error = error;
    u = p + i + d;
    
    if (u > MAX_INT){
        u = MAX_INT;
    }
    if (u < -MAX_INT){
        u = -MAX_INT;
    }
    printf("%d \r\n",u);
    motor_set_u((int16_t)u);
    //_delay_ms(100);
}


void controller_difficulty(uint8_t difficulty){
    if (difficulty = 0){ //easy
        controller_init(3,0,12);
    }
    if (difficulty = 1){ //medium
        controller_init(8,0,4);
    }
    if (difficulty = 2){ //hard
        controller_init(10,0,10);
    }
    
}
