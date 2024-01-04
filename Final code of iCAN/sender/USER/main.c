#include "sys.h"
#include "misc.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "24l01.h"
 int main(void)
 {
	u8 key;
	u8 tmp_buf[33];
 	u8 t;
 	SystemInit();
	delay_init();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	uart_init(9600);
 	LED_Init();	
 	KEY_Init1();
	KEY_Init2();
	NRF24L01_Init(); 
	while(NRF24L01_Check())
	{
		delay_ms(1000);
		LED0=!LED0;
	}
	NRF24L01_TX_Mode();
	for(t=0;t<6;t++)
	{
		tmp_buf[t]='0';
	}
	while(1)
	{
		 key=KEY_Scan(1);
		 switch(key)
		 {
		 case KEY0_PRES:
		 for(t=0;t<6;t++)
		{
		tmp_buf[t]='1';
		}
		NRF24L01_TxPacket(tmp_buf);
		break;
		 case KEY1_PRES:
		 for(t=0;t<6;t++)
		{
		tmp_buf[t]='2';
		}
		NRF24L01_TxPacket(tmp_buf);
		break;
		case KEY2_PRES:
		 for(t=0;t<6;t++)
		{
		tmp_buf[t]='3';
		}
		NRF24L01_TxPacket(tmp_buf);
		break;
		case KEY3_PRES:
		 for(t=0;t<6;t++)
		{
		tmp_buf[t]='4';
		}
		NRF24L01_TxPacket(tmp_buf);
		break;
		case KEY4_PRES:
		 for(t=0;t<6;t++)
		{
		tmp_buf[t]='5';
		}
		NRF24L01_TxPacket(tmp_buf);
		break;
		case KEY5_PRES:
		 for(t=0;t<6;t++)
		{
		tmp_buf[t]='6';
		}
		NRF24L01_TxPacket(tmp_buf);
		break;
		case 0:
		for(t=0;t<6;t++)
		{
		tmp_buf[t]='7';
		}
		NRF24L01_TxPacket(tmp_buf);
		break;
		}
	}
 	}

