#include "node2_solenoid.h"

#define  SOLENOID_DDR       DDRE
#define  SOLENOID_PORT      PORTE
#define  SOLENOID_PIN       PE4

//this is pin number 2 on arduino shield

static uint8_t solenoid_shot;
static uint8_t shoot = 0;

void solenoid_deactivate(){
    SOLENOID_PORT |= (1 << SOLENOID_PIN);
}

void solenoid_activate(){
    SOLENOID_PORT &= ~(1 << SOLENOID_PIN);
}


void solenoid_init(){
    /*set pin as output */
    SOLENOID_DDR |= (1 << SOLENOID_PIN);
    solenoid_shot = 0;
    solenoid_deactivate();
}

void solenoid_shoot(){
    solenoid_shot += 1;
    solenoid_activate();
    _delay_ms(75);
    solenoid_deactivate();
}

uint8_t solenoid_get_shot(){
    return solenoid_shot;
}

void solenoid_clear_shot(){
    solenoid_shot = 0;
}

void solenoid_update_shot(uint8_t value){
    if ((value == 1)&&(shoot == 0)){
        shoot = 1;
        solenoid_shoot();
    }
    if (value == 0){
        shoot = 0;
    }
}