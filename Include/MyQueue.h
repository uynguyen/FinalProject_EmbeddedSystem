
#include "CommonDefine.h"
#ifndef __MyQueue_H
#define __MyQueue_H


typedef struct{
    Token    *queue;
    char                                   queueCapacity;
    char                                   queueSize;
} MyQueue;

extern void queuePushData(Token,MyQueue *myQueue);
extern Token queuePopData(MyQueue *myQueue);


#endif