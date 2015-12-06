#include <stdint.h>
#include "uart.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include <stddef.h>
/*----------------------------------------------------------------------------*
 *                      Define variables                                      *
 *----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*
**Func name: RCC_Configuration                                                *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void RCC_Configuration(void)
{
    /* --------------------------- System Clocks Configuration -----------------*/
    /* USART3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);
    /* GPIOD clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
 
}
/*----------------------------------------------------------------------------*
**Func name: NVIC_Configuration                                               *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void NVIC_Configuration(uint16_t preem_priority, uint16_t sub_priority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
   
  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
   
  /* Enable the USART3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preem_priority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub_priority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
   
/*----------------------------------------------------------------------------*
**Func name: GPIO_Configuration                                               *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
     
    /* Connect USART pins to AF */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_TXD | GPIO_Pin_RXD;
    GPIO_Init(UART_GPIOx, &GPIO_InitStructure);
      
    GPIO_PinAFConfig(UART_GPIOx, GPIO_PinSource_TXD, GPIO_AF_USARTindex);
    GPIO_PinAFConfig(UART_GPIOx, GPIO_PinSource_RXD, GPIO_AF_USARTindex);
}
   
/*----------------------------------------------------------------------------*
**Func name: USART3_Configuration                                             *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void USARTx_Configuration(uint32_t baudrate)
{  
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART_index,&USART_InitStructure);
    USART_ITConfig(USART_index, USART_IT_RXNE , ENABLE); //Enable interrupt
    USART_Cmd(USART_index, ENABLE);
}


   
/*----------------------------------------------------------------------------*
**Func name: send_data                                                        *
**Execute: send data to HT                                                    *
**Func params:                                                                *
**      char *data: Array of character will be send                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void send_data(char *data) {
    int32_t count = 0;
    char character = data[count++];
       
    while (character)
    {
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) != SET)
        {
            //do nothing here;
        }
            
        USART_SendData(USART3, character);
        character = data[count++];
    } 
}

/*----------------------------------------------------------------------------*
**Func name: uart_init                                                        *
**Execute: Init uart                                                          *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void uart_init(uint32_t baudrate){
    RCC_Configuration();
   
    GPIO_Configuration();
    
    NVIC_Configuration(0,1);
    
    USARTx_Configuration(baudrate);
}
