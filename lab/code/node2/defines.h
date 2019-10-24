#ifndef DEFINES_H
#define DEFINES_H

#include <avr/io.h>

/******************************
Defines module

Defines all the general 
constants used in node 1 and 2. 

Gives ability to 
use reuse alot of the modules. 

******************************/

/******** NODE 1 *********/
#ifdef __AVR_ATmega162__

    /* generic */
    #define F_CPU 4915200UL

	
    /*SPI & MCP*/
    #define SPI_MOSI PB5
    #define SPI_MISO PB6
    #define SPI_SS PB4
    #define SPI_SCK PB7

	
    /*CAN*/
    #define INTRREG GICR
    #define INTRSEL INT0

    #define INTRSC  ISC11
    #define INTRSET MCUCR
    #define INTR_VECT INT0_vect

	
	/* TIMER */
	/* TIMER 1 */
	#define TIMER1_vector TIMER1_COMPA_vect
	#define TIMER1_CTRLA TCCR1A
	#define TIMER1_CTRLB TCCR1B
	#define TIMER1_TOP OCR1A
	#define TIMER1_REG TCNT1
	#define TIMER1_TIMSK TIMSK
	#define TIMER1_OCIE OCIE1A
	
	
	/* TIMER 2 */
	#define TIMER2_vector TIMER3_COMPA_vect
	#define TIMER2_CTRLA TCCR3A
	#define TIMER2_CTRLB TCCR3B
	#define TIMER2_TOP OCR3A
	#define TIMER2_REG TCNT3
	#define TIMER2_TIMSK ETIMSK
	#define TIMER2_OCIE OCIE3A


/******** NODE 2 *********/
#elif __AVR_ATmega2560__

    /* generic */
    
	
    /*SPI*/
    #define SPI_MOSI PB2
    #define SPI_MISO PB3
    #define SPI_SS PB7
    #define SPI_SCK PB1
    
	
    /*CAN*/
    #define INTRREG EIMSK
    #define INTRSEL INT2

    #define INTRSC  ISC01    
    #define INTRSET EICRB 
    #define INTR_VECT INT2_vect
	
	
	/* TIMER */
	/* TIMER 1 */
	#define TIMER1_vector TIMER1_COMPA_vect
	#define TIMER1_CTRLA TCCR1A
	#define TIMER1_CTRLB TCCR1B
	#define TIMER1_TOP OCR1A
	#define TIMER1_REG TCNT1
	#define TIMER1_TIMSK TIMSK1
	#define TIMER1_OCIE OCIE1A
	
	
	/* TIMER 2 */
	#define TIMER2_vector TIMER4_COMPA_vect
	#define TIMER2_CTRLA TCCR4A
	#define TIMER2_CTRLB TCCR4B
	#define TIMER2_TOP OCR4A
	#define TIMER2_REG TCNT4
	#define TIMER2_TIMSK TIMSK4
	#define TIMER2_OCIE OCIE4A
	
	
	/* MOTOR */
	#define MOTOR_DIR PH1
	#define MOTOR_SEL PH3
	#define MOTOR_EN  PH4
	#define MOTOR_OE  PH5
	#define MOTOR_RST PH6
	
	#define MOTOR_CONFIG  PORTH
	#define MOTOR_ENCODER PINK

		
	/* controller */
	#define SCALING_FACTOR 128 
	#define MAX_INT INT16_MAX
	#define MAX_LONG INT32_MAX
	#define MAX_I_TERM (MAX_LONG / 2)


	/* solenoid */
	#define SOLENOID_DDR  DDRE
	#define SOLENOID_PORT PORTE
	#define SOLENOID_PIN  PE4


#endif

/******** COMMON *********/


/**************************/
#endif