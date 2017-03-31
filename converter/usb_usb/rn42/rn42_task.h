#ifndef RN42_TASK_H
#define RN42_TASK_H

#include <stdbool.h>
#include "rn42.h"

typedef enum {
    BT_LED_ON,
    BT_LED_OFF,
    BT_LED_TOG,
} bt_led_t;

void rn42_task_init(void);
void rn42_task(void);

#endif
