/*
 * control.c
 *
 * Created: 19.10.2017 17:15:34
 *  Author: Kamil Bielowka
 */ 

#include "led.h"
#include "control.h"

void control(volatile uint8_t *ir_data, volatile uint8_t *last_command, volatile uint8_t *out_cycle, volatile uint8_t *status, volatile uint8_t *timeout){
	switch (*ir_data)
	{
		case RED:
		*last_command=0;
		break;
		
		case GREEN:
		*last_command=1;
		break;
		
		case BLUE:
		*last_command=2;
		break;
		
		case YELLOW:
		*last_command = 3;
		break;
		
		case A:
		*last_command = 4;
		break;
		
		case B:
		*last_command = 5;
		break;
		
		case C:
		*last_command = 6;
		break;
		
		case X:
		*last_command = 7;
		break;
		
		case VOL_DOWN:
		light_decrease(1, *last_command, out_cycle);
		break;
		
		case VOL_UP:
		light_increase(1, *last_command, out_cycle); 
		break;
		
		case DOWN:
		light_decrease(2, *last_command, out_cycle);
		break;
		
		case UP:
		light_increase(2, *last_command, out_cycle);
		break;
		
		case OK:
		*status|=0x02;
		break;
		
		case OFF:
		*status^=0x01;
		*timeout=MAX_TIMEOUT*3;
		break;
		
		case PROG_0:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(0,out_cycle);
			*status-=2;
		}
		else read_eeprom(0,out_cycle);
		break;
		
		case PROG_1:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(1,out_cycle);
			*status-=2;
		}
		else read_eeprom(1,out_cycle);
		break;
		
		case PROG_2:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(2,out_cycle);
			*status-=2;
		}
		else read_eeprom(2,out_cycle);
		break;
		
		case PROG_3:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(3,out_cycle);
			*status-=2;
		}
		else read_eeprom(3,out_cycle);
		break;
		
		case PROG_4:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(4,out_cycle);
			*status-=2;
		}
		else read_eeprom(4,out_cycle);
		break;
		
		case PROG_5:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(5,out_cycle);
			*status-=2;
		}
		else read_eeprom(5,out_cycle);
		break;
		
		case PROG_6:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(6,out_cycle);
			*status-=2;
		}
		else read_eeprom(6,out_cycle);
		break;
		
		case PROG_7:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(7,out_cycle);
			*status-=2;
		}
		else read_eeprom(7,out_cycle);
		break;
		
		case PROG_8:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(8,out_cycle);
			*status-=2;
		}
		else read_eeprom(8,out_cycle);
		break;
		
		case PROG_9:
		if ((*status&0x02)==0x02)
		{
			program_eeprom(9,out_cycle);
			*status-=2;
		}
		else read_eeprom(9,out_cycle);
		break;
		
	}
	return;

}