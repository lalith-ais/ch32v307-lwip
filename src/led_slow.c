#include "led_slow.h"

/* LED Configuration */
#define LED_SLOW_PORT    GPIOA
#define LED_SLOW_PIN     GPIO_Pin_15

/* Task Definition */
OS_TASK(led_slow_task, void)
{
    OS_TASK_START(led_slow_task);
    
    while (1)
    {
        /* Toggle LED on PBA15 */
        GPIO_WriteBit(LED_SLOW_PORT, LED_SLOW_PIN, 
                     (BitAction)(1 - GPIO_ReadOutputDataBit(LED_SLOW_PORT, LED_SLOW_PIN)));
        
        /* Wait 1 second */
        OS_TASK_WAITX(OS_SEC_TICKS );
    }
    
    OS_TASK_END(led_slow_task);
}

/* Initialize LED GPIO */
void led_slow_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    /* Enable GPIO Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* Configure PB4 as Push-Pull Output */
    GPIO_InitStructure.GPIO_Pin = LED_SLOW_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_SLOW_PORT, &GPIO_InitStructure);
    
    /* Initial State: LED OFF */
    GPIO_WriteBit(LED_SLOW_PORT, LED_SLOW_PIN, Bit_RESET);
}

