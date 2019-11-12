

#include "node1_USART.h"
#include "node1_memory_map.h"
#include <util/delay.h>
#include "node1_joystick.h"
#include "node1_slider.h"
#include "node1_oled.h"
#include "menu.h"
#include "node1_CAN.h"
#include "node1_input_com.h"

static menu_node_t* node_home;
static menu_node_t* node_exit;
static menu_node_t* node_play_game;
static menu_node_t* node_playing;

static menu_node_t* node_highscores;
static menu_node_t* node_set_difficulty;
static menu_node_t* current_node;

static menu_node_t* node_easy_setting;
static menu_node_t* node_medium_setting;
static menu_node_t* node_hard_setting;
static menu_node_t* node_send_difficulty;
static menu_node_t* node_song;



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
    node_exit = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_play_game = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_highscores = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_set_difficulty = (menu_node_t*) malloc(sizeof(menu_node_t));
    current_node = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_playing = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_song = (menu_node_t*) malloc(sizeof(menu_node_t));

    node_send_difficulty = (menu_node_t*) malloc(sizeof(menu_node_t));


    node_easy_setting = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_medium_setting = (menu_node_t*) malloc(sizeof(menu_node_t));
    node_hard_setting = (menu_node_t*) malloc(sizeof(menu_node_t));
/*
    menu_node_init(node_home, "1. Enter Main Menu", 2, NULL, node_play_game, node_home, node_exit, &print_menu);
    menu_node_init(node_exit, "2. Exit", 2, NULL, NULL, node_home, node_exit, NULL);
*/
    menu_node_init(node_play_game, "1. Play Game", 3, node_home, node_playing, node_play_game, node_set_difficulty, &play);
    menu_node_init(node_highscores, "2. Highscores", 3, node_home, node_playing, node_play_game, node_set_difficulty, &play_song);
    menu_node_init(node_set_difficulty, "3. Set difficulty", 3, node_home, node_easy_setting, node_play_game, node_set_difficulty, &print_menu);
    //menu_node_init(node_playing, "Playing Game",1,node_play_game,NULL,NULL,NULL, &play);
    //menu_node_init(node_song, "Playing song",1,node_highscores,NULL,NULL,NULL, &play_song);
    menu_node_init(node_send_difficulty, "Send difficulty",1,node_set_difficulty,NULL,NULL,NULL, &send_difficulty);

    menu_node_init(node_easy_setting, "1. Easy", 3, node_set_difficulty, node_easy_setting, node_easy_setting, node_hard_setting, &send_difficulty);
    menu_node_init(node_medium_setting, "2. Medium", 3, node_set_difficulty, node_easy_setting, node_easy_setting, node_hard_setting, &send_difficulty);
    menu_node_init(node_hard_setting, "3. Hard", 3, node_set_difficulty, node_easy_setting, node_easy_setting, node_hard_setting, &send_difficulty);

    //Create linked lists
    /*
    node_home->nxt = node_exit;
    node_home->prv = NULL;
    node_exit->nxt = NULL;
    node_exit->prv = node_home;
*/        printf("node is at %s\n", current_node->name);

    node_play_game->nxt = node_        printf("node is at %s\n", current_node->name);
highscores;
    node_play_game->prv = NULL;        printf("node is at %s\n", current_node->name);

    node_highscores->nxt = node        printf("node is at %s\n", current_node->name);
_set_difficulty;
    node_highscores->prv = node_play_game;
    node_set_difficulty->nxt = NULL;
    node_set_difficulty->prv = node_highscores;

    node_easy_setting->nxt = node_medium_setting;play_underworld
    node_easy_setting->prv = NULL;play_underworld
play_underworld
    node_medium_setting->nxt = node_hard_setting;play_underworld
    node_medium_setting->prv = node_easy_setting;play_underworld
play_underworld
    node_hard_setting->nxt = NULL;play_underworld
    node_hard_setting->prv = node_medium_setting;play_underworld
play_underworld
    node_playing->nxt = NULL;
    node_playing->prv = NULL;


    //current_node 

}

