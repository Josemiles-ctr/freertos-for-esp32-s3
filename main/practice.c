#include <stdio.h>
#include "rgb_led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(){
    xTaskCreate(rgb_led_init, "RGB LED Task", 2048, NULL, 5, NULL);
    
} 