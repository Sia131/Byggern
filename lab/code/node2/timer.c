#include "defines.h"
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"


static void (* timer1_function)(void);
static void (* timer2_function)(void);


void timer_init(uint8_t id, void (* function)() )
{
	cli();

	if (id == 1)
	{
		TIMER1_CTRLA = 0;
		TIMER1_CTRLB = (1 << WGM12);
		TIMER1_TIMSK |= (1 << TIMER1_OCIE);
		timer1_function = function;
	}
	else if (id == 2)
	{
		TIMER2_CTRLA = 0;
		TIMER2_CTRLB = (1 << WGM12);
		TIMER2_TIMSK |= (1 << TIMER2_OCIE);
		timer2_function = function;
	}
	else
	{
		printf("INVALID ID TIMER INIT\n");
		return;
	}
	
	sei();
	
    //top value
    timer_set_period(100, id);
}


void timer_set_period(uint16_t ms, uint8_t id)
{
	if (id == 1)
	{
		TIMER1_TOP = ms * 0.001 * F_CPU / (2 * 256) - 1;
	}
	else if (id == 2)
	{
		TIMER2_TOP = ms * 0.001 * F_CPU / (2 * 256) - 1;
	}
	else 
	{
		printf("INVALID ID TIMER SET PERIODE\n");
		return;
	}
}


void timer_start(uint8_t id)
{
	if (id == 1)
	{
		TIMER1_REG = 0;
		/* Prescale 256 */
		TIMER1_CTRLB |= (1 << CS12) | (0 << CS11) | (0 << CS10);
	}
	else if (id == 2)
	{
		TIMER2_REG = 0;
		/* Prescale 256 */
		TIMER2_CTRLB |= (1 << CS12) | (0 << CS11) | (0 << CS10);
	}
	else 
	{
		printf("INVALID ID TIMER START\n");
		return; 
	}
}


void timer_stop(uint8_t id)
{
	if (id == 1)
	{
		// turn off timer
		TIMER1_CTRLB &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
	}
	else if (id == 2)
	{
		// turn off timer
		TIMER2_CTRLB &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
	}
	else
	{
		printf("INVALID ID TIMER STOP\n");
		return;
	}
}



ISR(TIMER1_vector)
{
	timer1_function();
}

ISR(TIMER2_vector)
{
	timer2_function();
}
