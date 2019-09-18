#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include <string.h>
/************************************************
 ALIENTEK 阿波罗STM32F7开发板 实验3
 串口实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


/************************************************
配置esp8266为透传模式
************************************************/
u8 listenResp(char* resp){
	u8 len=0;	
		u32 timeout=0;
  u32 maxDelay=0x1FFFF;
	while(! (USART_RX_STA&0x8000))	{
        timeout++;////超时处理
        if(timeout>maxDelay){
					//return 0;
				}
	}
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
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
    Cache_Enable();                 //打开L1-Cache
    HAL_Init();				        //初始化HAL库
    Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
    delay_init(216);                //延时初始化
		uart1_init(921600);		        //串口初始化
    LED_Init();                     //初始化LED
	esp8266config_translink("aaaa", "bbbb",8080);

}
