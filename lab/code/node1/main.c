
#include "node1_USART.h"
#include "node1_memory_map.h"
#include <util/delay.h>
#include "node1_joystick.h"
#include "node1_slider.h"
#include "node1_oled.h"
#include <stdint.h>

#include "node1_SRAM_test.h"
#include "menu.h"
#include "node1_CAN.h"
#include "node1_input_com.h"
#include "highscores.h"
#include <avr/pgmspace.h>

    const char tester[] PROGMEM = "testing";

int main(void){
    //oled_clear();
    //oled_goto_pos(0,0);
	//oled_print_pgm(tester);
    //oled_write_word("hei");
	USART_Init(MYUBRR);
	memory_map_init();
	can_init();
	oled_init();
    /*for (int i = 0; 15i <  highscore_list_length; i++) {
        int point = highscore_list[i];
        char chr[3];
        itoa(point, chr,10); //convert int score to char 
        printf("score is %s",chr);
    }*/
    menu_init(); //main  loop inside here
	/*can_receive(&can_message);
	printf("can id; %d  can message %d  \r\n", can_message.id, can_message.data[0]);
	
	while(get_received()==0){
		can_message.length = 1;
		can_message.id = 50;
		can_write(&can_message);
	}
	
	can_receive(&can_message);
	printf("can id; %d  can message %d  \r\n", can_message.id, can_message.data[0]);

	printf("nothing");*/
	return 0; 

}

