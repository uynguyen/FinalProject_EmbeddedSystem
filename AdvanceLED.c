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
#include "AdvanceLED.h"
#include "SPI.h"
volatile LED_COLOR led_start;
volatile LED_DIRECTION led_direction;
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
void Set_led()
{
    char led = 0;
    UART_Send_String_data("\r\n---------------------------");
    UART_Send_String_data("\r\na.Set LED (r,g,o,b): ");
    UART_Send_String_data("\r\n ESC: return previous menu");
    

    do
    {
        led = UART_PopData();
            
    }while(led == 0);

    switch(led)
    {
        case 'r':
            led_start = RED_LED;
            break;
        
        case 'g':
            led_start = GREEN_LED;
            break;
        case 'o':
            led_start = ORANGE_LED;
            break;
        case 'b':
            led_start = BLUE_LED;
            break;
        
        default:
            led_start = RED_LED;
            break;
    }
    
    
}
/*----------------------------------------------------------------------------
  Function that read Button pins
 *----------------------------------------------------------------------------*/
uint32_t BTN_Get(void) {
    return (GPIOA->IDR & (1UL << 0));
}

void Set_direction()
{
    char direction = 0;
    UART_Send_String_data("\r\n---------------------------");
    UART_Send_String_data("\r\na.Set direction (c,a): ");
    UART_Send_String_data("\r\n ESC: return previous menu");
    do
    {
        direction = UART_PopData();
            
    }while(direction == 0);

    switch(direction)
    {
        case '0':
            led_direction = CLOCKWISE;
            break;
        
        case '1':
            led_direction = ANTICLOCKWISE;
            break;

        default:
            led_direction = CLOCKWISE;
            break;
    }
    
    
}
void Run()
{
    uint32_t btns = 0;
    uint8_t data = 0;
    char revc = 0;
        do { 
            /* Loop forever               */
            btns = BTN_Get();
            if (btns != (1UL << 0)) {
                All_LED_Off();
            }
            else
            {
                mySPIx_SendData(0x20, data); 
                LED_On(data);
               // Delay(200);
                data++;
                if(data == LED_NUM)
                    data = 0;
            }
            }while(revc != 27);
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
                Set_led();
            break;
            
            case (int)'b':
                Set_direction();
            break;
            
            case (int)'c':
                Run();
            break;
            
            default:
                break;
         }
        
    }while(recv != 27);
    
}
