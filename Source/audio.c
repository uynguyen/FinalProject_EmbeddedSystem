/**
  ******************************************************************************
  * @file    audio.c
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file provides firmware functions to execute audio functions of final project 
  ******************************************************************************
**/

/*----------------------------------------------------------------------------*
 *                      Include zone                                          *
 *----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "Uart.h"
#include "audio.h"
#include "audioplayer.h"
#include "LED.h"

/*----------------------------------------------------------------------------*
 *                      Define variables                                      *
 *----------------------------------------------------------------------------*/
uint8_t vol  = 70;
uint8_t vol_dt = 2;
uint8_t vol_cap = 90;


/*----------------------------------------------------------------------------*
**Func name: send__Menu                                                       *
**Execute: send menu of audio function                                        *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void send__Menu()
{
    char menu[200];
    char *playing_string = "\r\n5. Playing...";
    char *volumeup_string = "\r\n a. Volume Up";
    char *volumedown_string = "\r\n b. Volume Down";
    char *esc_string = "\r\n\r\nESC: return previous menu.";
    strcpy(menu, playing_string); 
    strcat(menu, volumeup_string);
    strcat(menu, volumedown_string);
    strcat(menu, esc_string);
    UART_Send_String_data(menu);
}

/*----------------------------------------------------------------------------*
**Func name: execute_Audio_Function                                           *
**Execute: Handle audio function                                              *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void execute_Audio_Function(void)
{
    char recv = 0;

    UART_Send_String_data("\033[2J");
    play();
    do
    {
        UART_Send_String_data("\033[2J");
        send__Menu();

        do
        {
           recv = UART_PopData();
        }while (recv == 0);
        if(recv != 27 && (recv >= 'a' && recv <= 'b'))
        switch(recv)
        {
            case (int)'a':
            {
               volume_up();
            }
            break;
            
            case (int)'b':
            {
               volume_down();
            }
            break;
            default:
            break;
        }

    }while(recv != 27);
    stop();
}

/*----------------------------------------------------------------------------*
**Func name: Play                                                             *
**Execute: Play audio                                                         *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void play(void)
{
    All_LED_On();
    WavePlayBack(I2S_AudioFreq_48k); 
    
}

/*----------------------------------------------------------------------------*
**Func name: volume_up                                                        *
**Execute: Up volume of audio                                                 *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void volume_up(void)
{
    if (vol < vol_cap) vol += vol_dt;
    WaveplayerCtrlVolume(vol);
}

/*----------------------------------------------------------------------------*
**Func name: volume_down                                                      *
**Execute: Down volume of audio                                               *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void volume_down(void)
{
    if (vol > 0) vol -= vol_dt;
    WaveplayerCtrlVolume(vol);
}

/*----------------------------------------------------------------------------*
**Func name: stop                                                             *
**Execute: Stop play audio                                                    *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void stop(void)
{
    All_LED_Off();
    WavePlayerStop();
}
