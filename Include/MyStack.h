#include "CommonDefine.h"
#ifndef __MyStack_H
#define __MyStack_H


typedef struct{
    Token    *data;
    char    stackCapacity;
    char    stackSize;
} MyStack;

extern void stackPushData(Token,MyStack*);
extern char stackPopData(MyStack*);



#endif