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

/* LED Definitions */
#define LED_NUM     4                        /* Number of user LEDs          */

extern void LED_Init(void);
extern void LED_On  (unsigned int num);
extern void LED_Off (unsigned int num);
extern void LED_Out (unsigned int value);
extern void LED_Double_On (unsigned int num);
extern void LED_Double_Off (unsigned int num);
extern void All_LED_On (void);
extern void All_LED_Off (void);
#endif
