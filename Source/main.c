/**
  ******************************************************************************
  * @file    main.c
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   main file
  ******************************************************************************
**/


/*----------------------------------------------------------------------------*
**                               INCLUDE zone                                *
*-----------------------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>
#include "Uart.h"
#include <string.h>
#include "Led.h"
#include "SimpleLED.h"
#include "Operation.h"
#include "AdvanceLED.h"
#include "SPI.h"
#include "audio.h"


/*----------------------------------------------------------------------------*
**                               DEFINE MACROS                                *
*-----------------------------------------------------------------------------*/
#define     MASTER

/*----------------------------------------------------------------------------*
**                               DEFINE VARIABLE                              *
*-----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
  Function that initializes Button pins
 *----------------------------------------------------------------------------*/
void BTN_Init(void) 
{
    STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
}

/*----------------------------------------------------------------------------*
**Func name: show_Basic_Infor                                                 *
**Execute: Show students info                                                 *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void show_Basic_Infor(void)
{
    
    char recv = 0;
    char *student_info_title = "\r\n1.Student info";
    char *id_student1 = "\r\nID: 1212505";
    char *fullname_student1 = "\r\nFull name: Nguyen Long Uy";
    char *id_student2 = "\r\nID: 1212513";
    char *fullname_student2 = "\r\nFull name: Le Quoc Vin";
    char *esc_string = "\r\nESC: return previous menu.";
    char final_string[100];
    UART_Send_String_data("\r\n------------------------");
    UART_Send_String_data(student_info_title);
    strcpy(final_string, id_student1); 
    strcat(final_string, fullname_student1);
    strcat(final_string, id_student2);
    strcat(final_string, fullname_student2);
    strcat(final_string, esc_string);
    UART_Send_String_data(final_string);
    do
    {
        do
        {
            recv = UART_PopData();
        }while (recv == 0);
    }while(recv != 27);
}

/*----------------------------------------------------------------------------*
**                               MAIN FUNCTION                                *
*----------------------------------------------------------------------------*/
int main()
{
    #ifdef MASTER
    char recv = 0;

    char main_menu[100];
    char *main_greeting = "Choose your option:";
    char *main_option_1 = "\r\n1.Student info.";
    char *main_option_2 = "\r\n2.Basic operation.";
    char *main_option_3 = "\r\n3.Simple led.";
    char *main_option_4 = "\r\n4.Advance led.";
    char *main_option_5 = "\r\n5.Audio.";
    char *main_input_your_choice = "\r\nInput your choice --> ";
    char *main_esc_string = "\r\nESC: return previous menu.";
    SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
    if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
      while (1);                                  /* Capture error              */
    }

    strcpy(main_menu, main_greeting); 
    strcat(main_menu, main_option_1);
    strcat(main_menu, main_option_2);
    strcat(main_menu, main_option_3);
    strcat(main_menu, main_option_4);
    strcat(main_menu, main_option_5);
    strcat(main_menu, main_input_your_choice);

   

    UART_Init(9600);
    LED_Init();
    mySPI_Init(SPI_Mode_Master);
    BTN_Init();
    
    UART_Send_String_data(main_menu);
    while(1)
    {
        recv = UART_PopData();
        if(recv != 0)
        {
            
            switch(recv & 0xff)
            {
                case (int)'1':
                   show_Basic_Infor();
                break;
                
                case (int)'2':
                    execute_Basic_Operation_Function();
                break;
                
                case (int)'3':
                    execute_Simple_LED_Function();
        
                break;
                
                case (int)'4':
                    execute_Advance_LED_Function();
                break;
                
                case (int)'5':
                    execute_Audio_Function();
                break;
                
                default:
                break;
            }
            UART_Send_String_data("\033[2J");
            UART_Send_String_data(main_menu);
        }
        recv = UART_PopData();
        
        if(recv != 0)
        {
            
            switch(recv & 0xff)
            {
                case (int)'1':
                   show_Basic_Infor();
                  
                break;
                
                case (int)'2':
                    execute_Basic_Operation_Function();
                break;
                
                case (int)'3':
                    execute_Simple_LED_Function();
        
                break;
                
                case (int)'4':
                    execute_Advance_LED_Function();
                break;
                
                case (int)'5':
                    execute_Audio_Function();
                break;
                
                default:
                break;
            }
            UART_Send_String_data("\033[2J");
            UART_Send_String_data(main_menu);
        }
    }
    #else
        uint16_t spi_receive_data;
        LED_Init();
        mySPI_Init(SPI_Mode_Slave);
        All_LED_On();
        while(1){
            if (spi1_get_status() == RECEIVE_COMPLETE)
            {
                spi_receive_data = spi1_get_receive_data();     
                All_LED_Off();   
                if(spi_receive_data != None_LED)
                {
                    LED_On((LED_INDEX)spi_receive_data);
                }                    
                
            }
       }
    #endif
    return 1;
}

