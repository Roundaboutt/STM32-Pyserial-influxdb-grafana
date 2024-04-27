#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "DHT11.h"
#include "LED.h"
#include "Serial.h"
#include "adc.h"
#include "Atomizer.h"
DHT11_Data_TypeDef DHT11_Data;

int main(void)
{	
	//Atomizer_Init();
	Serial_Init();
	LED_Init();
	Motor_Init();
	OLED_Init();
	
	OLED_ShowString(1,1,"State:");	
	OLED_ShowString(2, 1, "AirTemp:");
	OLED_ShowString(3, 1, "AirHumidity:");
	OLED_ShowString(4, 1, "SoilHumi:");
	DHT11_GPIO_Config();
	Adc_Init();
	while (1)
	{	
		uint16_t oil=Get_Adc_Average(ADC_Channel_5,10);
		if(oil<=2000)oil=2000;
		if(oil>=4020)oil=4020;
		float moisture=(float)(4020-oil)/(2020)*100;
		uint16_t moisture_int =(uint16_t) moisture;
		uint16_t moisture_deci = (moisture - moisture_int)*100;
		
		OLED_ShowNum(4,10, moisture_int,2);
		OLED_ShowString(4, 12, ".");
		OLED_ShowNum(4,13, moisture_deci,2);
		
		Delay_ms(100);
		Serial_SendString("T");
		Serial_SendNumber(DHT11_Data.temp_int,2);
		Serial_SendNumber(DHT11_Data.temp_deci,1);
		Delay_ms(100);
		Serial_SendString("H");
		Serial_SendNumber(DHT11_Data.humi_int,2);
		Serial_SendNumber(DHT11_Data.humi_deci,1);
		Delay_ms(100);
		Serial_SendString("S");
		Serial_SendNumber(moisture_int,2);
		Serial_SendNumber(moisture_deci,2);
		
		if(Read_DHT11(&DHT11_Data) == SUCCESS)
		{	
			
			OLED_ShowNum(3, 13, DHT11_Data.humi_int, 2);
			OLED_ShowString(3, 15, ".");
			OLED_ShowNum(3, 16, DHT11_Data.humi_deci, 1);
			
			OLED_ShowNum(2, 9, DHT11_Data.temp_int, 2);
			OLED_ShowString(2, 11, ".");
			OLED_ShowNum(2, 12, DHT11_Data.temp_deci, 1);
			
		}
		
		if(moisture <= 70){
			Motor_ON();
			LED2_ON();
			OLED_ShowString(1,7,"ON ");
		}
		else
		{
			Motor_OFF();
			LED2_OFF();
			OLED_ShowString(1,7,"OFF");
		}
		
		if(DHT11_Data.humi_int <= 70)
		{
			Atomizer_ON();
		}
		else
		{
			Atomizer_OFF();
		}
	}
}
