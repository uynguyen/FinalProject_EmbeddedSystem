#include "stm32f4xx.h"

#include <stdio.h>

#include "LED.h"
#include "SPI.h"

uint8_t spi_receive_data;
spi_status_t current_status = NOT_INIT;
/*----------------------------------------------------------------------------*
**Func name: mySPIx_GetData                                                   *
**Execute: Get data from SPI->DR                                              *
**Func params:                                                                *
**      None                                                                  *
**Func return:                                                                *
**      utin8_t: Data is received                                             *
 *----------------------------------------------------------------------------*/
uint8_t mySPIx_GetData(){

    GPIO_ResetBits(GPIOE, GPIO_Pin_3);
    while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
    return SPI_I2S_ReceiveData(SPI1); //return reveiced data
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

    GPIO_ResetBits(GPIOE, GPIO_Pin_3);
       
    while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));  //transmit buffer empty?
    SPI_I2S_SendData(SPI1, data);
    //wait for spi send complete
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

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
    
    GPIO_InitTypeDefStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_6;
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
    
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
    
    GPIO_SetBits(GPIOE, GPIO_Pin_3);
    //config interupt
    // Configure the NVIC Preemption Priority Bits
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // Enable the SPI1 Interrupt
    SPI_ITConfig(SPI1, SPI_IT_RXNE, ENABLE);
    
    SPI_Cmd(SPI1, ENABLE);
    current_status = AVAILABLE;
}


///
/// @brief:  get received data with SPI1
/// @param:  void
/// @return: data with received
///
uint8_t spi1_get_receive_data(void)
{
    uint8_t data = 0x00;
    
    if (current_status == RECEIVE_COMPLETE)
    {
        data = spi_receive_data;
        current_status = AVAILABLE;
    }
    
    return data;
}


///
/// @brief:  get current status of SPI1
/// @param:  data: data to send
/// @return: void
///
spi_status_t spi1_get_status(void)
{
    return current_status;
}

//SPI1 IT handler
void SPI1_IRQHandler(void)
{
    if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) == SET)
    {
        current_status = RECEIVING;
        spi_receive_data = SPI_I2S_ReceiveData(SPI1);
        current_status = RECEIVE_COMPLETE;
    }
}
