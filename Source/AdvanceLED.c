/**
  ******************************************************************************
  * @file    AdvanceLED.c
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file provides firmware functions to execute AdvanceLED functions of final project 
  ******************************************************************************
**/

/*----------------------------------------------------------------------------*
 *                      Include zone                                          *
 *----------------------------------------------------------------------------*/
 
#include "STM32F4xx.h"
#include "LED.h"
#include "Uart.h"
#include <string.h>
#include "AdvanceLED.h"
#include "SPI.h"

/*----------------------------------------------------------------------------*
 *                      Define variables                                      *
 *----------------------------------------------------------------------------*/
volatile int32_t LED_index = 0;
volatile LED_DIRECTION led_direction = CLOCKWISE;
volatile LED_INDEX led_array[4] = { Green_LED, Orange_LED, Red_LED, Blue_LED};

/*----------------------------------------------------------------------------*
**Func name: send_Advance_LED_Menu                                           *
**Execute: send menu of advance LED to hyperterminal                          *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*
**Func name: Set_led                                                          *
**Execute: Set index LED to first start                                       *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
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
            LED_index = Red_LED;
            break;
        
        case 'g':
            LED_index = Green_LED ;
            break;
        case 'o':
            LED_index = Orange_LED ;
            break;
        case 'b':
            LED_index = Blue_LED;
            break;
        
        default:
            LED_index = Red_LED ;
            break;
    }
    
    
}
/*----------------------------------------------------------------------------
  Function that read Button pins
 *----------------------------------------------------------------------------*/
uint32_t BTN_Get(void) {
    return (GPIOA->IDR & (1UL << 0));
}

volatile uint32_t msTicks;

void SysTick_Handler (void) //Enter here every 1 ms
{
    msTicks++;
}

//-------------------------------
void Delay(uint32_t dlyTicks)
{
    uint32_t curTicks;

    curTicks = msTicks;
    while ((msTicks - curTicks) < dlyTicks);
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
        case 'c':
            if(led_direction == ANTICLOCKWISE)
            {
                LED_index += 2;
                if(LED_index  >= LED_NUM )
                    LED_index = 0;
            }
            led_direction = CLOCKWISE;
            
            break;
        
        case 'a':
            if(led_direction == CLOCKWISE)
            {
                LED_index-=2;
                if(LED_index  <= 0 )
                    LED_index = LED_NUM - 1;
            }
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

    char revc = 0;
    UART_Send_String_data("\r\n----------------------");
    UART_Send_String_data("\r\nc. Running.....");
    do { 
        revc = UART_PopData();
        btns = BTN_Get();
        if (btns == (1UL << 0)) 
        {
            mySPIx_SendData(led_array[LED_index]); 
           
            Delay(200);
            if(led_direction == CLOCKWISE)
            {
                
                LED_index++;
                if(LED_index  == LED_NUM )
                    LED_index = 0;
            }
            else{
                LED_index--;
                if(LED_index < 0)
                    LED_index = LED_NUM - 1;
            }
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
