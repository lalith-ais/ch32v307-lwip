#include "main.h"

void systick_start(void) {

    NVIC_SetPriority(SysTicK_IRQn,0xff);
    NVIC_EnableIRQ(SysTicK_IRQn);
    SysTick->CTLR= 0;
    SysTick->SR  = 0;
    SysTick->CNT = 0;
    SysTick->CMP = SystemCoreClock / OS_SEC_TICKS;
    SysTick->CTLR= 0xf;
}


int main(void)
{
    Delay_Init();
    USART_Printf_Init(115200);
	
	systick_start();
	led_fast_init();
	
	OS_INIT_TASKS();
    OS_TASK_EXIT_ANOTHER(os_lwip_timeouts); 

    while(1) {
        OS_RUN_TASK(os_lwip);
	    OS_RUN_TASK(os_lwip_timeouts);
	    OS_RUN_TASK(led_fast_task);
	    
	}
}

