#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_gsm_gprs.h" 
#include "bsp_gsm_usart.h"
#include <string.h>

char *GSM_USART2_RX;//ָ��GSM���͹��������ݵ�ַ
extern volatile uint8_t MakePhone_And_SendMessage_Order;//����绰�ͷ���ָ�������ʼֵΪ'0'
const char Number[]="18033156303";//���ն��ŵĵ绰����

int main(void)
{
    SysTick_Init();//��ʼ��ϵͳ��ʱ�� 
    
	  Debug_USART1_Config();//��ʼ��USART1
	
	  GSM_USART2_Config();//��ʼ��USART2

    /*���ģ����Ӧ�Ƿ�����*/
    while(gsm_init()!= GSM_TRUE)
    {
      printf("\r\nģ����Ӧ�쳣����\r\n");
			GSM_Delay(500);
    }
    printf("\r\nģ����Ӧ���������������ָ��\r\n");
		printf("\r\n����'M'Ϊ����绰  ����'S'Ϊ���Ͷ���\r\n");
    
		/*�ȴ����ڵ��Թ��߷���ָ��*/
    while(1)
		{
			switch(MakePhone_And_SendMessage_Order)
		  {
			  case MAKE_PHONE://����绰
			  {
					MakePhone_And_SendMessage_Order = '0';//����绰�ͷ���ָ����ָ������ֵ�������ظ�����
				  gsm_call("18033156303");//���͵绰������GSMģ�飬�����䲦��绰
          GSM_USART2_RX = gsm_waitask(0);//�ȴ�����GSMģ�鷵�ز���绰�ɹ�ָ��
          if(strstr(GSM_USART2_RX,"ATD") != NULL)//��ӦOK����ʾģ���������յ��������绰
          {
            printf("\r\n���ں���.....\r\n");
						printf("\r\n���гɹ�\r\n");
          }
			  }break;
			
			  case SEND_MESSAGE://���Ͷ���
			  {
				  MakePhone_And_SendMessage_Order = '0';//����绰�ͷ���ָ����ָ������ֵ�������ظ�����
					printf("\r\nӢ�Ķ��ŷ�����......\r\n");
	        if(gsm_sms((char *)Number,"hellow world") == GSM_TRUE)//���Ͷ��ŵ�18033156303�绰�����ж��Ƿ��ͳɹ�
		      {
					  printf("\r\nӢ�Ķ��ŷ��ͳɹ�\r\n");
					}
	        else
	        {
		        printf("\r\nӢ�Ķ��ŷ���ʧ��\r\n");
	        } 
			  }break;
			
			  default: break;
								
		  }
		}			
}



