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
 *                      Define funcs                                          *
 *----------------------------------------------------------------------------*/
extern void UART_Init(uint32_t);
extern void UART_UpdateBuffer(volatile char szNewBuffer[]);
extern void UART_ClearBuffer(void);
extern char UART_IsTransfering(void);
extern void UART_Send_String_data(char *);

/* Interrupt functions ****************************************************/

extern char UART_PopData(void);

#endif
