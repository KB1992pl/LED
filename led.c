/*
 * led.c
 * Created: 19.10.2017
 * Author : KB1992PL
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include "user_def.h"
#include "led.h"
#include "control.h"

void init(void)
{
	DDRC=0xff;
	PORTD=0x00;
	DDRB=0xff;
	PORTB=0x00;
	DDRD=0xfb;
	DDRC=0xff;

	MCUCR|=(1<<ISC01);	//falling egde interrupt
	GICR|=(1<<INT0);	//interrupt "INT0" enable
	TIMSK|=(1<<TOIE0);	//timer overflow interrupt enable
	#if (TIMER0_DIVIDER ==1)
	TCCR0=0x01;			
	#endif
	#if (TIMER0_DIVIDER ==8)
	TCCR0=0x02;			
	#endif
	#if (TIMER0_DIVIDER ==64)
	TCCR0=0x03;	
	#endif
	PORTD|=(1<<DIODE_ON);

}


void light_decrease(uint8_t change, volatile uint8_t last_command, volatile uint8_t *out_cycle)
{
	
	if (*(out_cycle+last_command)-change > 0) 
	{
		(*(out_cycle+last_command))-=change;
	}
	else
	{
		*(out_cycle+last_command) = 0;
	}
}


void light_increase(uint8_t change,  volatile uint8_t last_command, volatile uint8_t *out_cycle)
{
	
	if (*(out_cycle+last_command)+change<=MAX_CYCLE)
	{
		(*(out_cycle+last_command))+=change;
	}
	else
	{
		*(out_cycle+last_command)=MAX_CYCLE;
	}
}



void program_eeprom(uint8_t address,volatile uint8_t *cycles)
{
	cli();
	for (uint8_t i =0; i<=7;++i)
	{
		eeprom_busy_wait();
		eeprom_write_byte((uint8_t*) ((address*8 )+ i),*(cycles + i));
	}

	eeprom_busy_wait();
	sei();
}



void read_eeprom(uint8_t address, volatile uint8_t *cycles)
{
	cli();
	for (uint8_t i =0; i<=7;++i)
	{
		eeprom_busy_wait();
		*(cycles +i)=eeprom_read_byte((uint8_t*) ((address*8)+i));
	}

	eeprom_busy_wait();
	sei();
}
