#ifndef __BSP_USART_H
#define	__BSP_USART_H

#include "stm32f10x.h"
#include <stdio.h>

// USART1 ����궨��
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200


// USART1 GPIO ���ź궨��
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT         GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN          GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10


// USART1 �жϷ�������غ궨��
#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler


//����绰�ͷ��Ͷ���ָ����غ궨��
#define  MAKE_PHONE                     'M'//����绰ָ��궨��
#define  SEND_MESSAGE                   'S'//���Ͷ���ָ��궨��

void Debug_USART1_Config(void);
void bsp_DEBUG_USART_IRQHandler(void);
char *get_rebuff(uint8_t *len);
void clean_rebuff(void);

#endif /* __BSP_USART_H */
