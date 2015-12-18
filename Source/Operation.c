/**
  ******************************************************************************
  * @file    Operation.c
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file provides firmware functions to execute basic operation of final project 
  ******************************************************************************
**/

/*----------------------------------------------------------------------------*
 *                      Include zone                                          *
 *----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "Uart.h"
#include "Operation.h"

/*----------------------------------------------------------------------------*
 *                      Define macros                                         *
 *----------------------------------------------------------------------------*/
#define MAX_SIZE_OF_DIGIT_ARRAY 10
#define MAX_SIZE_OF_RESULT_ARRAY 50


/*----------------------------------------------------------------------------*
 *                      Define variables                                      *
 *----------------------------------------------------------------------------*/
char basic_operation_menu[200];
char *basic_oper_option_1 = "\r\na.Plus.";
char *basic_oper_option_2 = "\r\nb.Subtract.";
char *basic_oper_option_3 = "\r\nc.Multiple.";
char *basic_oper_option_4 = "\r\nd.Divide.";
char *basic_oper_option_5 = "\r\ne.Module.";
char *basic_oper_esc_string = "\r\nESC: return previous menu.";

/*----------------------------------------------------------------------------*
 *                      Define function pointer                               *
 *----------------------------------------------------------------------------*/
typedef double (*Operation)(double,double);
Operation funct_pointer[] = {operation_Add, operation_Subtract, operation_Multiple, operation_Divide, operation_Module};


/*----------------------------------------------------------------------------*
**Func name: send_Basic_Operation_Menu                                        *
**Execute: send menu of basic operation to hyperterminal                      *
**Func params: None                                                           *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void send_Basic_Operation_Menu(void)
{

    strcpy(basic_operation_menu, basic_oper_option_1); 
    strcat(basic_operation_menu, basic_oper_option_2);
    strcat(basic_operation_menu, basic_oper_option_3);
    strcat(basic_operation_menu, basic_oper_option_4);
    strcat(basic_operation_menu, basic_oper_option_5);
    strcat(basic_operation_menu, basic_oper_esc_string);
    UART_Send_String_data(basic_operation_menu);
    
}

/*----------------------------------------------------------------------------*
**Func name: isDigit                                                          *
**Execute: Check if array is proper digit                                     *
**Func params:                                                                *
**              char_array: char array is checked                             *
**Func return:                                                                *
**              bool: whether array is proper or not.                         *
 *----------------------------------------------------------------------------*/
bool isDigit(char char_array[MAX_SIZE_OF_DIGIT_ARRAY])
{
    bool result = true;
    uint8_t number_of_dot = 0;
    uint8_t i = 0;
    char ch;
    for(; i < MAX_SIZE_OF_DIGIT_ARRAY; i++)
    {
        ch = char_array[i];
        
        if(ch != 46 && ch != '\0' && ( ch < 48 || ch > 57 ))
        {
            result = false;
            i = MAX_SIZE_OF_DIGIT_ARRAY;
        }
        if(ch == 46) //DOT
            number_of_dot++;
        if(number_of_dot >= 2)
        {
            result = false;
            i = MAX_SIZE_OF_DIGIT_ARRAY;
        }
    }
    return result;
}

/*----------------------------------------------------------------------------*
**Func name: get_Operands_From_User                                           *
**Execute: Get operands form hyperterminal                                    *
**Func params:                                                                *
**              index: Index of operand                                       *
**Func return:                                                                *
**              char*: Char array of operand                                  *
 *----------------------------------------------------------------------------*/
char* get_Operands_From_User(int index)
{
    char ch_digit = 0;
    bool is_exist_dot = false;
    bool is_exist_negative = false;
    uint8_t idx = 0;
    char *digit = malloc(MAX_SIZE_OF_DIGIT_ARRAY);

    UART_Send_String_data("\r\nOperand  ");
    UART_Send_Char_data(index + 48);
    UART_Send_String_data(" : ");
    while(1)
    {
        ch_digit = UART_PopData();

        if(ch_digit == 13 || idx == MAX_SIZE_OF_DIGIT_ARRAY)
            break;
        // Digit or first DOT or [0] first negative sign
        if(ch_digit != 0)
        {
            if((ch_digit == 46 && is_exist_dot == true))
                continue;
            if(ch_digit == 45)
            {    
                if(is_exist_negative == true || idx != 0)
                    continue;
            }
            if(((ch_digit >= 48 && ch_digit <= 57)) || (ch_digit == 45) || (ch_digit == 46))
            {
                if(ch_digit == 46) //IF DOT then turn on flag
                    is_exist_dot = true;
                if(ch_digit == 45) //IF NEGATIVE SIGN then turn on flag
                    is_exist_negative = true;
                digit[idx] = ch_digit;
                idx++;
                UART_Send_Char_data(ch_digit);
            }
        }
    }

    return digit;
}

/*----------------------------------------------------------------------------*
**Func name: operation_Add                                                    *
**Execute: Add two operands                                                   *
**Func params:                                                                *
**              double pram1: First param                                     *
**              double pram2: Second param                                    *
**Func return:                                                                *
**              double: Result of operation                                   *
 *----------------------------------------------------------------------------*/
