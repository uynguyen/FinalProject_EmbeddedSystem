/*----------------------------------------------------------------------------
 * Name:    Simple_LED.c
 * Purpose: low level LED functions
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

#include "STM32F4xx.h"
#include "LED.h"
#include "Uart.h"
#include <string.h>
void send_Advance_LED_Menu(void)
{
    char simple_LED_menu[200];
    char *option_1 = "\r\na.Set LED.";
    char *option_2 = "\r\nb.Set direction.";
    char *option_3 = "\r\nc.Start.";
    strcpy(simple_LED_menu, option_1); 
    strcat(simple_LED_menu, option_2);
    strcat(simple_LED_menu, option_3);
    UART_Send_String_data(simple_LED_menu);
}

void execute_Advance_LED_Function(void)
{
    char recv = 0;
    UART_Send_String_data("\033[2J");
    do
    {
        UART_Send_String_data("\033[2J");
        send_Advance_LED_Menu();
        do
        {
           recv = UART_PopData();
        }while (recv == 0);
        
        switch(recv)
        {
            case (int)'a':
                LED_On(GREEN_LED);
            break;
            
            case (int)'b':
                LED_Off(GREEN_LED);
            break;
            
            case (int)'c':
                LED_On(ORANGE_LED);
            break;
            
            default:
                break;
         }
        
    }while(recv != 27);
    
}
