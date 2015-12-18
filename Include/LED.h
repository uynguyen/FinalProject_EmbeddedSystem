/**
  ******************************************************************************
  * @file    LED.h
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file is header file of LED.c file 
  ******************************************************************************
**/

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
    Blue_LED = 3,
    None_LED = 4
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
