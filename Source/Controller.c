/*----------------------------------------------------------------------------*
**                               Include Libraries                              *
*----------------------------------------------------------------------------*/
#include <string.h> 
#include "stm32f4xx.h"
#include "Uart.h"
#include "LED.h"
#include "SimpleLED.h"
/*----------------------------------------------------------------------------*
**                               DEFINE VARIABLE                              *
*----------------------------------------------------------------------------*/
char option_final[500];
char *greeting = "Choose your option:";
char *option_1 = "\r\n1.Student info.";
char *option_2 = "\r\n2.Basic operation.";
char *option_3 = "\r\n3.Simple led.";
char *option_4 = "\r\n4.Advance led.";
char *option_5 = "\r\n5.Audio.";
char *input_your_choice = "\r\nInput your choice --> ";
char *esc_string = "\r\nESC: return previous menu.";

 

void show_basic_infor(void)
{
    char *id_student1 = "\r\nID: 1212505";
    char *fullname_student1 = "\r\nFull name: Nguyen Long Uy";
    char *id_student2 = "\r\nID: 1212513";
    char *fullname_student2 = "\r\nFull name: Le Quoc Vin";
    char final_string[100];
    strcpy(final_string, id_student1); 
    strcat(final_string, fullname_student1);
    strcat(final_string, id_student2);
    strcat(final_string, fullname_student2);
    strcat(final_string, esc_string);
    send_data(final_string);
    
}

void init_Main_Menu(void)
{
    strcpy(option_final, greeting); 
    strcat(option_final, option_1);
    strcat(option_final, option_2);
    strcat(option_final, option_3);
    strcat(option_final, option_4);
    strcat(option_final, option_5);
    strcat(option_final, input_your_choice);
}
void send_Main_Menu(void)
{
    send_data(option_final);
}
/*----------------------------------------------------------------------------*
**Func name: USART3_IRQHandler                                                *
**Execute: Receive data and send to HT                                        *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void USART3_IRQHandler(void)
{
    char chr;

    while (USART_GetFlagStatus(USART_index, USART_FLAG_RXNE) != SET) ;
    
    chr = USART_ReceiveData(USART_index);
    switch(chr & 0xff)
    {
        case (int)'1':
            show_basic_infor();
            
        break;
        
        case (int)'2':
        break;
        
        case (int)'3':
        break;
        
        case (int)'4':
            send_Simple_LED_Menu();
        break;
        
        case (int)'5':
        break;
        
        case (int)'a':
        break;
        
        case (int)'b':
        break;
        
        case (int)'c':
        break;
        
        case (int)'d':
        break;
        
        case (int)'e':
        break;
        
        case (int)'f':
        break;
        
        case (int)'g':
        break;
        
        case (int)'h':
        break;
        
        
        case (int)'j':
        break;
        
        
        case 27://ESC
            
        break;
        default:
            show_basic_infor();
            All_LED_On();
        break;
    }
}
