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



typedef enum
{
    NOT_INIT,
    AVAILABLE,
    SENDING,
    SEND_COMPLETE,
    RECEIVING,
    RECEIVE_COMPLETE
} spi_status_t;



uint8_t mySPI_Get_Receive_Data(void);
spi_status_t mySPI_Get_Status(void);
extern void mySPI_Init(uint16_t);
extern void mySPIx_SendData(uint8_t);



#endif