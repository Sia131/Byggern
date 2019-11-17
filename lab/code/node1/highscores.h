

#include "node1_oled.h"

#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#define highscore_list_length = 5

int highscore_list = [highscore_list_length];

void show_highscores();

void update_highscores(int score);


#endif