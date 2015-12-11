/*----------------------------------------------------------------------------
 * Name:    LED.h
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

#ifndef __LED_H
#define __LED_H
/*----------------------------------------------------------------------------*
 *                      Define macros                                         *
 *----------------------------------------------------------------------------*/
#define     LED_NUM                      4                        /* Number of user LEDs          */

typedef enum {
    GREEN_LED = GPIO_Pin_12, 
    ORANGE_LED = GPIO_Pin_13,
    RED_LED = GPIO_Pin_14,
    BLUE_LED = GPIO_Pin_15
} LED_COLOR;

typedef enum {
    Green_LED = 0, 
    Orange_LED = 1, 
    Red_LED = 2, 
    Blue_LED = 3 
} LED_INDEX;


/*----------------------------------------------------------------------------*
 *                      Define functions                                         *
 *----------------------------------------------------------------------------*/
extern void LED_Init(void);
extern void LED_On  (LED_INDEX);
extern void LED_Off (LED_INDEX);
extern void All_LED_On (void);
extern void All_LED_Off (void);
#endif