double operation_Add(double param1, double param2)
{
    return param1 + param2;
}

/*----------------------------------------------------------------------------*
**Func name: operation_Subtract                                               *
**Execute: Subtract two operands                                              *
**Func params:                                                                *
**              double pram1: First param                                     *
**              double pram2: Second param                                    *
**Func return:                                                                *
**              double: Result of operation                                   *
 *----------------------------------------------------------------------------*/
double operation_Subtract(double param1, double param2)
{
    return param1 - param2;
}

/*----------------------------------------------------------------------------*
**Func name: operation_Multiple                                               *
**Execute: Multiple two operands                                              *
**Func params:                                                                *
**              double pram1: First param                                     *
**              double pram2: Second param                                    *
**Func return:                                                                *
**              double: Result of operation                                   *
 *----------------------------------------------------------------------------*/
double operation_Multiple(double param1, double param2)
{
    return param1 * param2;
}

/*----------------------------------------------------------------------------*
**Func name: operation_Divide                                                 *
**Execute: Divide two operands                                                *
**Func params:                                                                *
**              double pram1: First param                                     *
**              double pram2: Second param                                    *
**Func return:                                                                *
**              double: Result of operation                                   *
 *----------------------------------------------------------------------------*/
double operation_Divide(double param1, double param2)
{
    double result = 0;
    if(param2 != 0)
    {
        result = param1 / param2;
    }
    return result;
}


/*----------------------------------------------------------------------------*
**Func name: operation_Module                                                 *
**Execute: Module two operands                                                *
**Func params:                                                                *
**              double pram1: First param                                     *
**              double pram2: Second param                                    *
**Func return:                                                                *
**              double: Result of operation                                   *
 *----------------------------------------------------------------------------*/
double operation_Module(double param1, double param2)
{
    double result = 0;
    if((int32_t)param2 != 0 )
    {
        result =  (int32_t)param1 % (int32_t)param2;
    }
    return result;
}

/*----------------------------------------------------------------------------*
**Func name: execute_Operation                                                *
**Execute: Execute operation                                                  *
**Func params:                                                                *
**              Operation oper: Function pointer to execute                   *
**Func return:                                                                *
**              None:                                                         *
**----------------------------------------------------------------------------*/
void execute_Operation(FUNCTION_POINTER idx_oper){
    uint32_t recv = 0;
    char *result, *digit1, *digit2;
    double operand1, operand2, execute;

    result = malloc(MAX_SIZE_OF_RESULT_ARRAY);
     digit1 = get_Operands_From_User(1);
             digit2 = get_Operands_From_User(2);

    operand1 = atof(digit1);
    operand2 = atof(digit2);
    
    execute = funct_pointer[idx_oper](operand1,operand2);
    if(execute == 0 && operand2 == 0 && ( idx_oper == FUNCTION_DIVIDE || idx_oper == FUNCTION_MODULE))
    {
        UART_Send_String_data("\r\nCan't devide by Zero ... !");
    }
    else
    {
        sprintf(result, "%.4f", execute);
        UART_Send_String_data("\r\nResult: ");
        UART_Send_String_data(result);

    }
    UART_Send_String_data("\r\n----------------------");
    UART_Send_String_data(basic_oper_esc_string);
   
    do{
        recv = UART_PopData();
    }
    while(recv != 27);
    
    free(digit1);
    free(digit2);
    free(result);
}

/*----------------------------------------------------------------------------*
**Func name: execute_Basic_Operation_Function                                 *
**Execute: Execute basic operation                                            *
**Func params:                                                                *
**              None                                                          *
**Func return:                                                                *
**              None:                                                         *
**----------------------------------------------------------------------------*/
void execute_Basic_Operation_Function(void)
{
    char recv = 0;

    UART_Send_String_data("\033[2J");
    do
    {
        UART_Send_String_data("\033[2J");
        send_Basic_Operation_Menu();
        do
        {
            recv = UART_PopData();
        }while (recv == 0);
        UART_Send_String_data("\r\n----------------------");
        switch(recv)
        {
            case (int)'a':
            {
                UART_Send_String_data(basic_oper_option_1);
                execute_Operation(FUNCTION_ADD);
            }
            break;
            
            case (int)'b':
            {
                UART_Send_String_data(basic_oper_option_2);
                execute_Operation(FUNCTION_SUBTRACT);
            }
            break;
            
            case (int)'c':
            {
                UART_Send_String_data(basic_oper_option_3);
                execute_Operation(FUNCTION_MULTIPLE);
            }
            break;
            
            case (int)'d':
            {
                UART_Send_String_data(basic_oper_option_4);
                execute_Operation(FUNCTION_DIVIDE);
            }
            break;
            
            case (int)'e':
            {
                UART_Send_String_data(basic_oper_option_5);
                execute_Operation(FUNCTION_MODULE);
            }
            break;
            
            default:
            break;
        }
        
    }while(recv != 27);
    
}