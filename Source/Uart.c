/**
  ******************************************************************************
  * @file    Uart.c
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file provides firmware functions to execute Uart functions of final project 
  ******************************************************************************
**/


/*----------------------------------------------------------------------------*
 *                      Include zone                                          *
 *----------------------------------------------------------------------------*/
#include <stdint.h>
#include "uart.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include <stddef.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------*
 *                      Define Macro                                          *
 *----------------------------------------------------------------------------*/
#define UART_PREEMPTION_PRIORITY                1
#define UART_USART                              USART3
#define UART_RCC_APB1Periph_USART               RCC_APB1Periph_USART3
#define UART_RCC_AHB1Periph_GPIO                RCC_AHB1Periph_GPIOB
#define UART_GPIO                               GPIOB
#define UART_GPIO_PinSource1                    GPIO_PinSource10
#define UART_GPIO_PinSource2                    GPIO_PinSource11
#define UART_GPIO_AF_USART                      GPIO_AF_USART3
#define UART_GPIO_Pin                           (GPIO_Pin_10 | GPIO_Pin_11)
#define UART_NVIC_IRQChannel                    USART3_IRQn

/*----------------------------------------------------------------------------*
 *                      Define variables                                      *
 *----------------------------------------------------------------------------*/
volatile char            g_szBuffer[255];
volatile int             g_idx = 0;
volatile int             g_iMaxCount = 255;
volatile char            g_iLen = 0;
volatile char            g_isTransfering = 0;
volatile char            g_queue[10];
volatile char            g_queueCapacity = 10;
volatile char            g_queueSize = 0;

/*-------------------------------INIT FUNCTIONS--------------------------------------------*/

/*----------------------------------------------------------------------------*
**Func name: UART_Init                                                        *
**Execute: Init uart                                                          *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void UART_Init(uint32_t baudrate){
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    // Step 1
    RCC_APB1PeriphClockCmd(UART_RCC_APB1Periph_USART, ENABLE);
    
    // Step 2
    RCC_AHB1PeriphClockCmd(UART_RCC_AHB1Periph_GPIO, ENABLE);
    
    // Step 3
    GPIO_PinAFConfig(UART_GPIO, UART_GPIO_PinSource1, UART_GPIO_AF_USART);
    GPIO_PinAFConfig(UART_GPIO, UART_GPIO_PinSource2, UART_GPIO_AF_USART);
    
    GPIO_InitStruct.GPIO_Pin = UART_GPIO_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(UART_GPIO, &GPIO_InitStruct);
    
    // Step 4
    USART_InitStruct.USART_BaudRate = baudrate;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(UART_USART, &USART_InitStruct);
    
    // Step 5
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStruct.NVIC_IRQChannel = UART_NVIC_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = UART_PREEMPTION_PRIORITY;
    NVIC_Init(&NVIC_InitStruct);
    
    USART_ITConfig(UART_USART, USART_IT_RXNE, ENABLE);
    
    // Step 7
    USART_Cmd(UART_USART, ENABLE);

}



/*------------------------------------ END INIT FUNCTIONS ----------------------- */

/*----------------------------------------------------------------------------*
**Func name: UART_ITConfigTXE                                                 *
**Execute: config ITConfigTXE                                                 *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void UART_ITConfigTXE(FunctionalState newState)
{
    USART_ITConfig(UART_USART, USART_IT_TXE, newState);
}


/*----------------------------------------------------------------------------*
**Func name: UART_ITConfigRXNE                                                *
**Execute: config ITConfigRXE                                                 *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/

void UART_ITConfigRXNE(FunctionalState newState)
{
    USART_ITConfig(UART_USART, USART_IT_RXNE, newState);
}

   
/*----------------------------------------------------------------------------*
**Func name: send_data                                                        *
**Execute: send data to HT                                                    *
**Func params:                                                                *
**      char *data: Array of character will be send                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void UART_Send_String_data(char *data) {

    while(UART_IsTransfering()){
        // IF UART is trasferring then do nothing
    }

    UART_UpdateBuffer(data);

}

/*----------------------------------------------------------------------------*
**Func name: UART_Receive_Data                                                *
**Execute: Receive Data from uart                                             *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
uint8_t UART_Receive_Data()
{
    return USART_ReceiveData(UART_USART);
}



/*----------------------------------------------------------------------------*
**Func name: UART_PushData                                                    *
**Execute: Push a character data into buffer                                  *
**Func params:                                                                *
**                  ch:     Character is pushed into buffer                   *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void UART_PushData(char ch)
{
    while(g_queueSize >= g_queueCapacity)
    {
        UART_PopData();
    }
    g_queue[g_queueSize++] = ch;
 
}

/*----------------------------------------------------------------------------*
**Func name: UART_PopData                                                     *
**Execute: Pop a character data from buffer                                   *
**Func params: None                                                           *
**Func return: None                                                           *
**                  char:     Character is popped from buffer                 *
 *----------------------------------------------------------------------------*/
