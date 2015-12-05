/*----------------------------------------------------------------------------
 * Name:    Uart.h
 * Purpose: low level LED definitions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __Uart_H
#define __Uart_H
/*----------------------------------------------------------------------------*
 *                      Define macros                                      *
 *----------------------------------------------------------------------------*/
#define     USART_index                 USART3
#define     GPIO_PinSource_TXD          GPIO_PinSource10
#define     GPIO_PinSource_RXD          GPIO_PinSource11
#define     GPIO_Pin_TXD                GPIO_Pin_10
#define     GPIO_Pin_RXD                GPIO_Pin_11
#define     GPIO_AF_USARTindex          GPIO_AF_USART3
#define     UART_GPIOx                  GPIOB
#define     RCC_APB1Periph_USARTx       RCC_APB1Periph_USART3
#define     RCC_AHB1Periph_GPIOx        RCC_AHB1Periph_GPIOB
#define     USARTx_IRQn                 USART3_IRQn
/*----------------------------------------------------------------------------*
 *                      Define funcs                                          *
 *----------------------------------------------------------------------------*/
extern void uart_init(uint32_t);
extern void send_data(char *);
extern void GPIO_Configuration(void);
extern void RCC_Configuration(void);
#endif
