#include "menu.h"
#include "game.h"
#include "node1_CAN.h"

uint8_t game_play(void) {
    oled_clear();
    oled_goto_pos(4,4);
    oled_print("Playing Ping Pong");
    JOYSTICK menu_joystick;
    while(1){
    get_joystick_values(&menu_joystick);
    input_com_send_data();
    /*if (can_interrupt() { //We need an interrupt to know when the game is over
            can_receive(&can_message);
            game_over();
            _delay_ms(2000);
            current_node = node_home;
            break;
        }
    }*/
}

uint8_t game_over(void) {
    oled_clear();
    oled_goto_pos(3,4);
    oled_print("Game over!");
    oled_goto_pos(4,4):
    oled_print("Check highscores to see if you made it!")
}


void send_difficulty(uint8_t difficulty){
    MESSAGE message;
    message.id = 0;
    message.length = 1;
    message.data[0] = difficulty;
    /*send the message over the can buss*/
    can_write(&message);
    current_node = node_home;
}