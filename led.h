/*
 * led.h
 * Created: 19.10.2017
 * Author : KB1992PL
 *
 * Functions to control PWM and programming mode
 */ 


#ifndef LED_H_
#define LED_H_



#include <avr/io.h>



void init(void);
void light_decrease(uint8_t change,  volatile uint8_t last_command,volatile uint8_t *out_cycle);
void light_increase(uint8_t change,  volatile uint8_t last_command,volatile uint8_t *out_cycle); 
void read_eeprom(uint8_t adress,volatile uint8_t *cycles);		//reads PWM cycles (intensity) from eeprom
void program_eeprom(uint8_t adress, volatile uint8_t *cycles);	//write PWM cycles (intensity) to eeprom

#endif
