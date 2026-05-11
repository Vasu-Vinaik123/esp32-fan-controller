#include "driver/gpio.h"
#include "esp_log.h"


#define LED1_PIN  32
#define LED2_PIN  33
#define LED3_PIN  14

static const char *TAG = "LEDS";

void leds_init(void)
{
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3_PIN, GPIO_MODE_OUTPUT);

    gpio_set_level(LED1_PIN, 0);
    gpio_set_level(LED2_PIN, 0);
    gpio_set_level(LED3_PIN, 0);

    ESP_LOGI(TAG, "LEDs initialized on GPIO %d, %d, %d",
             LED1_PIN, LED2_PIN, LED3_PIN);
}

void leds_set_speed_bar(int percent)
{
    gpio_set_level(LED1_PIN, percent > 0  ? 1 : 0);
    gpio_set_level(LED2_PIN, percent > 33 ? 1 : 0);
    gpio_set_level(LED3_PIN, percent > 66 ? 1 : 0);
}