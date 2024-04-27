#include "stm32f10x.h"
#include "delay.h"
#include "gpio.h"
#include "usart1.h"
 
void Gpio_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStructure;                     //定义一个设置GPIO的变量
	
	
 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA端口时钟
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;       //设置PA0/1
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   		   //下拉输入，默认状态是低电平
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   		   //上拉输入，默认状态是高电平 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //浮空输入
 GPIO_Init(GPIOA, &GPIO_InitStructure);            		 //设置PA
	
}
 
int Gpio_read(void)
{
	if(gpio_readA == 1)
	{ 
		Delay_Ms(100);
		return 1;
	}
	return 0;
}