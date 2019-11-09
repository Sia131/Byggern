
//#include "node1_USART.h"
//#include "node1_memory_map.h"
//#include <util/delay.h>
//#include "node1_joystick.h"
//#include "node1_slider.h"
//#include "node1_oled.h"

#include "node1_SRAM_test.h"
#include "menu.h"
#include "node1_CAN.h"
#include "node1_input_com.h"
#include "sound.h"

int main(void){
	USART_Init(MYUBRR);
	memory_map_init();
	oled_init();
	JOYSTICK joystick;
	menu_init();
	can_init();

	while (1) {
		
		//input_com_send_data();
		//_delay_ms(20);
			
	//get_joystick_values(&joystick);
	//printf("%5d \r\n", joystick.x_analog);
	

	//pwm_set_ms(10);
	
	}
	return 0; 

}

