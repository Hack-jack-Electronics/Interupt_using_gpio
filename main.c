#include "gpio_drive.h" // this is the library used to initiliase the GPIO pins
#include "stm32f10x.h" // standard library used to access the registers
#include "systick.h" // for delay or handling perfect timings 
unsigned long last_press_time_0 = 0;
unsigned long last_press_time_1 = 0;
unsigned long last_press_time_2 = 0;
char count = 0;


int main() {
		
		systick_init(); //for starting the systick timer
		//setting up the pin
		//initialising all the GPIO for buttons and LED 
		init_GP(PA,10,OUT50,O_GP_PP); 
		init_GP(PA,11,OUT50,O_GP_PP);
		init_GP(PA,12,OUT50,O_GP_PP);
    init_GP(PA,0,IN,I_PP); // pin used for button
	
		systick_inr_start(); //starting with the systick inorder to use milliseconds to avoid debounce
	
		//setting up the interupt
		RCC->APB2ENR |= 1; //enabling the alternative function
		
		//registering the interupt in NVIC and setting other important regsiters such IMR 
		__disable_irq();
		AFIO->EXTICR[0] = 0x0000;
		EXTI->IMR |= 0x1;
		EXTI->RTSR |= 0x1;
		NVIC_EnableIRQ(EXTI0_IRQn);
		__enable_irq();
		
		
		// I have put this code in while as I need to run it multiple times it is out of while then this run only for once and then will stop and since initial condition for count = 0 no effect
		while(1)
		{
			if(count == 1)
		{
			W_GP(PA,10,1);
			W_GP(PA,11,0);
			W_GP(PA,12,0);
		}
		else if(count == 2)
		{
			W_GP(PA,10,0);
			W_GP(PA,11,1);
			W_GP(PA,12,0);
		}
		else if(count == 3)
		{
			W_GP(PA,10,0);
			W_GP(PA,11,0);
			W_GP(PA,12,1);
		}
		else if(count == 4)
		{
			W_GP(PA,10,1);
			W_GP(PA,11,1);
			W_GP(PA,12,1);
		}
		else if(count == 5)
		{
			count = 0;
			//here all the leds are turned off so that completion of pattern can be properly judged
			W_GP(PA,10,0);
			W_GP(PA,11,0);
			W_GP(PA,12,0);
		}
		}
	
	
}


// making the function that will execute when interupt is being received from GPIO
void EXTI0_IRQHandler()
{
	unsigned long current_ms = get_current_ms();
	if ((current_ms - last_press_time_0) > 50){
		count++;
	}
	EXTI->PR |= (1 << 0); // I need to clear this flag else I will be stuck in here
	
}