char UART_PopData(void)
{
 
    char ret;
    int i = 1;
    if(g_queueSize == 0)
        return 0;
    
    ret = g_queue[0];
    
    for(; i < g_queueSize; i++)
    {
        g_queue[i - 1] = g_queue[i];
    }
    
    g_queueSize--;
    
    return ret;
}

/*------------------------- IT HANDLER ------------------------- */


/*----------------------------------------------------------------------------*
**Func name: UART_ITSend                                                      *
**Execute: UART Send data by interrupt                                        *
**Func params:                                                                *
**             uint8_t ch: Character is sent                                  *
**Func return: None                                                           *
**             None                                                           *
 *----------------------------------------------------------------------------*/
void UART_ITSend(uint8_t ch)
{
    USART_SendData(UART_USART, ch);
}

/*----------------------------------------------------------------------------*
**Func name: UART_ClearBuffer                                                 *
**Execute: UART Clear Buffer                                                  *
**Func params:                                                                *
**             None                                                           *
**Func return:                                                                *
**             None                                                           *
 *----------------------------------------------------------------------------*/
void UART_ClearBuffer()
{
    int i = 0;
    for(; i < g_iMaxCount; i++)
    {
        g_szBuffer[i] = 0;
    }
    
    g_idx = 0;
    g_iLen = 0;
}

/*----------------------------------------------------------------------------*
**Func name: UART_UpdateBuffer                                                *
**Execute: UART update sended buffer                                          *
**Func params:                                                                *
**             char szNewBuffer: new buffer is sent                           *
**Func return:                                                                *
**             None                                                           *
 *----------------------------------------------------------------------------*/
void UART_UpdateBuffer(volatile char szNewBuffer[])
    
{
    int i = 0;
    g_isTransfering = 1;
    UART_ClearBuffer();
    
    for(; szNewBuffer[i] != 0; i++)
    {
        g_szBuffer[i] = szNewBuffer[i];
    }
    
    g_iLen = i;

    // Ready to send data.
    UART_ITConfigTXE(ENABLE);
}


/*----------------------------------------------------------------------------*
**Func name: UART_IsTransfering                                               *
**Execute: Check if UART is trasfering                                        *
**Func params:                                                                *
**             None                                                           *
**Func return:                                                                *
**             None                                                           *
 *----------------------------------------------------------------------------*/
char UART_IsTransfering(void)
{
    return g_isTransfering;
}


/*----------------------------------------------------------------------------*
**Func name: USART3_IRQHandler                                                *
**Execute: Receive data and send to HT                                        *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void USART3_IRQHandler(void)
{
    // Ready to send.
    if(RESET != USART_GetITStatus(UART_USART, USART_IT_TXE))
    {
        USART_ClearITPendingBit(UART_USART, USART_IT_TXE);
        // Check whether internal queue has data.
        if(g_idx < g_iLen)
        {
            UART_ITSend(g_szBuffer[g_idx]);
            g_idx++;
        
            // All character sent.
            if(g_idx >= g_iLen)
            {
                UART_ClearBuffer();

                g_isTransfering = 0;
                
                // Disable TXE flag.
                UART_ITConfigTXE(DISABLE);
            }
        }
    }
    
    // Has data to receive.
    if(RESET != USART_GetITStatus(UART_USART, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(UART_USART, USART_IT_RXNE);
        
        UART_PushData(UART_Receive_Data());
    }
}


