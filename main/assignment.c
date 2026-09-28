#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdio.h>

#define LED_PIN GPIO_NUM_7


void reset_pin(){
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
}

// static const uint8_t digits[10] = {
//     0b00111111, // 0
//     0b00000110, // 1
//     0b01011011, // 2
//     0b01001111, // 3
//     0b01100110, // 4
//     0b01101101, // 5
//     0b01111101, // 6
//     0b00000111, // 7
//     0b01111111, // 8
//     0b01101111  // 9
// };

void print_numbers(void *param){
    reset_pin();
    while (1)
    {
        printf("Lighting Bulb");
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(LED_PIN, 0);
    }
    

}
void run_led(){
    xTaskCreate(print_numbers, "Print NUmbers", 2048, NULL, 1, NULL);
}

