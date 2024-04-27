#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "DHT11.h"

//配置PB11口
void DHT11_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
  	GPIO_InitStructure.GPIO_Pin = DHT11_Out_Pin;	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_Init(GPIOB, &GPIO_InitStructure);		  

	GPIO_SetBits(GPIOB, DHT11_Out_Pin);	 
}
//配置上拉输出
static void DHT11_Mode_IPU(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;
	  GPIO_InitStructure.GPIO_Pin = DHT11_Out_Pin;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
	  GPIO_Init(GPIOB, &GPIO_InitStructure);	 
}
//配置推挽输出
static void DHT11_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

  	GPIO_InitStructure.GPIO_Pin = DHT11_Out_Pin;	

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  	GPIO_Init(DHT11, &GPIO_InitStructure);	 	 
}

static uint8_t Read_Byte(void)
{
	uint8_t i, temp=0;

	for (i=0; i<8; i++)    
	{	 
		while (GPIO_ReadInputDataBit(DHT11, DHT11_Out_Pin) == Bit_RESET);

		Delay_us(40);    	  

		if (GPIO_ReadInputDataBit(DHT11, DHT11_Out_Pin) == Bit_SET)//输入高电平
		{
			while(GPIO_ReadInputDataBit(DHT11, DHT11_Out_Pin) == Bit_SET);

			temp |= (uint8_t)(0x01 << (7 - i));
		}
		else//输入低电平
		{			   
			temp &= (uint8_t) ~ (0x01 << (7 - i)); 
		}
	}
	return temp;
}

uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{  
	DHT11_Mode_Out_PP();
	DHT11_DATA_OUT(LOW);
	Delay_ms(18);

	DHT11_DATA_OUT(HIGH); 

	Delay_us(30);  

	DHT11_Mode_IPU();

	if(DHT11_DATA_IN() == Bit_RESET)     
	{
		while(DHT11_DATA_IN() == Bit_RESET);

		while(DHT11_DATA_IN() == Bit_SET);
		//湿度
		DHT11_Data -> humi_int = Read_Byte();
		DHT11_Data -> humi_deci = Read_Byte();
		
		//温度
		DHT11_Data -> temp_int = Read_Byte();
		DHT11_Data -> temp_deci = Read_Byte();
		
		//校验和
		DHT11_Data -> check_sum= Read_Byte();


		DHT11_Mode_Out_PP();
		DHT11_DATA_OUT(HIGH);

		//检验校验和
		if (DHT11_Data -> check_sum == DHT11_Data -> humi_int + DHT11_Data -> humi_deci + DHT11_Data -> temp_int + DHT11_Data -> temp_deci)
			return SUCCESS;
		else 
			return ERROR;
	}
	else
	{		
		return ERROR;
	}   
}
