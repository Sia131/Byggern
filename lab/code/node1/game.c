#include "menu.h"
#include "game.h"
#include "node1_CAN.h"


uint8_t game_play(void) {
    oled_clear();
    oled_goto_pos(4,4);
    oled_print("Playing Ping Pong");
    MESSAGE state; 
    state.length = 4;
    state.id = 10; //This is the id for states siawash
    state.data[] = "play";
    can_write(*state);
}

uint8_t game_over(void) {
    oled_clear();
    oled_goto_pos(3,4);
    oled_print("Game over!");
    oled_goto_pos(4,4):
    oled_print("Check highscores to see if you made it!")
}


void send_difficulty(uint8_t difficulty);