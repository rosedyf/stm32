#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define KEY2   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define KEY3   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11)
#define KEY4   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)
#define KEY5   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)

#define KEY0_PRES 	1
#define KEY1_PRES	  2	
#define KEY2_PRES   3	
#define KEY3_PRES   4
#define KEY4_PRES   5
#define KEY5_PRES   6
void KEY_Init1(void);
void KEY_Init2(void);
u8 KEY_Scan(u8);  	  
#endif

