#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"


void KEY_Init1(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void KEY_Init2(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
}


u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;
	if(mode)key_up=1;  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0))
	{
		delay_ms(10);
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
		else if(KEY5==0)return KEY5_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1)key_up=1; 	    
 	return 0;
}

