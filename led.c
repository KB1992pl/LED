/*
 * led.c
 * Created: 19.10.2017
 * Author : Kamil Bielowka
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>
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
	TCCR0=0x02;			//timer divider: FCPU/8
	sei();
}


void light_decrease(uint8_t change, volatile uint8_t last_command, volatile uint8_t *out_cycle)
{
	if (change==1)
	{
		if (*(out_cycle+last_command) > 0) (*(out_cycle+last_command))--;
	}
	else
	{
		*(out_cycle+last_command) = 0;
	}
}


void light_increase(uint8_t change,  volatile uint8_t last_command, volatile uint8_t *out_cycle)
{
	if (change==1)
	{
		if (*(out_cycle+last_command)<=MAX_CYCLE) (*(out_cycle+last_command))++;
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