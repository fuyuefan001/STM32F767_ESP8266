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
	while(! (USART_RX_STA&0x8000));
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			strcpy(resp, USART_RX_BUF);
			resp[len]='\0';
			USART_RX_STA=0;
	}
	return len;
}
int esp8266config_translink(char* ssid, char* pswd){
	char buffer2[100];
	char* AT_CWMODE="AT+CWMODE=1\r\n";
	char* AT_RST="AT+RST\r\n";
	char* AT_CWJAP="AT+RST\r\n";
	u8 len;
	char resp[200];
	while(1){
		printf("AT+RST\r\n");
		len=listenResp(resp);
		printf("%s\r\n",resp);
		printf("%d\r\n",len);
		delay_ms(10);
	}
    
	// delay_ms(1000);
	// printf("AT+CIPMODE=1\r\n");
	// delay_ms(4000);
	// printf("AT+CIPSTART=\"TCP\",\"139.199.176.32\",8080\r\n");
	// delay_ms(4000);
	// printf("AT+CIPSEND\r\n");
	// delay_ms(4000);



	sprintf(buffer2,"%s%s\r\n",ssid,pswd);
	delay_ms(10);
	HAL_UART_Transmit(&UART1_Handler,(uint8_t*)buffer2,strlen(buffer2),1000);
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
		uart_init(115200);		        //���ڳ�ʼ��
    LED_Init();                     //��ʼ��LED
	esp8266config_translink("aaaa", "bbbb");
    // while(1){
    //    if(USART_RX_STA&0x8000)
	// 	{					   
	// 		len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
	// 		printf("\r\n�����͵���ϢΪ:\r\n");
	// 		HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//���ͽ��յ�������
	// 		while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
	// 		printf("\r\n\r\n");//���뻻��
	// 		USART_RX_STA=0;
	// 	}else
	// 	{
	// 		times++;
	// 		if(times%200==0);
	// 		// if(times%30==0)LED0_Toggle;//��˸LED,��ʾϵͳ��������.
	// 		delay_ms(10);   
	// 	}
	// }
}
