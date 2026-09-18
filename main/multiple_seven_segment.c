#include "multiple_seven_segment.h"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define DS      GPIO_NUM_2
#define SHCP    GPIO_NUM_4
#define STCP    GPIO_NUM_9

#define DIG1    GPIO_NUM_10
#define DIG2    GPIO_NUM_11
#define DIG3    GPIO_NUM_12
#define DIG4    GPIO_NUM_13

static gpio_num_t segments[7]={
    DS,
    SHCP,
    STCP,
    DIG1,
    DIG2,
    DIG3,
    DIG4,
};
static const uint8_t digits[5] = {
    0b01011011, // 2
    0b01101101, // 5
    0b10000000, //dp
    0b00111111, // 0
    0b01101111  // 9
};
void mode_and_reset(void){
    for (int i=0; i<sizeof(segments)/ sizeof(segments[0]); i++){
        gpio_reset_pin(segments[i]);
        gpio_set_direction(segments[i],GPIO_MODE_OUTPUT);
        gpio_set_level(segments[i],0);
    }
}
void print_4_digit_num(void *pvParameter){
    mode_and_reset();
    while(1){
        for(int i=0; i<sizeof(digits)/sizeof(digits[0]); i++){
            gpio_set_level(DIG1, 1);
            gpio_set_level(DIG2, 1);
            gpio_set_level(DIG3, 1);
            gpio_set_level(DIG4, 1);

            gpio_set_level(STCP, 0);
            for(int j=7; j>=0; j--){ 
                gpio_set_level(SHCP, 0);
                gpio_set_level(DS, (digits[i]>>j)&1);
                gpio_set_level(SHCP, 1);
            }
            gpio_set_level(STCP, 1);

            switch (i){
                case 0: 
                    gpio_set_level(DIG1, 0); 
                    break;
                case 1: 
                    gpio_set_level(DIG2, 0); 
                    break;
                case 2:
                    gpio_set_level(DIG2, 0); 
                    break;
                case 3: 
                    gpio_set_level(DIG3, 0); 
                    break;
                case 4: 
                    gpio_set_level(DIG4, 0); 
                    break;
            }
            vTaskDelay(pdMS_TO_TICKS(3));
        }
    }
}