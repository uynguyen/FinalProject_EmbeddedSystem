#include "stm32f4xx.h"
#include <stdio.h>
#include "Uart.h"
#include <string.h>
#include "Led.h"
#include "Controller.h"
/*----------------------------------------------------------------------------*
**                               DEFINE VARIABLE                              *
*----------------------------------------------------------------------------*/
 
int main()
{
    init_Main_Menu();
    
    LED_Init();
    uart_init(9600);
    send_Main_Menu();
    while(1){
        // Do nothing
    };
    
    
    return 1;
}