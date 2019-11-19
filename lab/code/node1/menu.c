

#include "node1_USART.h"
#include "node1_memory_map.h"
#include <util/delay.h>
#include "node1_joystick.h"
#include "node1_slider.h"
#include "node1_oled.h"
#include "menu.h"
#include "node1_CAN.h"
#include "node1_input_com.h"
#include "highscores.h"
#include <avr/pgmspace.h>
#include <avr/io.h>



static menu_node_t* node_home;
static menu_node_t* node_play_game;
static menu_node_t* node_highscores;
static menu_node_t* node_set_difficulty;
static menu_node_t* current_node;
static menu_node_t* node_playing;
static menu_node_t* node_easy_setting;
static menu_node_t* node_medium_setting;
static menu_node_t* node_hard_setting;
static menu_node_t* node_play_song;
static menu_node_t* node_show_highscores;

static int score;


const char play_pong_c[] PROGMEM = "Playing ping pong";
const char good_luck[] PROGMEM= " Good luck!";
const char setting_difficulty_c[] PROGMEM = " Setting difficulty ";
const char wait_c[] PROGMEM = " Please wait";



void oled_print_arrow(uint8_t row, uint8_t col){
    oled_goto_pos(row, col);
    oled_write_data(0b00011000);
    oled_write_data(0b00011000);
    oled_write_data(0b01111110);
    oled_write_data(0b00111100);
    oled_write_data(0b00011000);
}

void oled_clear_arrow(uint8_t row, uint8_t col){
    oled_goto_pos(row, col);
    for (int i = 0; i < 10; ++i){
        oled_write_data(0x00);
    }
}

void menu_node_init(menu_node_t* node, char* name, int num_siblings, menu_node_t* parent, menu_node_t* first_child, menu_node_t* head, menu_node_t* tail, void* action){
    node->name = name;
    node->num_siblings = num_siblings;
    node->parent = parent;   
    node->first_child = first_child;
    node->head = head;
    node->tail = tail;
    node->action = action;
}

void create_linked_list(){

    node_home = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_play_game = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_highscores = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_set_difficulty = (menu_node_t*) malloc(sizeof(menu_node_t));
    current_node = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_play_song = (menu_node_t*) malloc(sizeof(menu_node_t));


    node_easy_setting = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_medium_setting = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_hard_setting = (menu_node_t*) malloc(sizeof(menu_node_t));

    menu_node_init(node_play_game, "1. Play game", 4, node_home, NULL, node_play_game, node_play_song, &play);
    menu_node_init(node_highscores, "2. Highscores", 4, node_home, NULL, node_play_game, node_play_song, &print_highscores);
    menu_node_init(node_set_difficulty, "3. Set difficulty", 4, node_home, node_easy_setting, node_play_game, node_play_song, &print_menu);
    menu_node_init(node_play_song, "4. Play Song", 4, node_home, NULL,node_play_game,node_play_song, &play_song);

    menu_node_init(node_easy_setting, "1. Easy", 3, node_set_difficulty,NULL , node_easy_setting, node_hard_setting, &send_difficulty);
    menu_node_init(node_medium_setting, "2. Medium", 3, node_set_difficulty,NULL , node_easy_setting, node_hard_setting, &send_difficulty);
    menu_node_init(node_hard_setting, "3. Hard", 3, node_set_difficulty, NULL, node_easy_setting, node_hard_setting, &send_difficulty);

    node_play_game->nxt = node_highscores;
    node_play_game->prv = NULL;
    node_highscores->nxt = node_set_difficulty;
    node_highscores->prv = node_play_game;
    node_set_difficulty->nxt = node_play_song;
    node_set_difficulty->prv = node_highscores;
    node_play_song->nxt = NULL;
    node_play_song->prv = node_set_difficulty;

    node_easy_setting->nxt = node_medium_setting;
    node_easy_setting->prv = NULL;

    node_medium_setting->nxt = node_hard_setting;
    node_medium_setting->prv = node_easy_setting;

    node_hard_setting->nxt = NULL;
    node_hard_setting->prv = node_medium_setting;

    node_playing->nxt = NULL;
    node_playing->prv = NULL;
}

void print_menu(menu_node_t* node) {
    oled_clear();
    menu_node_t* curr_node = node->head;
    int line = 0;
    while (curr_node != node->tail) {
        oled_goto_pos(line,10);
        oled_write_word(curr_node->name);
        curr_node = curr_node->nxt;
        line++;
    }
    oled_goto_pos(line,10);
    oled_write_word(node->tail->name);
}