void print_loading_screen() {
    oled_goto_pos(3,0);
	for (int i = 0; i < 6; i++) {
    	char word[] = " Welcome to this session ";
        char wait[] = " Please wait.";
        char wait2[] = " Please wait..";
        char wait3[] = " Please wait...";
        char* wait_list[3];
        wait_list[0] = wait;
        wait_list[1] = wait2;
        wait_list[2] = wait3;

        oled_goto_line(3);
	    oled_write_word(word);	
        oled_goto_pos(4,0);
        oled_write_word(wait_list[i%3]);

	    _delay_ms(1000);
        oled_clear_line(4);
	}
    oled_clear();
    
    oled_goto_pos(3,0);
    char word[] = "Use the Joystick";
    char word2[] = "to navigate through the menu";
    oled_write_word(word);	
    oled_goto_pos(4,0);
    oled_write_word(word2);
    _delay_ms(3000);


    oled_clear();
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

void menu_init(){
    create_linked_list();
    volatile int joystick_pos = 0;
    JOYSTICK menu_joystick;
    current_node = node_play_game;
    int linked_list_len = current_node->num_siblings;
    print_menu(node_play_game);
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
            } else if (current_node->first_child == NULL){
                (*current_node->action)();
            }          


            _delay_ms(100);
        }
        if ((menu_joystick.x_direction == LEFT) && (current_node->parent != NULL)){
            current_node = current_node->parent;
            (*current_node->action)(current_node);
            joystick_pos = 0;
        }        printf("node is at %s\n", current_node->name);

        linked_list        printf("node is at %s\n", current_node->name);
_len = current_node->num_siblings;
        joystick_po        printf("node is at %s\n", current_node->name);
s = abs(joystick_pos % linked_list_len);
        printf("node is at %s\n", current_node->name);

        printf("pos %d\t", joystick_pos);
        printf("node is at %s\n", current_node->name);
        //printf("parent: %s\n", current_node->parent);
        oled_print_arrow(joystick_pos,0);

        uint8_t neutral = 50;
        int diff = abs(((int)neutral - (int)menu_joystick.y_analog)/5);
        int delay_time = (1000/(diff+1));
        printf("speed: %d\n", delay_time);
        if (diff > 1) {
            for (int i = 0; i < delay_time; i++) {
                _delay_ms(1);
            }
        } else  {
            _delay_ms(200);
        }
        oled_clear_arrow(joystick_pos,0);

    }
}

void send_difficulty(menu_node_t* node){ //not currently working
    int difficulty = 0;
    if (current_node->name == "1. Easy"){
        int difficulty = 4;
    }
    if (current_node->name == "2. Medium"){
        int difficulty = 1;
    }
    if (current_node->name == "3. Hard"){
        int difficulty = 2;
    }
    printf("difficulty set to: %d", difficulty);
    
    oled_clear();
    oled_goto_pos(3,0);
	for (int i = 0; i < 3; i++) {
    	char word[] = " Setting difficulty ";
        char wait[] = " Please wait.";
        char wait2[] = " Please wait..";
        char wait3[] = " Please wait...";
        char* wait_list[3];
        wait_list[0] = wait;
        wait_list[1] = wait2;
        wait_list[2] = wait3;

        oled_goto_line(3);
	    oled_write_word(word);	
        oled_goto_pos(4,0);
        oled_write_word(wait_list[i%3]);

	    _delay_ms(1000);
        oled_clear_line(4);
	}
    oled_clear();
    current_node = node->parent->parent;
    print_menu(node_play_game);
    _delay_ms(500);
    /*send the message over the can buss
    MESSAGE message;
    message.id = 0;
    message.length = 1;
    message.data[0] = difficulty;
    //printf("nodename: %s\r\n", current_node->name);
    */
    //can_write(&message);
}



void play(menu_node_t* node) {
    printf("Playing ping pong\n");
    oled_clear();
    oled_goto_pos(4,4);
    //play_song();
    for (int i = 0; i < 3; i++) {
    	char word[] = " Good luck!";
        char wait[] = " Please wait.";
        char wait2[] = " Please wait..";
        char wait3[] = " Please wait...";
        char* wait_list[3];
        wait_list[0] = wait;
        wait_list[1] = wait2;
        wait_list[2] = wait3;

        oled_goto_line(3);
	    oled_write_word(word);	
        oled_goto_pos(4,0);
        oled_write_word(wait_list[i%3]);

	    _delay_ms(1000);
        oled_clear_line(4);
	}
    oled_clear();
    oled_goto_pos(3,0);
    oled_write_word("Playing Ping Pong");
    //JOYSTICK game_joystick;
    while(1){
        //get_joystick_values(&game_joystick);
        input_com_send_data();
    /*if (can_interrupt() { //We need an interrupt to know when the game is over
            can_receive(&can_message);
            game_over();
            _delay_ms(2000);
            current_node = node_home;
            break;
    }*/
    }
}


void play_song(menu_node_t* node){
    MESSAGE msg;
    msg.id = 2;
    msg.length = 1;
    msg.data[0] = 4;
    can_write(&msg);
    current_node = current_node->parent;
    _delay_ms(5000);
}

void game_finished(){
    /*
    oled_clear();
    oled_goto_pos(3,4);
    oled_write_word("Game over!");
    oled_goto_pos(4,4);
    oled_write_word("Check highscores to see if you made it!");*/
}