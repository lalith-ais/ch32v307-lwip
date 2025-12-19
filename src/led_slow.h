#ifndef LED_SLOW_H
#define LED_SLOW_H

#include "ch32v30x.h"
#include "tiny-macro-os.h"

/* Task Prototype */
OS_TASK(led_slow_task, void);

/* Public API */
void led_slow_init(void);
void led_slow_create_task(void);

#endif /* LED_SLOW_H */
