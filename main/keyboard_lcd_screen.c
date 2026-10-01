#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//LCD SCREEN PINS
#define RS GPIO_NUM_14
#define RW GPIO_NUM_13
#define ENABLE GPIO_NUM_11

#define D0 GPIO_NUM_37
#define D1 GPIO_NUM_36
#define D2 GPIO_NUM_35
#define D3 GPIO_NUM_41
#define D4 GPIO_NUM_48
#define D5 GPIO_NUM_47
#define D6 GPIO_NUM_21
#define D7 GPIO_NUM_20


// KEYBOARD PINS
#define R1 GPIO_NUM_10
#define R2 GPIO_NUM_9
#define R3 GPIO_NUM_8
#define R4 GPIO_NUM_18

#define C1 GPIO_NUM_7
#define C2 GPIO_NUM_6
#define C3 GPIO_NUM_5
#define C4 GPIO_NUM_4

gpio_num_t lcd_pins[11]={
    D0, D1, D2, D3, D4, D5, D6, D7, RS, RW, ENABLE
};
gpio_num_t row_pins[4]={R1, R2, R3, R4};
gpio_num_t column_pins[4]={C1, C2, C3, C4};
const uint8_t zero=0x30;
const uint8_t one=0x31;
const uint8_t two=0x32;
const uint8_t three=0x33;
const uint8_t four=0x34;
const uint8_t five=0x35;
const uint8_t six =0x36;
const uint8_t seven =0x37;
const uint8_t eight =0x38;
const uint8_t nine =0x39;

const uint8_t A = 0x41;
const uint8_t B = 0x42;
const uint8_t C = 0x43;
const uint8_t D = 0x44;

const uint8_t star = 0x2A;
const uint8_t hash = 0x23;

uint8_t buttons[4][4]={
    {one, two, three, A},
    {four, five, six, B},
    {seven, eight, nine, C},
    {star, zero, hash, D},
};
static void reset_and_set_pin_modes(){
    for(int i=0; i<sizeof(lcd_pins)/ sizeof(lcd_pins[0]); i++){
        gpio_reset_pin(lcd_pins[i]);
        gpio_set_direction(lcd_pins[i], GPIO_MODE_OUTPUT);
    }
    for(int i=0; i<sizeof(row_pins)/ sizeof(row_pins[0]); i++){
        gpio_reset_pin(row_pins[i]);
        gpio_set_direction(row_pins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(row_pins[i], 1);
    }
    for(int i=0; i<sizeof(column_pins)/ sizeof(column_pins[0]); i++){
        gpio_reset_pin(column_pins[i]);
        gpio_set_direction(column_pins[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(column_pins[i], GPIO_PULLUP_ONLY);
    }
    gpio_set_level(RS, 0);
    gpio_set_level(RW, 0);
    gpio_set_level(ENABLE, 0);
}

static void lcd_write_byte(uint8_t value, int rs , int rw){
    gpio_set_level(RS,rs);
    gpio_set_level(RW, rw);
    for(int i=0; i<8; i++){
        gpio_set_level(lcd_pins[i], (value >> i) & 0x01);
    }
    gpio_set_level(ENABLE, 1);
    vTaskDelay(pdMS_TO_TICKS(15));
    gpio_set_level(ENABLE, 0);
    vTaskDelay(pdMS_TO_TICKS(15));
}
static void get_click(){
    for(int row=0; row<4; row++){
        gpio_set_level(row_pins[row], 0);
        vTaskDelay(pdMS_TO_TICKS(1));

        for(int column=0; column<4; column++){
            if(gpio_get_level(column_pins[column]) == 0){
                lcd_write_byte(buttons[row][column], 1, 0);
                vTaskDelay(pdMS_TO_TICKS(20));

                while(gpio_get_level(column_pins[column]) == 0){
                    vTaskDelay(pdMS_TO_TICKS(10));
                }

                gpio_set_level(row_pins[row], 1);
                return;
            }
        }

        gpio_set_level(row_pins[row], 1);
    }
}

void print_to_screen_task(void *param){
    reset_and_set_pin_modes();
    vTaskDelay(pdMS_TO_TICKS(50));

    lcd_write_byte(0x38, 0, 0);  // 8-bit mode, 2-line display
    lcd_write_byte(0x0F, 0, 0);  // display + cursor on
    lcd_write_byte(0x01, 0, 0);  // clear display
    lcd_write_byte(0x06, 0, 0);  // cursor increments after each character

    while(1){
        get_click();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
void print_to_screen(void){
    xTaskCreate(print_to_screen_task, "Initialize Screen with Screen On, Cursor On and Blinking On", 2048, NULL, 1, NULL);
}
