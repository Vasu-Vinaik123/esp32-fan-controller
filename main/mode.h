#ifndef MODE_H
#define MODE_H

#include "freertos/FreeRTOS.h"

typedef enum {
    MODE_MANUAL = 0,
    MODE_AUTO,
    MODE_BURST,
    MODE_STOP
} mode_t;


void event_task(void *pvParameters);
void mode_task(void *pvParameters);

#endif