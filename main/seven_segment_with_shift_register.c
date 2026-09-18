#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define DS GPIO_NUM_1
#define STCP GPIO_NUM_2
#define SHCP GPIO_NUM_21

static const gpio_num_t pins[3]={
    DS,
    STCP,
    SHCP
};

static const uint8_t digits[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};
void reset_pins(){
    for(int i=0; i<sizeof(pins)/ sizeof(pins[0]); i++){
        gpio_reset_pin(pins[i]);
        gpio_set_direction(pins[i],GPIO_MODE_OUTPUT);
    }
}

void count_numbers(void *pvParameter){
    reset_pins();
    for(int i=0; i<sizeof(digits)/ sizeof(digits[0]); i++){
        gpio_set_level(STCP,0);
        for(int j=7; j>=0;j--){
            gpio_set_level(SHCP, 0);
            gpio_set_level(DS, (digits[i]>>j)&1);
            gpio_set_level(SHCP,1);
        }
        gpio_set_level(STCP,1);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void run_numbers(){
    xTaskCreate(count_numbers, "Counting NUmbers", 2048, NULL, 1, NULL);
}