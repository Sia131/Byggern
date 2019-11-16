
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

int main(void){
	
	
	USART_Init(MYUBRR);
	memory_map_init();
	oled_init();
	can_init();
	//menu_init(); //main  loop inside here

	MESSAGE can_message;
	/*
	while (get_received()==0){
		input_com_send_data();
		_delay_ms(10);
	}
	can_receive(&can_message);
	printf("can id; %d  can message %d  \r\n", can_message.id, can_message.data[0]);
	*/
	while(get_received()==0){
		can_message.length = 1;
		can_message.id = 50;
		can_write(&can_message);
	}
	
	can_receive(&can_message);
	printf("can id; %d  can message %d  \r\n", can_message.id, can_message.data[0]);

	printf("nothing");
	return 0; 

}