/*
menu_node_t update_menu(){
    get_joystick_values(&menu_joystick);
        if (menu_joystick.y_direction == UP) {
            if (joystick_pos == 0){
                joystick_pos = linked_list_len-1;
                current_node = current_node->tail;
            } else {
                (joystick_pos)--;
                current_node = current_node->prv;
            }
        }
        if (menu_joystick.y_direction == DOWN) {
            if (joystick_pos == linked_list_len-1){
                joystick_pos = 0;
                current_node = current_node->head;
            } else {
                (joystick_pos)++;
                current_node = current_node->nxt;
            }
        }
        if ((menu_joystick.x_direction == RIGHT) ){
            if (current_node->first_child != NULL){
                (*current_node->action)(current_node->first_child);
                current_node = current_node->first_child;
                joystick_pos = 0;
            } else if (current_node->first_child == NULL) {
                if (current_node == node_highscores){
                    print_highscores();   
                }
                if (current_node == node_play_game){
                    score = play(); //play until interrupt
                    printf("score: %d",score);
                    update_highscores(score);
                }
            }
        }
}*/

void menu_init(){
    create_linked_list();
    volatile int joystick_pos = 0;
    JOYSTICK menu_joystick;
    current_node = node_play_game;
    int linked_list_len = current_node->num_siblings;
    print_menu(node_play_game);
    //int* submenus = malloc(sizeof(menu_node_t));
	//printf("malloc (%d)\r\n", submenus);
    while(1){
        get_joystick_values(&menu_joystick);
        if (menu_joystick.y_direction == UP) {
            if (joystick_pos == 0){
                joystick_pos = linked_list_len-1;
                current_node = current_node->tail;
            } else {
                (joystick_pos)--;
                current_node = current_node->prv;
            }
        }
        if (menu_joystick.y_direction == DOWN) {
            if (joystick_pos == linked_list_len-1){
                joystick_pos = 0;
                current_node = current_node->head;
            } else {
                (joystick_pos)++;
                current_node = current_node->nxt;
            }
        }
        if ((menu_joystick.x_direction == RIGHT) ){
            if (current_node->first_child != NULL){
                (*current_node->action)(current_node->first_child);
                current_node = current_node->first_child;
                joystick_pos = 0;
            } else if (current_node->first_child == NULL) {
                if (current_node == node_highscores){
                    //printf("node highscore: %d ", score);
                    update_highscores(6);
                    print_highscores();   
                }
                /*if (current_node == node_play_game){
                    score = play(); //play until interrupt
                    printf("score: %d",score);
                    update_highscores(score);
                }*/
                else{
                (*current_node->action)();
                (*current_node->parent->action)(current_node->head);

                }
            }
        }
        if ((menu_joystick.x_direction == LEFT) && (current_node->parent != NULL)){
            current_node = current_node->parent;
            (*current_node->action)(current_node);
            joystick_pos = 0;
        }
        linked_list_len = current_node->num_siblings;
        joystick_pos = abs(joystick_pos % linked_list_len);

        printf("pos %d\t", joystick_pos);
        printf("node is at %s\n", current_node->name);
        oled_print_arrow(joystick_pos,0);

        uint8_t neutral = 50;
        int diff = abs(((int)neutral - (int)menu_joystick.y_analog)/5);
        int delay_time = (1000/(diff+1));
        //printf("speed: %d\n", delay_time);
        if (diff > 1) {
            for (int i = 0; i < delay_time; i++) {
                _delay_ms(1);
            }
        } else  {
            _delay_ms(250);
        }
        oled_clear_arrow(joystick_pos,0);

    }
}

void send_difficulty(){ //fix
    int difficulty = 0;
    if (current_node == node_easy_setting){
        difficulty = 0;
    }
   if (current_node == node_medium_setting){
        difficulty = 1;
    }
    if (current_node == node_hard_setting){
        difficulty = 2;
    }    
    oled_clear();
    oled_goto_pos(3,0);
    oled_goto_line(3);
    oled_print_pgm(setting_difficulty_c);
    _delay_ms(1000);
    oled_clear();
    MESSAGE message;
    message.id = 30;
    message.length = 1;
    message.data[0] = difficulty;
    can_write(&message);
    _delay_ms(1000);
}


int play() {
    oled_clear();
    oled_goto_pos(4,4);
    _delay_ms(1000);
    //oled_write_word("Playing");	
    oled_print_pgm(play_pong_c);
    while(1){
        input_com_send_data();
        MESSAGE can_message;
        if (get_received()) {
            MESSAGE can_message_received;
            can_receive(&can_message_received);
            score = can_message_received.data[0];
            printf("score %d\r\n", score);
            update_highscores(score);
            _delay_ms(500);
            //game_finished();
            //current_node = current_node->parent;
            break;
        }
    }
}


void play_song(menu_node_t* node){
    MESSAGE msg;
    msg.id = 40;
    msg.length = 1;
    msg.data[0] = 4;
    can_write(&msg);
    _delay_ms(5000);
}

void game_finished(){
    oled_clear();
    oled_goto_pos(3,4);
    /*oled_write_word("Game over!");
    oled_goto_pos(4,4);
    oled_write_word("Check hk");
	int* submenus = malloc(sizeof(menu_node_t));
	printf("malloc (%d)\r\n", submenus);
    oled_goto_pos(5,4);
    oled_write_word("to see if you made it");
    MESSAGE can_message;
    can_receive(&can_message);10
    if (can_message.id == 1) {
        int score = can_message.data[0];
        update_highscores(score);
        printf("score: %d", score);
        current_node = node_home;
    }*/
}