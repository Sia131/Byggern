#include "node1_USART.h"
#include "node1_memory_map.h"
#include <util/delay.h>
#include "node1_joystick.h"
#include "node1_slider.h"
#include "node1_oled.h"

#ifndef NODE1_MENU_H_
#define NODE1_MENU_H_

typedef struct menu_node_t {
    char* name;
    struct menu_node_t* parent;
    struct menu_node_t* first_child;
    struct menu_node_t* head;
    struct menu_node_t* tail;
    struct menu_node_t* nxt;
    struct menu_node_t* prv;
    int num_siblings; //including the node itself == length of linked list
    void (*action)();
} menu_node_t;

// Prints the arrow used in menu
void menu_oled_print_arrow(uint8_t row, uint8_t col);

// Clears old arrow to allow new to be printed
void oled_clear_arrow(uint8_t row, uint8_t col);

// Prints the current page based on the current node linked list
void menu_print_page(menu_node_t* node);

// Initialises a menu node (constructor)
void menu_node_init(menu_node_t* node, char* name, int num_siblings, menu_node_t* parent,menu_node_t* first_child, menu_node_t* head, menu_node_t* tail, void* action);

// Creates all linked lists part of the menu
void menu_create_linked_list(void);

// Sets the current node and prints the main page
void menu_init(void);

// Called in a loop, where pointer moves
void menu_run(void);

// Plays the ping pong game
void menu_play(void);

// Sets 
void menu_send_difficulty(void);

void menu_play_mario(menu_node_t* node);

void menu_play_underworld(void);

#endif