
//#include "node1_USART.h"
//#include "node1_memory_map.h"
//#include <util/delay.h>
//#include "node1_joystick.h"
//#include "node1_slider.h"
//#include "node1_oled.h"

#include "node1_SRAM_test.h"
#include "menu.h"
#include "node1_CAN.h"


int main(void){
	USART_Init(MYUBRR);
	memory_map_init();
	SRAM_test();
	JOYSTICK joystick;
	SLIDER slider;



	DDRB &= ~(1 << PB1);
	//DDRB |= (1 << PB1);
	while (1) {	
	//printf("dd");

	printf("%x \n",(PINB & 0b00000010) >> 1);
	}
	return 0; 

}

