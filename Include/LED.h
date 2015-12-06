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

typedef enum {GREEN_LED = GPIO_Pin_12, ORANGE_LED = GPIO_Pin_13,RED_LED = GPIO_Pin_14, BLUE_LED = GPIO_Pin_15} LED_COLOR;




/*----------------------------------------------------------------------------*
 *                      Define functions                                         *
 *----------------------------------------------------------------------------*/
extern void LED_Init(void);
extern void LED_On  (LED_COLOR);
extern void LED_Off (LED_COLOR);
extern void LED_Out (unsigned int value);
extern void LED_Double_On (unsigned int num);
extern void LED_Double_Off (unsigned int num);
extern void All_LED_On (void);
extern void All_LED_Off (void);
#endif
