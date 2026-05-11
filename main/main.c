#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor.h"
#include "sensor.h"
#include "input.h"
#include "mode.h"
#include "led.h"




void app_main(void)
{

    motor_init();
    input_init();
    leds_init();

    xTaskCreate(event_task,
                "event_task",
                2048,
                NULL,
                1,
                NULL);

    xTaskCreate(sensor_task,
                "sensor_task",
                2048,
                NULL,
                1,
                NULL);

    xTaskCreate(mode_task,
                "mode_task",
                4096,
                NULL,
                2,
                NULL);
}