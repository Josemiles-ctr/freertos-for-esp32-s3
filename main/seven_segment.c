#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "freertos/list.h"


#define sevseg_A GPIO_NUM_15
#define sevseg_B GPIO_NUM_16
#define sevseg_C GPIO_NUM_21
#define sevseg_D GPIO_NUM_4
#define sevseg_E GPIO_NUM_5
#define sevseg_F GPIO_NUM_7
#define sevseg_G GPIO_NUM_6
#define sevseg_DP GPIO_NUM_20

static gpio_num_t segments[]={
    sevseg_A, 
    sevseg_B, 
    sevseg_C, 
    sevseg_D, 
    sevseg_E, 
    sevseg_F, 
    sevseg_G, 
    sevseg_DP,
};
// 000010101
#include <stdint.h>
//        a
//      *****
//    f * g * b
//      *****
//    e *   * c
//      *****
//        d
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
static void gpio_init(){
        for (int i=0; i < sizeof(segments)/ sizeof(segments[0]); i++){
            gpio_reset_pin(segments[i]);
            gpio_set_direction(segments[i], GPIO_MODE_OUTPUT);
            gpio_set_level(segments[i], 0);     
        }
    }
void display_digits(){
    for(int n=0; n<sizeof(digits)/ sizeof(digits[0]); n++){
        for (int bit = 0; bit < 8; bit++){
            gpio_set_level( segments[bit],(digits[n] >> bit) & 1);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
void print_numbers(void *pvParameters){
    gpio_init();
    while (1){
        display_digits();
    }
}