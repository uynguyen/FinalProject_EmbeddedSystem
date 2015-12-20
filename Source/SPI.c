/**
  ******************************************************************************
  * @file    SPI.c
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file provides firmware functions to execute SPI functions of final project 
  ******************************************************************************
**/

/*----------------------------------------------------------------------------*
 *                      Include zone                                          *
 *----------------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "LED.h"
#include "SPI.h"

/*----------------------------------------------------------------------------*
 *                      Define Macro                                          *
 *----------------------------------------------------------------------------*/
#define SPI_PREEMPTION_PRIORITY                 0
#define SPI_SUB_PRIORITY                        1
#define SPIx                                    SPI1
#define SPIx_RCC_APB2Periph                     RCC_APB2Periph_SPI1
#define SPI_GPIO                                GPIOA
#define SPI_GPIO_Pin                           (GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_6)
#define SPI_GPIO_PinSource5                     GPIO_PinSource5
#define SPI_GPIO_PinSource6                     GPIO_PinSource6
#define SPI_GPIO_PinSource7                     GPIO_PinSource7

/*----------------------------------------------------------------------------*
 *                      Define variables                                      *
 *----------------------------------------------------------------------------*/
uint8_t spi_receive_data;
uint8_t spi_send_data;
spi_status_t current_status = NOT_INIT;

/*----------------------------------------------------------------------------*
**Func name: SPI_ITConfigTXE                                                  *
**Execute: config ITConfigTXE                                                 *
**Func params:                                                                *
**             FunctinalState newState: State is set to SPI TXE               *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void SPI_ITConfigTXE(FunctionalState newState)
{
    SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_TXE, newState);
}


/*----------------------------------------------------------------------------*
**Func name: mySPIx_SendData                                                  *
**Execute: Send data from adress                                              *
**Func params:                                                                *
**      adress: Address hold data                                             *
**      data:   Send data                                                     *
**Func return:                                                                *
**      None                                                                  *
 *----------------------------------------------------------------------------*/
void mySPIx_SendData(uint8_t data){
    spi_send_data = data;
    SPI_ITConfigTXE(ENABLE);
}
/*----------------------------------------------------------------------------*
**Func name: mySPI_Init                                                       *
**Execute: Init SPI                                                           *
**Func params:                                                                *
**      ROLE: MASTER or SLAVE                                                 *
**Func return:                                                                *
**      None                                                                  *
 *----------------------------------------------------------------------------*/

void mySPI_Init(uint16_t ROLE){
    SPI_InitTypeDef SPI_InitTypeDefStruct;
    GPIO_InitTypeDef GPIO_InitTypeDefStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(SPIx_RCC_APB2Periph, ENABLE);

    SPI_InitTypeDefStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitTypeDefStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitTypeDefStruct.SPI_Mode = ROLE;
    SPI_InitTypeDefStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitTypeDefStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitTypeDefStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitTypeDefStruct.SPI_CPOL = SPI_CPOL_High;
    SPI_InitTypeDefStruct.SPI_CPHA = SPI_CPHA_2Edge;
    
    SPI_Init(SPI1, &SPI_InitTypeDefStruct);
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE , ENABLE);
    
    GPIO_InitTypeDefStruct.GPIO_Pin = SPI_GPIO_Pin;
    GPIO_InitTypeDefStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitTypeDefStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitTypeDefStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitTypeDefStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitTypeDefStruct);
    
    GPIO_InitTypeDefStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitTypeDefStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitTypeDefStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitTypeDefStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitTypeDefStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_InitTypeDefStruct);
    
    GPIO_PinAFConfig(SPI_GPIO, SPI_GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(SPI_GPIO, SPI_GPIO_PinSource6, GPIO_AF_SPI1);
    GPIO_PinAFConfig(SPI_GPIO, SPI_GPIO_PinSource7, GPIO_AF_SPI1);
    
    GPIO_SetBits(GPIOE, GPIO_Pin_3);
    
    
    // Config interupt
    // Configure the NVIC Preemption Priority Bits
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = SPI_PREEMPTION_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SPI_SUB_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // Enable the SPI1 Interrupt
    SPI_ITConfig(SPIx, SPI_IT_RXNE, ENABLE);
    
    SPI_Cmd(SPIx, ENABLE);
    current_status = AVAILABLE;
}


/*----------------------------------------------------------------------------*
**Func name: mySPI1_Get_Receive_Data                                          *
**Execute: get receive data from master                                       *
**Func params:                                                                *
**      None                                                                  *
**Func return:                                                                *
**      uint8_t: data                                                         *
 *----------------------------------------------------------------------------*/
uint8_t mySPI_Get_Receive_Data(void)
{
    uint8_t data = 0x00;
    
    if (current_status == RECEIVE_COMPLETE)
    {
        data = spi_receive_data;
        current_status = AVAILABLE;
    }
    
    return data;
}


/*----------------------------------------------------------------------------*
**Func name: mySPI_Get_Status                                                 *
**Execute: Get spi status                                                     *
**Func params:                                                                *
**      None                                                                  *
**Func return:                                                                *
**      spi_status: SPI status                                                *
 *----------------------------------------------------------------------------*/
spi_status_t mySPI_Get_Status(void)
{
    return current_status;
}

/*----------------------------------------------------------------------------*
**Func name: SPI1_IRQHandler                                                  *
**Execute: Handler SPI interrupt                                              *
**Func params:                                                                *
**      None                                                                  *
**Func return:                                                                *
**      None                                                                  *
 *----------------------------------------------------------------------------*/
void SPI1_IRQHandler(void)
{
     // Ready to send.
    if(RESET != SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_TXE))
    {
        SPI_ClearITPendingBit(SPIx, SPI_I2S_IT_TXE);
        GPIO_ResetBits(GPIOE, GPIO_Pin_3);
        SPI_I2S_SendData(SPIx, spi_send_data);
        // Disable TXE flag.
        SPI_ITConfigTXE(DISABLE);
        
    }
    
    if (SET == SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_RXNE))
    {
        current_status = RECEIVING;
        spi_receive_data = SPI_I2S_ReceiveData(SPIx);
        current_status = RECEIVE_COMPLETE;
    }
}
