#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include <string.h>
/************************************************
 ALIENTEK ������STM32F7������ ʵ��3
 ����ʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


/************************************************
����esp8266Ϊ͸��ģʽ
************************************************/
u8 listenResp(char* resp){
	u8 len=0;	
		u32 timeout=0;
  u32 maxDelay=0x1FFFF;
	while(! (USART_RX_STA&0x8000))	{
        timeout++;////��ʱ����
        if(timeout>maxDelay){
					//return 0;
				}
	}
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			strcpy(resp, USART_RX_BUF);
			resp[len]='\0';
			USART_RX_STA=0;
	}
	return len;
}
int esp8266config_translink(char* ssid, char* pswd,int port){
	char buffer2[100];
	char* AT_CWMODE="AT+CWMODE=1\r\n";
	char* AT_RST="AT+RST\r\n";
	char* AT_CWJAP="AT+RST\r\n";
	u8 len;
	char resp[200];

	
		
		printf("AT+RST\r\n");
		len=listenResp(resp);
			if(strcmp(resp,"OK")==0){
				LED1(0);
			}
			if(strcmp(resp,"ERROR")==0){
				LED0(0);
			}			
		
		//printf("%s\r\n",resp);
		//printf("%d\r\n",len);
		delay_ms(1000);
		LED0(1);		
		LED1(1);
		
				printf("xxxxx\r\n");
		len=listenResp(resp);

			if(strcmp(resp,"OK")==0){
				LED1(0);
			}
			if(strcmp(resp,"ERROR")==0){
				LED0(0);
			}			
		
		//printf("%s\r\n",resp);
		//printf("%d\r\n",len);
		delay_ms(1000);
		LED0(1);		
		LED1(1);
		
		
		
		//LED1(1);
		//printf("AT+CIPMODE=1\r\n");
		//len=listenResp(resp);
		//printf("%s\r\n",resp);
		//printf("%d\r\n",len);
		//LED1(0);
		//delay_ms(1000);
		
		
		//LED1(1);
		//printf("AT+CIPSTART=\"TCP\",\"139.199.176.32\",%d\r\n",port);
		//len=listenResp(resp);
		//printf("%s\r\n",resp);
		//printf("%d\r\n",len);
		//LED1(0);
		//delay_ms(5000);
		
	
	return 0;
}
int main(void)
{
		u8 len;	
		u16 times=0; 
    Cache_Enable();                 //��L1-Cache
    HAL_Init();				        //��ʼ��HAL��
    Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
    delay_init(216);                //��ʱ��ʼ��
		uart1_init(921600);		        //���ڳ�ʼ��
    LED_Init();                     //��ʼ��LED
	esp8266config_translink("aaaa", "bbbb",8080);

}
