#include "mode.h"
#include "input.h"
#include "motor.h"
#include "sensor.h"
#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define SPEED 50
#define BUTTON_PIN 12


static int64_t last_event_time = 0;

extern QueueHandle_t button_queue;
extern float temp;

const char* mode_names[] = {
    "MANUAL",
    "AUTO",
    "BURST",
    "STOP"
};


void event_task(void *pvParamaters){
    
    int event = 1;
    int last_button_state = 1;
    int current_button_state = 0;
    int64_t current_time;
    while(1){
        current_button_state = gpio_get_level(BUTTON_PIN);
        current_time = esp_timer_get_time()/1000;   // Convert to ms
        if (current_button_state == 0 && last_button_state == 1){
            
            if(current_time - last_event_time > 500){ // 500ms debounce
                xQueueSend(button_queue, &event, pdMS_TO_TICKS(10));
                last_event_time = current_time;
            }
            
        }
        last_button_state = current_button_state;
        vTaskDelay(pdMS_TO_TICKS(50));

    }
}

void mode_task(void *pvParamaters){
    mode_t current_mode = MODE_MANUAL;

    printf("Current Mode: %s\n", mode_names[current_mode]);
    int button_event;

    while(1){
        if (xQueueReceive(button_queue, &button_event, pdMS_TO_TICKS(10)) == pdTRUE){


            current_mode++;
            if (current_mode > MODE_STOP) current_mode = MODE_MANUAL;
                        
            printf("Mode changed to : %s\n", mode_names[current_mode]);
    
        }


        switch(current_mode){

            case MODE_MANUAL:
                motor_set_speed(SPEED);
                leds_set_speed_bar(SPEED);
                break;

            case MODE_AUTO:
                motor_set_speed(temp * 100 / 50); // Map 0-50°C to 0-100% speed
                leds_set_speed_bar(temp * 100 / 50);
                break;
                
            case MODE_BURST:
                motor_set_speed(100);
                leds_set_speed_bar(100);
                vTaskDelay(pdMS_TO_TICKS(300));
                motor_set_speed(0);
                leds_set_speed_bar(0);
                vTaskDelay(pdMS_TO_TICKS(300));
                break;
            
            case MODE_STOP:
                motor_stop();
                leds_set_speed_bar(0);
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}