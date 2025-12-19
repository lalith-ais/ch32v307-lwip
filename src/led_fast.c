#include "led_fast.h"

/* LED Configuration */
#define LED_FAST_PORT    GPIOB
#define LED_FAST_PIN     GPIO_Pin_4

/* Task Definition */
OS_TASK(led_fast_task, void)
{
    OS_TASK_START(led_fast_task);
    
    while (1)
    {
        /* Toggle LED on PB4 */
        GPIO_WriteBit(LED_FAST_PORT, LED_FAST_PIN, 
                     (BitAction)(1 - GPIO_ReadOutputDataBit(LED_FAST_PORT, LED_FAST_PIN)));
        
        /* Wait 250ms (0.25 seconds) */
        OS_TASK_WAITX(OS_SEC_TICKS / 4);
    }
    
    OS_TASK_END(led_fast_task);
}

/* Initialize LED GPIO */
void led_fast_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    /* Enable GPIO Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    /* Configure PB4 as Push-Pull Output */
    GPIO_InitStructure.GPIO_Pin = LED_FAST_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_FAST_PORT, &GPIO_InitStructure);
    
    /* Initial State: LED OFF */
    GPIO_WriteBit(LED_FAST_PORT, LED_FAST_PIN, Bit_RESET);
}

