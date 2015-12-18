/**
  ******************************************************************************
  * @file    SimpleLED.c
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file provides firmware functions to execute Simple LED of final project 
  ******************************************************************************
**/

#include "STM32F4xx.h"
#include "LED.h"
#include "Uart.h"
#include <string.h>
#include "SimpleLED.h"
/*----------------------------------------------------------------------------*
**Func name: send_Simple_LED_Menu                                             *
**Execute: Send simple LED menu to HiberTerminal                              *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void send_Simple_LED_Menu(void)
{
    char simple_LED_menu[200];
    char *simple_LED_title = "3.Simple LED.";
    char *option_1 = "\r\na.On Green.";
    char *option_2 = "\r\nb.Off Green.";
    char *option_3 = "\r\nc.On Orange.";
    char *option_4 = "\r\nd.Off Orange.";
    char *option_5 = "\r\ne.On Red.";
    char *option_6 = "\r\nf.Off Red.";
    char *option_7 = "\r\ng.On Blue.";
    char *option_8 = "\r\nh.Off Blue.";
    char *option_9 = "\r\ni.On All LED.";
    char *option_10 = "\r\nj.Off All LED.";
    char *esc_string = "\r\nESC: return previous menu.";
    strcpy(simple_LED_menu, simple_LED_title); 
    strcat(simple_LED_menu, option_1); 
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
    UART_Send_String_data(simple_LED_menu);
    
}

/*----------------------------------------------------------------------------*
**Func name: execute_Simple_LED_Function                                      *
**Execute: Handler simple LED function                                        *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void execute_Simple_LED_Function(void)
{
    char recv = 0;
    UART_Send_String_data("\033[2J");
    do
    {
        UART_Send_String_data("\033[2J");
        send_Simple_LED_Menu();
        do
        {
           recv = UART_PopData();
        }while (recv == 0);
        
        switch(recv)
        {
            case (int)'a':
                LED_On(Green_LED);
            break;
            
            case (int)'b':
                LED_Off(Green_LED);
            break;
            
            case (int)'c':
                LED_On(Orange_LED);
            break;
            
            case (int)'d':
                LED_Off(Orange_LED);
            break;
            
            case (int)'e':
                LED_On(Red_LED);
            break;
            
            case (int)'f':
                LED_Off(Red_LED);
            break;
            
            case (int)'g':
                LED_On(Blue_LED);
            break;
            
            case (int)'h':
                LED_Off(Blue_LED);
            break;
            
            case (int)'i':
                All_LED_On();
            break;
            
            case (int)'j':
                All_LED_Off();
            break;
            
            default:
                All_LED_Off();
            break;
        }
        
    }while(recv != 27);
    
}




















