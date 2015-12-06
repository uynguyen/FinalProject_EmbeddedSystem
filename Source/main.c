#include "stm32f4xx.h"
#include <stdio.h>
#include "Uart.h"
#include <string.h>
#include "Led.h"
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
    UART_UpdateBuffer(final_string);
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
    UART_UpdateBuffer(main_menu);
    while(1)
    {
        // UART currently transfer data, don't access it.
        
        if(!UART_IsTransfering())
        {
            recv = UART_PopData();
    
            if(recv != 0)
            {
                
                switch(recv & 0xff)
                {
                    case (int)'1':
                        show_Basic_Infor();
                        UART_Send_String_data("\033[2J");
                        UART_UpdateBuffer(main_menu);
                    break;
                    
                    case (int)'2':
                    break;
                    
                    case (int)'3':
                    break;
                    
                    case (int)'4':
                        execute_Simple_LED_function();
                        UART_Send_String_data("\033[2J");
                        UART_UpdateBuffer(main_menu);
                    break;
                    
                    case (int)'5':
                    break;
                    
                    
                    
                    
                    
                    default:
                        show_Basic_Infor();
                        All_LED_On();
                    break;
                }
            }
        }
    }
}
//    char recv = 0;
//    char isSpecialKey = 0;


//    UART_Init(9600);
//    LED_Init();
//    init_Main_Menu();
//    UART_UpdateBuffer(main_menu);

//    while(1)
//    {
//        // UART currently transfer data, don't access it.
//        if(!UART_IsTransfering())
//        {
//          
//            recv = UART_PopData();
//    
//            if(recv != 0)
//            {
//                switch(recv & 0xff)
//                {
//                    case (int)'1':
//                        show_Basic_Infor();
//                        
//                    break;
//                    
//                    case (int)'2':
//                    break;
//                    
//                    case (int)'3':
//                    break;
//                    
//                    case (int)'4':
//                        //send_Simple_LED_Menu();
//                        //recv = UART_PopData();
//                        
//                            
//                        
//                    break;
//                    
//                    case (int)'5':
//                    break;
//                    
//                    case (int)'a':
//                    break;
//                    
//                    case (int)'b':
//                    break;
//                    
//                    case (int)'c':
//                    break;
//                    
//                    case (int)'d':
//                    break;
//                    
//                    case (int)'e':
//                    break;
//                    
//                    case (int)'f':
//                    break;
//                    
//                    case (int)'g':
//                    break;
//                    
//                    case (int)'h':
//                    break;
//                    
//                    case (int)'j':
//                    break;
//                    
//                    
//                    case 27:
//                        UART_UpdateBuffer(main_menu);
//                        
//                    break;
//                    default:
//                        show_Basic_Infor();
//                        All_LED_On();
//                    break;
//                }
//                
//                if(isSpecialKey)
//                {
//                    isSpecialKey = 0;
//                    continue;
//                }
//                else
//                {
//                    if(recv >= 32 && recv <= 126) // Printable character.
//                    {
//                        szBuffer[0] = recv;
//                        strcat(szBuffer, sz2);
//                        UART_UpdateBuffer(szBuffer);
//                        
//                        
//                        
//                    }
//                    else if(recv == '\r')
//                    {
//                        UART_UpdateBuffer(sz4); // Print "<ENTER>\r\n" to terminal.
//                    }
//                    else // Special character.
//                    {
//                        isSpecialKey = 1;
//                        UART_UpdateBuffer(sz3);
//                    }
//                }
 //           }
//        }
 //   }
