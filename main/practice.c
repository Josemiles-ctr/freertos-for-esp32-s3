#include "../include/multiple_seven_segment.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{

    xTaskCreate(print_4_digit_num, "Printing A zero", 1024, NULL, 1, NULL);
    
}