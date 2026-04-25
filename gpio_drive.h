#include "stm32f10x.h"
//main bus register
#define RCC_APB2ENR (*((volatile unsigned long *) 0x40021018)) //using the RCC register along with the offset of APB2 to enable the pin

//GPIO registers
#define GPIO_A       (*((volatile unsigned long *) 0x40010800))
#define GPIO_B       (*((volatile unsigned long *) 0x40010C00))
#define GPIO_C       (*((volatile unsigned long *) 0x40011000))
	
//List of port 
#define PA 1
#define PB 2
#define PC 3


//setting the directions
#define IN    0 //using for input 
#define OUT10 1 //using output port at 10MHZ
#define OUT2  2 //using output port at 2MHZ
#define OUT50 3 //using output port at 50MHZ

//direction options for input
#define I_AN 0
#define I_F  1
#define I_PP 2

//direction option for output
#define O_GP_PP 0
#define O_GP_OD 1
#define O_AF_PP 2
#define O_AF_OD 3



void init_GP(unsigned short port,unsigned short pin,unsigned short dir,unsigned short opt);
int R_GP(unsigned short port, unsigned short pin); 
void W_GP(unsigned short port , unsigned short pin, unsigned short val);
void toggle_GP(unsigned short port, unsigned short pin);
void Digital_Input(unsigned short PORT,unsigned short PIN);
void Digital_Output(unsigned short PORT,unsigned short PIN);