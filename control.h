/*
 * control.h
 *
 * Created: 19.10.2017 17:15:48
 *  Author: KB1992PL
 *
 * Function which gets ir data and runs other functions to control programming mode, PWM, etc.
 */ 

#ifndef CONTROL_H_
#define CONTROL_H_

#include "led.h"


/*** decoded data frames from remote control (using logic analyzer) ***/
#define RED		 0b10101010
#define GREEN	 0b01101010
#define BLUE	 0b00011010
#define YELLOW	 0b11101010
#define VOL_UP	 0b01010000
#define VOL_DOWN 0b11010000
#define OFF		 0b01111000
#define UP		 0b10011010
#define DOWN	 0b01011010
#define OK		 0b00101000
#define A		 0b00001010
#define B		 0b10001010
#define C		 0b01001010
#define X		 0b11001010
#define PROG_1	 0b00000000
#define PROG_2	 0b10000000
#define PROG_3	 0b01000000
#define PROG_4	 0b11000000
#define PROG_5	 0b00100000
#define PROG_6	 0b10100000
#define PROG_7	 0b01100000
#define PROG_8	 0b11100000
#define PROG_9	 0b00010000
#define PROG_0	 0b10010000
#define TIMER_BUTTON 0b11101100
#define PG_PLUS		0b00111010
#define PG_MINUS	0b11011010
/***/




void control(volatile uint8_t *ir_data, volatile uint8_t *last_command, volatile uint8_t *out_cycle, volatile uint8_t *status, volatile uint8_t *timeout);


#endif
