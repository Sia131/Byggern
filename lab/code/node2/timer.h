#ifndef TIMER_H
#define TIMER_H

/**********************************************
Timer module

Implements 2 timers for node 1 and 2. 

Utilizes defines.h such that the 
code can be reused by both nodes
without change. 

The functions implemented are:

	timer_init(uint8_t id, void (* function)())
	
		Initializes the timer
		
		id: The id of the timer to be 
			initialized. 
		
		function: Pointer to the 
			function which is called 
			by the timer. 
			
	timer_set_period(uint16_t ms, uint8_t id)
	
		Sets the period of the timer id, 
		with the period ms given in 
		milliseconds. 
		
	timer_start(uint8_t id)
	
		Starts the timer given by id. 
		
	timer_stop(uint8_t id)
	
		Stops the timer given by id. 

**********************************************/

void timer_init(uint8_t id, void (* function)() );

void timer_set_period(uint16_t ms, uint8_t id);

void timer_start(uint8_t id);

void timer_stop(uint8_t id);

#endif