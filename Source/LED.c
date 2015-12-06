/*----------------------------------------------------------------------------
 * Name:    LED.c
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

const unsigned long led_mask[] = {GREEN_LED, ORANGE_LED, RED_LED, BLUE_LED};
    
/*----------------------------------------------------------------------------
  initialize LED Pins
 *----------------------------------------------------------------------------*/
void LED_Init (void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    /* GPIOD clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
     
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On (LED_COLOR led) {
    GPIO_SetBits(GPIOD, led);
}

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_Double_On (unsigned int num) {

    unsigned int condition = LED_NUM - 2;
    if (num < condition) {
        GPIOD->BSRRL = led_mask[num] | led_mask[num + 2];
    }
}

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void All_LED_On (void) {
    GPIO_SetBits(GPIOD, GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED);
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off (LED_COLOR led) {
    GPIO_ResetBits(GPIOD, led);
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Double_Off (unsigned int num) {
    unsigned int condition = LED_NUM - 2;
    if (num < condition) {
        GPIOD->BSRRH = led_mask[num] | led_mask[num + 2];
    }
}
/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void All_LED_Off (void) {
    GPIO_ResetBits(GPIOD, GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED);
}


/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(unsigned int value) {
    int i;
    for (i = 0; i < LED_NUM; i++) {
        if (value & (1 << i)) {
            LED_On(i);
        }
        else {
            LED_Off(i);
        }
    }
}
