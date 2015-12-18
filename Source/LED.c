/**
  ******************************************************************************
  * @file    Operation.c
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file provides firmware functions to execute LED of final project 
  ******************************************************************************
**/

#include "STM32F4xx.h"
#include "LED.h"

/*----------------------------------------------------------------------------*
 *                      Define variables                                      *
 *----------------------------------------------------------------------------*/
 
const unsigned long led_mask[] = {GREEN_LED, ORANGE_LED, RED_LED, BLUE_LED};
    
/*----------------------------------------------------------------------------*
**Func name: LED_Init                                                         *
**Execute: Config LED                                                         *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void LED_Init (void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    /* GPIOD clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
     
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*----------------------------------------------------------------------------*
**Func name: LED_On                                                           *
**Execute: On LED                                                             *
**Func params:                                                                *
**             LED_INDEX led: index of lex to turn on                         *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void LED_On (LED_INDEX led) {
    LED_COLOR led_color;
    switch(led)
    {
        case Green_LED:
            led_color = GREEN_LED;
        break;
        
        case Orange_LED:
            led_color = ORANGE_LED;
        break;
        
        case Red_LED: 
            led_color = RED_LED;
        break;
        
        case Blue_LED:
            led_color = BLUE_LED;
        break;
        
        default:
            break;
            
    }
    GPIO_SetBits(GPIOD, led_color);
}

/*----------------------------------------------------------------------------*
**Func name: All_LED_On                                                       *
**Execute: Turn on All LED                                                    *
**Func params:                                                                *
**             None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void All_LED_On (void) {
    GPIO_SetBits(GPIOD, GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED);
}

/*----------------------------------------------------------------------------*
**Func name: LED_Off                                                          *
**Execute: Off LED                                                            *
**Func params:                                                                *
**             LED_INDEX led: index of lex to turn off                        *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void LED_Off (LED_INDEX led) {
    LED_COLOR led_color;
    switch(led)
    {
        case Green_LED:
            led_color = GREEN_LED;
        break;
        
        case Orange_LED:
            led_color = ORANGE_LED;
        break;
        
        case Red_LED: 
            led_color = RED_LED;
        break;
        
        case Blue_LED:
            led_color = BLUE_LED;
        break;
        
        default:
            break;
            
    }
    GPIO_ResetBits(GPIOD, led_color);
}

/*----------------------------------------------------------------------------*
**Func name: All_LED_Off                                                      *
**Execute: Turn off All LED                                                   *
**Func params:                                                                *
**             None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void All_LED_Off (void) {
    GPIO_ResetBits(GPIOD, GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED);
}


