#include "MyStack.h"


/*----------------------------------------------------------------------------*
**Func name: UART_PushData                                                    *
**Execute: Push a character data into buffer                                  *
**Func params:                                                                *
**                  ch:     Character is pushed into buffer                   *
**Func return: None                                                           *
 *----------------------------------------------------------------------------*/
void stackPushData(Token ch, MyStack *myStack)
{
    while( myStack->stackSize >=  myStack->stackCapacity)
    {
        stackPopData(myStack);
    }
    myStack->data[myStack->stackSize++] = ch;
}

/*----------------------------------------------------------------------------*
**Func name: UART_PopData                                                     *
**Execute: Pop a character data from buffer                                   *
**Func params: None                                                           *
**Func return: None                                                           *
**                  char:     Character is popped from buffer                 *
 *----------------------------------------------------------------------------*/
Token stackPopData(MyStack *myStack)
{
    Token ret;

    if( myStack->stackSize == 0)
        return 0;
    
    ret =  myStack->data[myStack->stackSize - 1];
    
    
    myStack->stackSize--;
    
    return ret;
}

