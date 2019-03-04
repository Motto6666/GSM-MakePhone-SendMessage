#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_gsm_gprs.h" 
#include "bsp_gsm_usart.h"
#include <string.h>

char *GSM_USART2_RX;//指向GSM发送过来的数据地址
extern volatile uint8_t MakePhone_And_SendMessage_Order;//拨打电话和发送指令符，初始值为'0'
const char Number[]="18033156303";//接收短信的电话号码

int main(void)
{
    SysTick_Init();//初始化系统定时器 
    
	  Debug_USART1_Config();//初始化USART1
	
	  GSM_USART2_Config();//初始化USART2

    /*检测模块响应是否正常*/
    while(gsm_init()!= GSM_TRUE)
    {
      printf("\r\n模块响应异常！！\r\n");
			GSM_Delay(500);
    }
    printf("\r\n模块响应正常，请输入相关指令\r\n");
		printf("\r\n输入'M'为拨打电话  输入'S'为发送短信\r\n");
    
		/*等待串口调试工具发送指令*/
    while(1)
		{
			switch(MakePhone_And_SendMessage_Order)
		  {
			  case MAKE_PHONE://拨打电话
			  {
					MakePhone_And_SendMessage_Order = '0';//拨打电话和发送指令符恢复到最初值，避免重复操作
				  gsm_call("18033156303");//发送电话号码至GSM模块，并让其拨打电话
          GSM_USART2_RX = gsm_waitask(0);//等待接收GSM模块返回拨打电话成功指令
          if(strstr(GSM_USART2_RX,"ATD") != NULL)//响应OK，表示模块正常接收到命令并拨打电话
          {
            printf("\r\n正在呼叫.....\r\n");
						printf("\r\n呼叫成功\r\n");
          }
			  }break;
			
			  case SEND_MESSAGE://发送短信
			  {
				  MakePhone_And_SendMessage_Order = '0';//拨打电话和发送指令符恢复到最初值，避免重复操作
					printf("\r\n英文短信发送中......\r\n");
	        if(gsm_sms((char *)Number,"hellow world") == GSM_TRUE)//发送短信到18033156303电话，并判断是否发送成功
		      {
					  printf("\r\n英文短信发送成功\r\n");
					}
	        else
	        {
		        printf("\r\n英文短信发送失败\r\n");
	        } 
			  }break;
			
			  default: break;
								
		  }
		}			
}



