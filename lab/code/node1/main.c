
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
	can_init();

	

	
	MESSAGE message = {
		1,
		5,
		"heiii"
	};

	can_write(&message); // Sender melding Mottar melding
	
	MESSAGE receive = {
		2,
		3,
		"lool",
	};

	
	can_receive(& receive);

	
	printf("Id: %d \n", receive.id);
	printf("Lengde: %d \r\n", receive.length);
	printf("Melding: %s \r\n\r\n", receive.data);
	
	
	
	while (1) {	
	}
	
	return 0; 

}

