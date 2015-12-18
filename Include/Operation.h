/**
  ******************************************************************************
  * @file    Operation.h
  * @author  1212505 - 1212513
  * @version V1.0.0
  * @brief   This file is header file of Operation.c file 
  ******************************************************************************
**/

#ifndef __Operation_H
#define __Operation_H

typedef enum{
    FUNCTION_ADD = 0, 
    FUNCTION_SUBTRACT = 1,
    FUNCTION_MULTIPLE = 2,
    FUNCTION_DIVIDE = 3,
    FUNCTION_MODULE = 4
} FUNCTION_POINTER;

extern void send_Basic_Operation_Menu(void);
extern void execute_Basic_Operation_Function(void);
extern double operation_Add(double, double);
extern double operation_Subtract(double, double);
extern double operation_Multiple(double, double);
extern double operation_Divide(double, double);
extern double operation_Module(double, double);
#endif