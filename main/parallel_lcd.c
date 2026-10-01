#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define RS GPIO_NUM_14
#define RW GPIO_NUM_13
#define ENABLE GPIO_NUM_11

#define D0 GPIO_NUM_37
#define D1 GPIO_NUM_36
#define D2 GPIO_NUM_35
#define D3 GPIO_NUM_45
#define D4 GPIO_NUM_48
#define D5 GPIO_NUM_47
#define D6 GPIO_NUM_21
#define D7 GPIO_NUM_20

void reset_and_set_pin_modes(void)
{
    gpio_reset_pin(RS);
    gpio_reset_pin(RW);
    gpio_reset_pin(ENABLE);

    gpio_reset_pin(D0);
    gpio_reset_pin(D1);
    gpio_reset_pin(D2);
    gpio_reset_pin(D3);
    gpio_reset_pin(D4);
    gpio_reset_pin(D5);
    gpio_reset_pin(D6);
    gpio_reset_pin(D7);

    gpio_set_direction(RS, GPIO_MODE_OUTPUT);
    gpio_set_direction(RW, GPIO_MODE_OUTPUT);
    gpio_set_direction(ENABLE, GPIO_MODE_OUTPUT);

    gpio_set_direction(D0, GPIO_MODE_OUTPUT);
    gpio_set_direction(D1, GPIO_MODE_OUTPUT);
    gpio_set_direction(D2, GPIO_MODE_OUTPUT);
    gpio_set_direction(D3, GPIO_MODE_OUTPUT);
    gpio_set_direction(D4, GPIO_MODE_OUTPUT);
    gpio_set_direction(D5, GPIO_MODE_OUTPUT);
    gpio_set_direction(D6, GPIO_MODE_OUTPUT);
    gpio_set_direction(D7, GPIO_MODE_OUTPUT);
}
static void lcd_write_byte_command(uint8_t value)
{
    gpio_set_level(RS,0);
    gpio_set_level(RW, 0);

    gpio_set_level(D0, (value >> 0) & 0x01);
    gpio_set_level(D1, (value >> 1) & 0x01);
    gpio_set_level(D2, (value >> 2) & 0x01);
    gpio_set_level(D3, (value >> 3) & 0x01);
    gpio_set_level(D4, (value >> 4) & 0x01);
    gpio_set_level(D5, (value >> 5) & 0x01);
    gpio_set_level(D6, (value >> 6) & 0x01);
    gpio_set_level(D7, (value >> 7) & 0x01);

    gpio_set_level(ENABLE, 1);
    vTaskDelay(pdMS_TO_TICKS(15));
    gpio_set_level(ENABLE, 0);
    vTaskDelay(pdMS_TO_TICKS(15));
}

void initialize_task(void *param)
{
    

    reset_and_set_pin_modes();

    while(1){
        lcd_write_byte_command(0x0F); //F is 15 which is equivalent to 1111 Hence 0x0F=00001111
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
void initialize_screen(){
    xTaskCreate(initialize_task, "Initialize Screen with Screen On, Cursor On and Blinking On", 2048, NULL, 1, NULL);
}