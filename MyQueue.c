#include "MyQueue.h"


/*----------------------------------------------------------------------------*
**Func name: UART_PushData                                                    *
**Execute: Push a character data into buffer                                  *
**Func params:                                                                *
**                  ch:     Character is pushed into buffer                   *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void queuePushData(Token ch, MyQueue *myQueue)
{
    while( myQueue->queueSize >=  myQueue->queueCapacity)
    {
        queuePopData(myQueue);
    }
    myQueue->queue[myQueue->queueSize++] = ch;
}

/*----------------------------------------------------------------------------*
**Func name: UART_PopData                                                     *
**Execute: Pop a character data from buffer                                   *
**Func params: None                                                           *
**Func return: None                                                           *
**                  char:     Character is popped from buffer                 *
 *----------------------------------------------------------------------------*/
Token queuePopData(MyQueue *myQueue)
{
    Token ret;
    int i = 1;
    if( myQueue->queueSize == 0)
        return ret;
    
    ret =  myQueue->queue[0];
    
    for(; i <  myQueue->queueSize; i++)
    {
         myQueue->queue[i - 1] =  myQueue->queue[i];
    }
    
    myQueue->queueSize--;
    
    return ret;
}

