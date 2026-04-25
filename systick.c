#include "systick.h"
#include "stm32f10x.h"

volatile unsigned long msTicks = 0; 


//this is the intialsing function
void systick_init(void)
{
	SysTick->CTRL = 0;  
	SysTick->LOAD = 0x00FFFFFF; 
	SysTick->VAL  = 0;  
	SysTick->CTRL = 5; 
}

// for using the interupt that will be generated on completion of the count
void systick_inr_start()
{
	__disable_irq();
	SysTick->CTRL = 0;
	SysTick->LOAD = 72000 - 1; //-1 because I am considering 0 as well and this is for 1ms time
	SysTick->VAL  = 0;
	SysTick->CTRL |= 7; 
	__enable_irq();
}

//this function will be executed when interupt will be generated
void SysTick_Handler(void) {
    msTicks++;
}


//function to get the current value
unsigned long get_current_ms(void) {
    return msTicks;
}
