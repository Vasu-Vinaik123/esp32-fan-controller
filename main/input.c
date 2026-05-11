#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"


#define BUTTON_PIN 12


QueueHandle_t button_queue;


void input_init(void){

    button_queue = xQueueCreate(10, sizeof(int));

    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
}

