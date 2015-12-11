#include <stdint.h>
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "Uart.h"
#include <stdlib.h>
#include <stdbool.h>
volatile char operand1 = 0,operand2 = 0;

void send_Basic_Operation_Menu(void)
{
    char basic_operation_menu[200];
    char *option_1 = "\r\na.Plus.";
    char *option_2 = "\r\nb.Subtract.";
    char *option_3 = "\r\nc.Multiple.";
    char *option_4 = "\r\nd.Divide.";
    char *option_5 = "\r\ne.Module.";
    char *esc_string = "\r\nESC: return previous menu.";
    strcpy(basic_operation_menu, option_1); 
    strcat(basic_operation_menu, option_2);
    strcat(basic_operation_menu, option_3);
    strcat(basic_operation_menu, option_4);
    strcat(basic_operation_menu, option_5);
    strcat(basic_operation_menu, esc_string);
    UART_Send_String_data(basic_operation_menu);
    
}
bool isDigit(char ch)
{
    return (ch >= 48 && ch <= 57);
}
void get_Operands_From_User()
{
    bool checkoperand = false;
    do
    {
        UART_Send_String_data("\r\n----------------------");
        UART_Send_String_data("\r\nOperand 1: ");
        do
        {
            operand1 = UART_PopData();
            
        }while(operand1 == 0);
        checkoperand = isDigit(operand1);
            if(!checkoperand)
                UART_Send_String_data("\r\n Please input digital ... !");
    }while(checkoperand == false);
   
    UART_Send_Char_data(operand1);
    checkoperand = false;
    do
    {
        UART_Send_String_data("\r\nOperand 2: ");
        do
        {
            operand2 = UART_PopData();
            
        }while(operand2 == 0);
        checkoperand = isDigit(operand2);
            if(!checkoperand)
                UART_Send_String_data("\r\n Please input digital ... !");
    }while(checkoperand == false);
    
    UART_Send_Char_data(operand2);
    
    UART_Send_String_data("\r\nResult: ");
    operand1 -= 48;
    operand2 -= 48;
}

void execute_Basic_Operation_Function(void)
{
    char recv = 0;
    int32_t result = 0;
    char *esc_string = "\r\nESC: return previous menu.";
    UART_Send_String_data("\033[2J");
    do
    {
        UART_Send_String_data("\033[2J");
        send_Basic_Operation_Menu();
        do
        {
           recv = UART_PopData();
        }while (recv == 0);
        if(recv != 27)
            get_Operands_From_User();
        switch(recv)
        {
            case (int)'a':
            {
                result = operand1 + operand2;
                UART_Send_Char_data(result + 48);
                UART_Send_String_data("\r\n----------------------");
                UART_Send_String_data(esc_string);
                do{
                    recv = UART_PopData();
                }
                while(recv != 27);
                recv = 0;
            }
            break;
            
            case (int)'b':
            {
                result =  operand1 -  operand2;
                UART_Send_Char_data(result + 48);
                UART_Send_String_data("\r\n----------------------");
                UART_Send_String_data(esc_string);
                do{
                    recv = UART_PopData();
                }
                while(recv != 27);
                recv = 0;
            }
                
            break;
            
            case (int)'c':
            {
                result =  operand1 *  operand2;
                UART_Send_Char_data(result + 48);
                UART_Send_String_data("\r\n----------------------");
                UART_Send_String_data(esc_string);
                do{
                    recv = UART_PopData();
                }
                while(recv != 27);
                recv = 0;
            }
            break;
            
            case (int)'d':
            {
                result =  operand1 /  operand2;
                UART_Send_Char_data(result + 48);
                UART_Send_String_data("\r\n----------------------");
                UART_Send_String_data(esc_string);
                do{
                    recv = UART_PopData();
                }
                while(recv != 27);
                recv = 0;
            }
            break;
            
            case (int)'e':
            {
                result =  operand1 % operand2;
                UART_Send_Char_data(result + 48);
                UART_Send_String_data("\r\n----------------------");
                UART_Send_String_data(esc_string);
                do{
                    recv = UART_PopData();
                }
                while(recv != 27);
                recv = 0;
            }
            break;
            
            default:
            break;
        }
        
    }while(recv != 27);
    
}