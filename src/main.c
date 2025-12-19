#include "Debug/debug.h"
#include "ch32v30x_eth.h"
#include "main.h"
#include "tiny-os-task.h"

int main(void)
{
    Delay_Init();
    USART_Printf_Init(115200);

    lwip_setup(); // initialise os related task

    printf("Enter main loop.\n");
    while(1) {
	os_task_loop();
    }
}

