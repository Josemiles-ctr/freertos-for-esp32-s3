#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/seven_segment.h"

void app_main(){
    xTaskCreate(test_segments, "Seven Segment Display", 2048, NULL, 1, NULL);     
} 