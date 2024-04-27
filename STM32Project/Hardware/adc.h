#ifndef __ADC_H
#define __ADC_H	
void Adc_Init(void);
int Get_Adc(int ch);
int Get_Adc_Average(int channel,int count);
#endif 
