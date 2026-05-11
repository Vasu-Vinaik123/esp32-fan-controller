#ifndef INPUT_H
#define INPUT_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

extern QueueHandle_t button_queue;

void input_init(void);

#endif