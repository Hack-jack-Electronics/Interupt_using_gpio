#include"gpio_drive.h"
int i1;


// this is the initialising function here offset and used for the ease and reduce the execution time
void init_GP(unsigned short port,unsigned short pin,unsigned short dir,unsigned short opt)
{
	unsigned short port_offset = 0x04;
	unsigned short offset = 0x00;
	unsigned short tpin = pin;
	volatile unsigned long * CR = 0;
	if (pin >7)
	{
		tpin -= 8; //this will map (0-7) with (8-15) so to use same logic
		offset = 0x01;
	}
	
	
	if(port == 1)
	{
		RCC_APB2ENR |= port_offset; 
		CR = (volatile unsigned long *) (&GPIO_A + offset);
	}
	else if(port == 2)
	{
		RCC_APB2ENR |= (port_offset << 1);
		CR = (volatile unsigned long *) (&GPIO_B + offset);

	}
	else if(port == 3)
	{
		RCC_APB2ENR |= (port_offset << 2);
		CR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	
	*CR &= ~(0xf<<(tpin)*4); //reseting the target pin
	*CR |= ((dir<<(tpin)*4) | (opt<<(tpin*4+2))); // this for adding the option and the direction bits
	
	

	
}


//this will read the state of the GPIO if the GPIO is set in input mode used to check the connection of the button
int R_GP(unsigned short port, unsigned short pin)
{
	volatile unsigned long *IDR = 0; // initialising it to 0 so that it should not point in any random direction at any point of time in code
	unsigned short offset = 0x02; // these value is decided from the register map and from thier by shifting 2 from the main address we get to IDR
	int state; //finally needed variable
	
	
	if(port == 1)
	{
		IDR = (volatile unsigned long *) (&GPIO_A + offset);
	}
	else if (port == 2)
	{
		IDR = (volatile unsigned long *) (&GPIO_B + offset);
	}
	else if (port == 3)
	{
		IDR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	
	state = ((*IDR & (1 << pin))>>pin); // we are moving back with pin so that at the end bit it is 0 or 1
	return state;
}


//this will write any value to GPIO
void W_GP(unsigned short port , unsigned short pin, unsigned short state)
{
	unsigned short offset = 0x03;
	volatile unsigned long *ODR = 0;
	
	if(port == 1)
	{
		ODR = (volatile unsigned long *) (&GPIO_A + offset);
	}
	else if (port == 2)
	{
		ODR = (volatile unsigned long *) (&GPIO_B + offset);
	}
	else if (port == 3)
	{
		ODR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	state ? (*ODR |= (state<<pin)) : 	(*ODR &= ~(1<<pin));
}



		