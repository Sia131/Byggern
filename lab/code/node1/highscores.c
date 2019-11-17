#include "highscores.h"
#include "menu.h"
#include <stdio.h>

#define highscore_list_length 5

 int highscore_list[highscore_list_length] = {0};


void show_highscores(menu_node_t* node){
    oled_clear();
    oled_write_word("");
    for (int i = 0; i <  highscore_list_length; i++) {
        oled_goto_pos(i,0);
        int point = highscore_list[i];
        char chr[3];
        itoa(point, chr,10); //convert int score to char 
        oled_write_word(chr);
    }
}

void update_highscores(int score){
    for (int i = 0; i <  highscore_list_length; i++) {
        if (score > highscore_list[i]) {
            highscore_list[i] = score;
            break;
        }
    }
}