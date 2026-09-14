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
static void gpio_init(){
    for (int i=0; i < sizeof(segments)/ sizeof(segments[0]); i++){
        gpio_reset_pin(segments[i]);
        gpio_set_direction(segments[i], GPIO_MODE_OUTPUT);
        gpio_set_level(segments[i], 0);
    }
}
static void reset_pins(){
    for (int i=0; i < sizeof(segments)/ sizeof(segments[0]); i++){
        gpio_set_level(segments[i],0);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
}

void figure_zero(){
    gpio_set_level(segments[0], 1);
    gpio_set_level(segments[1], 1);
    gpio_set_level(segments[2], 1);
    gpio_set_level(segments[3], 1);
    gpio_set_level(segments[4], 1);
    gpio_set_level(segments[5], 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
}

void figure_one(){
    gpio_set_level(segments[1], 1);
    gpio_set_level(segments[2], 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
}
void figure_two(){
    gpio_set_level(segments[0], 1);
    gpio_set_level(segments[1], 1);
    gpio_set_level(segments[3], 1);
    gpio_set_level(segments[4], 1);
    gpio_set_level(segments[6], 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
}
void figure_three(){
    gpio_set_level(segments[0], 1);
    gpio_set_level(segments[1], 1);
    gpio_set_level(segments[2], 1);
    gpio_set_level(segments[3], 1);
    gpio_set_level(segments[6], 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
}
void figure_four(){
    gpio_set_level(segments[1], 1);
    gpio_set_level(segments[2], 1);
    gpio_set_level(segments[5], 1);
    gpio_set_level(segments[6], 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
}
void figure_five(){
    gpio_set_level(segments[0], 1);
    gpio_set_level(segments[2], 1);
    gpio_set_level(segments[3], 1);
    gpio_set_level(segments[5], 1);
    gpio_set_level(segments[6], 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
}
void test_segments(void *pvParameters){
    gpio_init();
    while (1)
    {
        figure_zero();
        reset_pins();
        figure_one();
        reset_pins();
        figure_two();
        reset_pins();
        figure_three();
        reset_pins();
        figure_four();
        reset_pins();
        figure_five();
        reset_pins();
    }
    

}