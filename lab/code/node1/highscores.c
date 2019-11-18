#include "highscores.h"
#include "menu.h"
#include <stdio.h>    
#include <util/delay.h>

#define highscore_list_length 5

static int highscore_list[highscore_list_length] = {0};


void print_highscores() {
    
    oled_clear();
    oled_write_word("");
    printf("printing highscore");
    for (int i = 0; i <  highscore_list_length; i++) {
        oled_goto_pos(i,10);
        int point = highscore_list[i];
        printf("score1 %d\r\n", point);
        char chr[3];
        itoa(point, chr,10); //convert int score to char 
        printf("score is %s",chr);
        oled_write_word(chr);
    }
}

void update_highscores(int score){
    highscore_list[0] = score;
    
    printf("inside update");
    for (int i = 0; i <  highscore_list_length; i++) {
        if (score > highscore_list[i]) {
            printf("replacing highscore");
            highscore_list[i] = score;
            printf("from high: %d, %d",highscore_list[i], i);
            break;
        }
    }
    
}