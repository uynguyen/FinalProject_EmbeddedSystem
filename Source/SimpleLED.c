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
//char simple_LED_menu[100];

char* init_option(void)
{
    char *simple_LED_menu = (char*) malloc(100 * sizeof(char));
    char *option_1 = "\r\na.On Green.";
    char *option_2 = "\r\nb.Off Green.";
    char *option_3 = "\r\nc.On Orange.";
    char *option_4 = "\r\nd.Off Orange.";
    char *option_5 = "\r\ne.On Red.";
    char *option_6 = "\r\nf.Off Red.";
    char *option_7 = "\r\ng.On Blue.";
    char *option_8 = "\r\nh.Off Blue.";
    char *option_9 = "\r\ni.On All LED.";
    char *option_10 = "\r\j.Off All LED.";
    char *esc_string = "\r\nESC: return previous menu.";
    strcpy(simple_LED_menu, option_1); 
    strcat(simple_LED_menu, option_2);
    strcat(simple_LED_menu, option_3);
    strcat(simple_LED_menu, option_4);
    strcat(simple_LED_menu, option_5);
    strcat(simple_LED_menu, option_6); 
    strcat(simple_LED_menu, option_7);
    strcat(simple_LED_menu, option_8);
    strcat(simple_LED_menu, option_9);
    strcat(simple_LED_menu, option_10);
    strcat(simple_LED_menu, esc_string);
    
    return simple_LED_menu;
}
void send_Simple_LED_Menu(void)
{
    char* simple_LED_menu = init_option();
    send_data("\033[2J");
    send_data(simple_LED_menu);
    free(simple_LED_menu);
}

















