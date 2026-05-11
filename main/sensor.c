#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "dht.h"
#include "esp_log.h"

#define DHT_PIN 4
#define SENSOR_TYPE DHT_TYPE_DHT11

float temp = 0;
float humidity = 0;
static const char *TAG = "SENSOR";

void sensor_task( void *pvParameters){

    while(1){
        if (dht_read_float_data(SENSOR_TYPE, DHT_PIN, &humidity, &temp) == ESP_OK) {
            ESP_LOGI(TAG, "Sensor Value: %.2f", temp);
        } else {
            ESP_LOGE(TAG, "Failed to read from sensor");        

        }
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}