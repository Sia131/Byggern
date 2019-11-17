#include "highscores.h"

void show_highscores(){
    oled_clear();
    oled_write_word("Highscores")
    for (int i = 0; i <  highscore_list_length; i++){
        oled_goto_pos(i,0);
        oled_write_word(highscore_list[i]);
}

void update_highscores(int score){
    for (int i = 0; i <  highscore_list_length; i++){
        if (score > highscore_list[i]) {
            highscore_list[i] = score;
            break;
        }
    }
}