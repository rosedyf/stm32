#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	
#include "usmart.h"	 
#include "rtc.h" 
#include "beep.h" 
#include "driver.h"
#include "pwm.h"
#include "spi.h"
#include "24l01.h"

 
/************************************************
 ALIENTEK��ӢSTM32������ʵ��15
 RTCʵʱʱ��ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


int T=200;
int N=400;
int direction1[400];
int direction2[400];
u8 tmp_buf[33];
int e=0;//�˳�ģʽ��ʶ��
int n=0;//�����������
int decode=0;//ң���źŽ������
 int main(void)
 {
	 vu8 key=0;
	 u8 t=0;
   int x,y;	 
   x=0;
	 y=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	KEY_Init();         	//��ʼ���밴�����ӵ�Ӳ���ӿ�
 	LED_Init();			     //LED�˿ڳ�ʼ��
	BEEP_Init(); 
	LCD_Init();		
	SystemInit();
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	
	RTC_Init();	  			//RTC��ʼ��
	RTC_Alarm_Set(2019,9,19,x,y,00);
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,24,24,"Elite STM32");	
	LCD_ShowString(60,80,200,24,24,"RTC");	
	//��ʾʱ��
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,110,200,24,24,"    -  -  ");	   
	LCD_ShowString(60,170,200,24,24,"  :  :  ");		
	NRF24L01_Init(); 
	ENDIR_Init();//���������ʼ��
	ENDIR_Set();
	TIM3CH2_PWM_Init(8999,0);//PWM�����ʼ��
	TIM2CH3_PWM_Init(8999,0);
	for(n=0;n<N;n++)
	{
		direction1[n]=0;
		direction2[n]=0;
	}
	while (NRF24L01_Check())
	{
	LED0=!LED0;
	delay_ms(500);
	}
	while (1)
	{
		NRF24L01_RX_Mode();
	while(1)
	{		
      key=KEY_Scan(0);	//�õ���ֵ
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES://��WKUP����ң��ģʽ
      while(1)
				{
					e=0;
					for(n=0;n<N-1;n++)
					{							
					if (NRF24L01_RxPacket(tmp_buf) == 0)
			{
					 decode=((tmp_buf[0]-'0')*100000+(tmp_buf[1]-'0')*10000+(tmp_buf[2]-'0')*1000+(tmp_buf[3]-'0')*100+
				(tmp_buf[4]-'0')*10+(tmp_buf[5]-'0')*1);
				switch (decode)
				{
				case 555555://�˳�ң��ģʽ
					e=1;
					break;
				case 666666://ǰ��
				direction1[n]=1;
				TIM_SetAutoreload(TIM2,8999);
				TIM_SetAutoreload(TIM3,8999);
				TIM_SetCompare2(TIM3,4499);
        TIM_SetCompare3(TIM2,4499);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5);
				GPIO_SetBits(GPIOD,GPIO_Pin_3);
				delay_ms(T);
				GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4);	
				break;
				case 222222://��ת
				direction1[n]=2;
				TIM_SetAutoreload(TIM2,8999);
				TIM_SetAutoreload(TIM3,6299);
		    GPIO_ResetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5);
				GPIO_SetBits(GPIOD,GPIO_Pin_3);
				delay_ms(T);
				GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4);
					break;
				case 333333://��ת
				direction1[n]=3;
				TIM_SetAutoreload(TIM3,8999);
				TIM_SetAutoreload(TIM2,6299);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5);
				GPIO_SetBits(GPIOD,GPIO_Pin_3);
				delay_ms(T);
				GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4);
					break;
				case 444444://����
				direction1[n]=4;
				TIM_SetAutoreload(TIM3,17999);
				TIM_SetAutoreload(TIM2,17999);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_3);
				GPIO_SetBits(GPIOD,GPIO_Pin_5);
				delay_ms(T);
				GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4);
					break;
				case 999999:
				direction1[n]=7;
				delay_ms(2000);
				break;
				case 777777://δ�����ź�
				if (n!=0)
				{
				direction1[n]=5;
				delay_ms(T);
				break;
				}
				else if (n==0)
				{
					n=n-1;
					break;
				}
			}
		}
				if (e==1) 
				{
					direction1[n+1]=6;//�ڽ������е�n+1������ֵΪ������ʶ��6
					e=0;
					break;
				}
			else continue;
	}
					while(1)
					{
					if(KEY2==0)
					{
						delay_ms(10);
					if(KEY2==0)
					{
						LED1=!LED1;
						break;
					}
					}
				}
					for(n=0;n<N-1;n++)
					{							
					if (NRF24L01_RxPacket(tmp_buf) == 0)
			{
					 decode=((tmp_buf[0]-'0')*100000+(tmp_buf[1]-'0')*10000+(tmp_buf[2]-'0')*1000+(tmp_buf[3]-'0')*100+
				(tmp_buf[4]-'0')*10+(tmp_buf[5]-'0')*1);
				switch (decode)
				{
				case 555555://�˳�ң��ģʽ
					e=1; 
					break;
				case 666666://ǰ��
				direction2[n]=1;
				TIM_SetAutoreload(TIM2,8999);
				TIM_SetAutoreload(TIM3,8999);
				TIM_SetCompare2(TIM3,4499);
        TIM_SetCompare3(TIM2,4499);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5);
				GPIO_SetBits(GPIOD,GPIO_Pin_3);
				delay_ms(T);
				GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4);
					break;
				case 222222://��ת
				direction2[n]=2;
				TIM_SetAutoreload(TIM2,8999);
				TIM_SetAutoreload(TIM3,6299);
		    GPIO_ResetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5);
				GPIO_SetBits(GPIOD,GPIO_Pin_3);
				delay_ms(T);
				GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4);
					break;
				case 333333://��ת
				direction2[n]=3;
				TIM_SetAutoreload(TIM3,8999);
				TIM_SetAutoreload(TIM2,6299);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5);
				GPIO_SetBits(GPIOD,GPIO_Pin_3);
				delay_ms(T);
				GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4);		
					break;
				case 444444://����
				direction2[n]=4;
				TIM_SetAutoreload(TIM3,17999);
				TIM_SetAutoreload(TIM2,17999);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_3);
				GPIO_SetBits(GPIOD,GPIO_Pin_5);
				delay_ms(T);
				GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_4);
					break;
				case 999999:
				direction2[n]=7;
				delay_ms(2000);
				break;
				case 777777://δ�����ź�
				if (n!=0)
				{
				direction2[n]=5;
				delay_ms(T);
				break;
				}
				else if (n==0)
				{
					n=n-1;
					break;
				}
			}
		}
				if (e==1) 
				{
					direction2[n+1]=6;//�ڽ������е�n+1������ֵΪ������ʶ��6
					e=0;
					break;
				}
			else continue;
	}
					break;
}
			
     
					break; 
				case KEY1_PRES:	
					x=x+1; 
				if(x==24)
				{
					x=0;
					break;
				}else
					break;
				case KEY0_PRES:	
					y=y+1;
				if(y==60)
				{
					y=0;
					break;
				}else
					break;
				case KEY2_PRES:	
					BEEP=0;
				break;
			}
		}
		else 
		{
			RTC_Alarm_Set(2019,9,21,x,y,00);
		delay_ms(10);
		}
	
	
					LED1=!LED1;
			t=calendar.sec;
			LCD_ShowNum(60,110,calendar.w_year,4,24);									  
			LCD_ShowNum(120,110,calendar.w_month,2,24);									  
			LCD_ShowNum(156,110,calendar.w_date,2,24);	 
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(60,140,200,24,24,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60,140,200,24,24,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60,140,200,24,24,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60,140,200,24,24,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60,140,200,24,24,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60,140,200,24,24,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60,140,200,24,24,"Saturday ");
					break;  
			}
			LCD_ShowNum(60,170,calendar.hour,2,24);									  
			LCD_ShowNum(95,170,calendar.min,2,24);									  
			LCD_ShowNum(130,170,calendar.sec,2,24);
			POINT_COLOR=RED;//��������Ϊ��ɫ 
			LCD_ShowString(60,200,200,24,24,"ALARM SET");
			POINT_COLOR=BLUE;//��������Ϊ��ɫ
			LCD_ShowString(60,230,200,24,24,"  :    ");	
			LCD_ShowNum(60,230,x,2,24);
			LCD_ShowNum(95,230,y,2,24);
			RTC_IRQHandler();
	
		delay_ms(10);								  
	};  
 }
	}

