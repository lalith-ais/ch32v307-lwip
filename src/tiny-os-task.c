#include "lwip_task.h"
#include "tiny-macro-os.h"
#include "debug.h"

void os_task_loop() {
    OS_RUN_TASK(os_lwip);
    OS_RUN_TASK(os_lwip_timeouts);
}
