/*
 * user_def.h
 *
 * Created: 02.11.2017 22:13:42
 *  Author: KB1992PL
 */ 


#ifndef USER_DEF_H_
#define USER_DEF_H_

/****** parameters to change ******/
#define F_CPU 8000000L		//clock frequency
#define TIMER_CYCLE 100		//in us
#define CHANNELS_ENABLED 4	
#define TIMEOUT_MS 30		//time between receiving two data frames from remote IR
#define MAX_CYCLE 150		// "steps" of PWM
#define TIMER0_DIVIDER 8	//values to use: 1, 8, 64


/****** Atmega port assignment ******/

#define CONTROL PORTB //selection of the control port of the diodes
#define DIODE_RED	 0
#define DIODE_GREEN	 1
#define DIODE_BLUE	 2
#define DIODE_YELLOW 3
#define DIODE_A 4
#define DIODE_B 5
#define DIODE_C 6
#define DIODE_X 7
#define DIODE_ON 0		//PORTD
#define DIODE_PROG 1	//PORTD

/****** END parameters to change *****/
#define OFFSET 4		//count of ignored data bits - the same for all commands
#define TIMER0_REGISTER 255-((F_CPU*TIMER_CYCLE)/(TIMER0_DIVIDER*1000000L))
#define PULSE_WIDTH_0_MIN 700/TIMER_CYCLE	//700us
#define PULSE_WIDTH_0_MAX 1300/TIMER_CYCLE	//1300us
#define PULSE_WIDTH_1_MIN 1600/TIMER_CYCLE	//1600us
#define PULSE_WIDTH_1_MAX 2400/TIMER_CYCLE	//2400us
#define PULSE_TRANSMISSION_1_MIN 8000/TIMER_CYCLE
#define PULSE_TRANSMISSION_1_MAX 10000/TIMER_CYCLE
#define PULSE_TRANSMISSION_2_MIN 4200/TIMER_CYCLE
#define PULSE_TRANSMISSION_2_MAX 5800/TIMER_CYCLE
#define PWM_CYCLE TIMER_CYCLE*MAX_CYCLE
#define MAX_TIMEOUT (TIMEOUT_MS*1000L)/(TIMER_CYCLE*MAX_CYCLE)


#if (PWM_CYCLE>15000)
#warning "Low frequency - light could damage seeing"
#endif

#if (TIMER0_REGISTER<0)
#error "Timer register <0 - please check TIMER_CYCLE and TIMER0_DIVIDER"
#endif

#if (TIMER1_REGISTER<0)
#error "Timer register <0 - please check TIMER1_CYCLE and TIMER1_DIVIDER"
#endif

#if (CHANNELS_ENABLED >8)
#error "There are only 8 channels"
#endif

#if (CHANNELS_ENABLED < 1)
#error "You have to enable at least one channel"
#endif

#if (PULSE_TRANSMISSION_1_MAX >255)
#error "Too small TIMER_CYCLE value"
#endif

#if (MAX_TIMEOUT >255)
#error "Too large TIMEOUT_MS"
#endif


#endif /* USER_DEF_H_ */