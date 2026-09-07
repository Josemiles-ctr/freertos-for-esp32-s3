#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include <stdio.h>
#define RED_LED_PIN  GPIO_NUM_21
#define GREEN_LED_PIN  GPIO_NUM_20
#define BLUE_LED_PIN  GPIO_NUM_19

void rgb_led_init(void *param) {
    gpio_reset_pin(RED_LED_PIN);
    gpio_reset_pin(GREEN_LED_PIN);
    gpio_reset_pin(BLUE_LED_PIN);

    gpio_set_direction(RED_LED_PIN, GPIO_MODE_OUTPUT);    
    gpio_set_direction(GREEN_LED_PIN, GPIO_MODE_OUTPUT);   
    gpio_set_direction(BLUE_LED_PIN, GPIO_MODE_OUTPUT);

    /*Achieving primary colors by turning on one LED at a time, secondary colors by turning on two LEDs at a time with delays continuously in an infinite loop
    */
    while(true){
        // Red
        gpio_set_level(RED_LED_PIN, 1);
        gpio_set_level(GREEN_LED_PIN, 0);
        gpio_set_level(BLUE_LED_PIN, 0);
        printf("Red LED ON\n");
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Green
        gpio_set_level(RED_LED_PIN, 0);
        gpio_set_level(GREEN_LED_PIN, 1);
        gpio_set_level(BLUE_LED_PIN, 0);
        printf("Green LED ON\n");
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Blue
        gpio_set_level(RED_LED_PIN, 0);
        gpio_set_level(GREEN_LED_PIN, 0);
        gpio_set_level(BLUE_LED_PIN, 1);
        printf("Blue LED ON\n");
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Yellow (Red + Green)
        gpio_set_level(RED_LED_PIN, 1);
        gpio_set_level(GREEN_LED_PIN, 1);
        gpio_set_level(BLUE_LED_PIN, 0);
        printf("Yellow LED ON\n");
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Cyan (Green + Blue)
        gpio_set_level(RED_LED_PIN, 0);
        gpio_set_level(GREEN_LED_PIN, 1);
        gpio_set_level(BLUE_LED_PIN, 1);
        printf("Cyan LED ON\n");
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Magenta (Red + Blue)
        gpio_set_level(RED_LED_PIN, 1);
        gpio_set_level(GREEN_LED_PIN, 0);
        gpio_set_level(BLUE_LED_PIN, 1);
        printf("Magenta LED ON\n");
        vTaskDelay(pdMS_TO_TICKS(1000));

        for(int i = 0; i < 3; i++) {
            // Red
            gpio_set_level(RED_LED_PIN, 1);
            gpio_set_level(GREEN_LED_PIN, 0);
            gpio_set_level(BLUE_LED_PIN, 0);
            printf("Red LED ON\n");
            vTaskDelay(pdMS_TO_TICKS(500));

            // Green
            gpio_set_level(RED_LED_PIN, 0);
            gpio_set_level(GREEN_LED_PIN, 1);
            gpio_set_level(BLUE_LED_PIN, 0);
            printf("Green LED ON\n");
            vTaskDelay(pdMS_TO_TICKS(500));

            // Blue
            gpio_set_level(RED_LED_PIN, 0);
            gpio_set_level(GREEN_LED_PIN, 0);
            gpio_set_level(BLUE_LED_PIN, 1);
            printf("Blue LED ON\n");
            vTaskDelay(pdMS_TO_TICKS(500));

            // Yellow (Red + Green)
            gpio_set_level(RED_LED_PIN, 1);
            gpio_set_level(GREEN_LED_PIN, 1);
            gpio_set_level(BLUE_LED_PIN, 0);
            printf("Yellow LED ON\n");
            vTaskDelay(pdMS_TO_TICKS(500));

            // Cyan (Green + Blue)
            gpio_set_level(RED_LED_PIN, 0);
            gpio_set_level(GREEN_LED_PIN, 1);
            gpio_set_level(BLUE_LED_PIN, 1);
            printf("Cyan LED ON\n");
            vTaskDelay(pdMS_TO_TICKS(500));

            // Magenta (Red + Blue)
            gpio_set_level(RED_LED_PIN, 1);
            gpio_set_level(GREEN_LED_PIN, 0);
            gpio_set_level(BLUE_LED_PIN, 1);
            printf("Magenta LED ON\n");
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
    
}