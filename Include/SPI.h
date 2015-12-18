/**
  ******************************************************************************
  * @file    SPI.h
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file is header file of SPI.c file 
  ******************************************************************************
**/

#ifndef __SPI_H
#define __SPI_H




extern void mySPI_Init(uint16_t);
extern uint8_t mySPIx_GetData();
extern void mySPIx_SendData(uint8_t);



#endif