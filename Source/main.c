#include "stm32f4xx.h"
#include <stdio.h>
#include "Uart.h"
#include <string.h>
#include "Led.h"
#include "SimpleLED.h"
#include "Operation.h"
/*----------------------------------------------------------------------------*
**                               DEFINE VARIABLE                              *
*----------------------------------------------------------------------------*/


void show_Basic_Infor(void)
{
    char recv = 0;
    char *id_student1 = "\r\nID: 1212505";
    char *fullname_student1 = "\r\nFull name: Nguyen Long Uy";
    char *id_student2 = "\r\nID: 1212513";
    char *fullname_student2 = "\r\nFull name: Le Quoc Vin";
    char final_string[100];
    strcpy(final_string, id_student1); 
    strcat(final_string, fullname_student1);
    strcat(final_string, id_student2);
    strcat(final_string, fullname_student2);
    UART_Send_String_data(final_string);
    do
    {
        do
        {
           recv = UART_PopData();
        }while (recv == 0);
    }while(recv != 27);
}

void init_Main_Menu(void)
{
    
}
/*----------------------------------------------------------------------------*
**                               MAIN FUNCTION                                *
*----------------------------------------------------------------------------*/
int main()
{
    char recv = 0;
    char isSpecialKey = 0;
    char main_menu[100];
    char *greeting = "Choose your option:";
    char *option_1 = "\r\n1.Student info.";
    char *option_2 = "\r\n2.Basic operation.";
    char *option_3 = "\r\n3.Simple led.";
    char *option_4 = "\r\n4.Advance led.";
    char *option_5 = "\r\n5.Audio.";
    char *input_your_choice = "\r\nInput your choice --> ";
    char *esc_string = "\r\nESC: return previous menu.";
    strcpy(main_menu, greeting); 
    strcat(main_menu, option_1);
    strcat(main_menu, option_2);
    strcat(main_menu, option_3);
    strcat(main_menu, option_4);
    strcat(main_menu, option_5);
    strcat(main_menu, input_your_choice);
   

    UART_Init(9600);
    LED_Init();
    init_Main_Menu();
    UART_Send_String_data(main_menu);
    while(1)
    {
        // UART currently transfer data, don't access it.
        

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
                        
                    break;
                    
                    case (int)'5':
                    break;
                    
                    default:
                    break;
                }
                UART_Send_String_data("\033[2J");
                UART_Send_String_data(main_menu);
            }
            
        
    }
    return 1;
}

