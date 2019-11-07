#ifndef GAME_H_
#define GAME_H_
#include "node1_CAN.h"


typedef struct player {
    char* name;
    int score;
} player;



uint8_t game_play(void);

uint8_t game_over(void);

void send_difficulty(uint8_t difficulty);

#endif