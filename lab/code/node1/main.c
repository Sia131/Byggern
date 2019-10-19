/*
 * node1.c
 *
 * Created: 09.07.2019 03:43:54
 *  Author: siawashn
 */ 
#include "node1_USART.h"
#include "node1_memory_map.h"
#include <util/delay.h>
//#include "node1_SRAM_test.h"
#include "node1_joystick.h"
#include "node1_slider.h"
#include "node1_oled.h"
#include "menu.h"
#include "node1_CAN.h"

int main(void){

	USART_Init(MYUBRR);
	memory_map_init();
	can_init();
	
	MESSAGE message; 
	message.id = 1;
	message.length = 3;
	message.data = "hei"
	can_write(&message); // Sender melding Mottar melding
	
	MESSAGE* receive = can_receive();
	printf("Id: %d \r\n", receive->id);
	printf("Lengde: %d \r\n", receive->length);
	printf("Melding: %s \r\n\r\n", receive->data);
	
	DDRB |= (1 << PB1); //set as output

	while (1) {	
		PORTB |= (1 << PB1);
		//printf("ashwhole\n");
	}
	
	return 0; 

}



