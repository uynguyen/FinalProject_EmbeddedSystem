#include "stm32f4xx.h"
#include <stdio.h>
#include "Uart.h"
#include <string.h>

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
/*----------------------------------------------------------------------------*
**                               DEFINE VARIABLE                              *
*----------------------------------------------------------------------------*/
 

void show_basic_infor()
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
    send_data("\033[2J");
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
        case 49:
            show_basic_infor();
            
        break;
        
        case 50:
        break;
        
        case 51:
        break;
        
        case 52:
        break;
        
        case 53:
        break;
        
        case 27://ESC
            
        break;
        default:
            show_basic_infor();
            GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15); // On / off LED
        break;
    }
}

void init_option()
{
    strcpy(option_final, greeting); 
    strcat(option_final, option_1);
    strcat(option_final, option_2);
    strcat(option_final, option_3);
    strcat(option_final, option_4);
    strcat(option_final, option_5);
    strcat(option_final, input_your_choice);
}
int main()
{
    init_option();
    
   
    uart_init(9600);
    send_data(option_final);
    while(1){
        // Do nothing
    };
    
    
    return 1;
}