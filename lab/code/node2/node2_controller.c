#include "node2_controller.h"


void controller_init(int16_t K_p,int16_t K_i,int16_t K_d){
    ctrl.K_p = K_p;
    ctrl.K_i = K_i;
    ctrl.K_d = K_d;

    ctrl.r = 0;
    ctrl.sumE = 0;
    ctrl.prev_error = 0;

    ctrl.maxE = MAX_INT / (ctrl.K_p + 1);
    ctrl.maxSumE = MAX_I_TERM / (ctrl.K_i + 1);

    ctrl.speed = 50;
}

int16_t slider_to_encoder(int value){
    return 85.94 * value;
}


void controller_set_reference(int16_t r){
    r = slider_to_encoder(r);
    ctrl.r = r;
}

void reset_integrator(){
    ctrl.sumE = 0;
}

int16_t controller_get_reference(){
    return ctrl.r;
}



void controller_update(){
    int16_t error,p,d;
    int32_t i, u, temp;

    int16_t measurment = - motor_read_encoder();
    error = ctrl.r - measurment;
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

    printf("%d \r\n", ctrl.sumE);
    


    u = p + i;

    
    if (u > MAX_INT){
        u = MAX_INT;
    }
    if (u < -MAX_INT){
        u = -MAX_INT;
    }

    //printf("%d \r\n", u);
    //motor_set_u((int16_t)u);
    
}
