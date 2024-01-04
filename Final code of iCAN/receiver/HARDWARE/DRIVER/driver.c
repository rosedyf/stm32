#include "driver.h"
#include "stm32f10x.h"
void ENDIR_Init (void)
 {
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PD时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//PD2，3，4，5
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为2MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);	 //根据设定参数初始化GPIOD.2,3,4,5
 }
 void ENDIR_Set (void)
 {
 GPIO_SetBits(GPIOD,GPIO_Pin_2);	 //PD2输出高
 GPIO_ResetBits(GPIOD,GPIO_Pin_3);//PD3输出低
 GPIO_SetBits(GPIOD,GPIO_Pin_4);	 //PD4输出高
 GPIO_ResetBits(GPIOD,GPIO_Pin_5);//PD5输出低	 
 }
 
 
 
 
 
 
 
 
 
 
 