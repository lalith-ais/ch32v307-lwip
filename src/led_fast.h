#ifndef LED_FAST_H
#define LED_FAST_H

#include "ch32v30x.h"
#include "tiny-macro-os.h"

/* Task Prototype */
OS_TASK(led_fast_task, void);

/* Public API */
void led_fast_init(void);
void led_fast_create_task(void);

#endif /* LED_FAST_H */
