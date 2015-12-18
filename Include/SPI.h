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


#ifndef __SPI_H
#define __SPI_H



typedef enum
{
    NOT_INIT,
    AVAILABLE,
    SENDING,
    SEND_COMPLETE,
    RECEIVING,
    RECEIVE_COMPLETE
} spi_status_t;



uint8_t spi1_get_receive_data(void);
spi_status_t spi1_get_status(void);
extern void mySPI_Init(uint16_t);
extern uint8_t mySPIx_GetData(void);
extern void mySPIx_SendData(uint8_t);



#endif