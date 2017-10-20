/*
 * main.c
 * Project: 8-channel LED driver
 * Created: 2016-10-25
 * Update : 2017-10-19 - code reorganization
 * Author : Kamil Bielowka
 * For proper working Atmega needs to be set at 8MHz clock
 
 */ 
#define F_CPU 8000000L



#include "led.h"	
#include "control.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

volatile uint8_t tclock;		//clock signal related to timer
volatile uint8_t ir_clock;
volatile uint8_t timeout; 
volatile uint8_t transmission=0;	//In this remote there are 3 long signals before data frame appears 
volatile uint8_t ir_data=0;
volatile uint8_t last_command;
volatile uint8_t counter;		//counts received bits
volatile uint8_t out_cycle[8];	// 0,1,2 - r,g,b; 3 - cold light; 4,5,6,7 - other, outputs for another lights
volatile uint8_t status=0x01;	//bit 0 - diodes output enable, bit 1 - programming mode enable 



int main(void)
{
	init();
    while (1) 
    {
		sleep_mode();
    }
}



/************************************************************************/
/* Interrupt counts time between falling edges and interprets it as     */
/*	"0" or "1"															*/
/************************************************************************/

SIGNAL(INT0_vect){
	if(counter<8+OFFSET){
	uint8_t ir_pulse_lenght=0;	
	timeout = MAX_TIMEOUT;	
	
	if(transmission>0){
	if (ir_clock<tclock) ir_pulse_lenght = tclock-ir_clock;
	else ir_pulse_lenght = (tclock+MAX_CYCLE)-ir_clock;		//difference in 0.1ms (pulse time = ir_pulse_length*0.1ms)
	}
	if (transmission>=3){			//after third long pulse start to receive data
		if ((ir_pulse_lenght>7)&&(ir_pulse_lenght<13)) 				//received "0"
		{
			if (transmission>=3+OFFSET)
			{
				ir_data=ir_data*2; 
			}
			else ++transmission; 
		}
		else if ((ir_pulse_lenght>16)&&(ir_pulse_lenght<24))		//received "1"
		{
			if (transmission>=3+OFFSET)
			{
				ir_data=(ir_data*2)+1;
			}
			else ++transmission;
		}
		++counter;
	}
	else if((transmission ==2)&&(ir_pulse_lenght>42)&&(ir_pulse_lenght<58)) transmission=3;		//
	else if((transmission ==1)&&(ir_pulse_lenght>80)&&(ir_pulse_lenght<100)) transmission=2;
	else if(transmission==0) transmission=1;		//first falling edge appears
	ir_clock = tclock;
	if (counter==8+OFFSET) control(&ir_data, &last_command, out_cycle, &status, &timeout);
	}
}



SIGNAL(TIMER0_OVF_vect){
	tclock++;
	TCNT0 = 156; //counts in 0.1ms
	if (timeout==0) 
	{
		counter=0; 
		ir_data=0; 
		transmission=0;
	}
		
	if ((tclock%50==0)&&(timeout>0)) --timeout;
	
	if ((status&0x01)==1)		//if led enable
	{
		PORTD|=(1<<DIODE_ON);
		for (int8_t i=0; i<=7; i++)			//PWM driver - controls LED intensity 
		{
			if (out_cycle[i]>tclock) CONTROL|=(1<<i);
			else CONTROL&=~(1<<i);
		}
	}
	else						// if led disable
	{
		PORTD=0x00;
		status=0;
		CONTROL=0x00;
	}
	if ((status&0x02)==0x02)	//programming mode enable
	 {
		PORTD=(1<<DIODE_PROG);
	}
	else
	{
		PORTD&=~(1<<DIODE_PROG);
	}
	
	if (tclock>MAX_CYCLE) tclock=0;
}