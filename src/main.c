#include "Debug/debug.h"
#include "ch32v30x_eth.h"
#include "main.h"
#include "tiny-os-task.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    Delay_Init();
    USART_Printf_Init(115200);

    lwip_setup();

    printf("Enter main loop.\n");
    while(1) {
	lwip_loop();
    }
}

