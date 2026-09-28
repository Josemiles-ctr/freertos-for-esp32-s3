#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"
#include "freertos/task.h"


#define DS GPIO_NUM_1
#define STCP GPIO_NUM_2
#define SHCP GPIO_NUM_21
TaskHandle_t display_task, reset_task;
SemaphoreHandle_t sem1, sem2, sem3;

static int start;
static int to_use=3;
start= &to_use;

static const gpio_num_t pins[3]={
    DS,
    STCP,
    SHCP
};
int power(int a, int b){
    int result=1;
    if(b==0){
        return 1;
    }else if(b==1){
        return a;
    }else{
        for(int i=0;i<b;i++){
            result=result*a;
        }
        return result;
    }
}
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
void incrementTask(void *param){
    xSemaphoreTake(sem1, portMAX_DELAY);
    start = start*start*start;
    xTaskNotifyGive(display_task);
    xTaskNotifyGive(reset_task);
    xSemaphoreGive(sem2);

}
void displayTask(void *param){
    xSemaphoreTake(sem2, portMAX_DELAY);
    int number=start;
    int i =0;
    while(1){
        uint32_t to_prints[4];
        for(int i=0;i<4;i++){
            to_prints[i]=0;
        }
        if(number<10){
            printf("Done");
            break;
        }else{
            int to_print=(number/power(10,i)) %10;
            int binary=digits[to_print];
        }
        number=number/power(10,i);
        to_prints[3-i]=number;
        printf("At index of %d , we have %d\n", 3-i, number);
        i++;
    }

}
void reset_pins(){
    for(int i=0; i<sizeof(pins)/ sizeof(pins[0]); i++){
        gpio_reset_pin(pins[i]);
        gpio_set_direction(pins[i],GPIO_MODE_OUTPUT);
    }
}

void print_number(int *start){
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
    xTaskCreate(incrementTask, "Counting NUmbers", 2048, NULL, 1, NULL);
}
