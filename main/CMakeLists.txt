idf_component_register(SRCS "led.c" "input.c" "motor.c" "mode.c" "sensor.c" "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES "driver" "esp_adc"
                    REQUIRES "esp_driver_gpio"
                    "esp_driver_ledc"
                    "esp_adc"
                    "esp_timer"
                    "log"
                    "freertos")
