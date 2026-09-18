#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiver_task_handle=NULL;

void sender (void *pvParameter){
    while (1)
    {
        xTaskNotifyGive(receiver_task_handle);
        printf("Sender Notifying Receiver\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}
void receiver (void *pvParameter){
    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("Receiver Task Notified\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    

}
void task_Notifications(){
    xTaskCreate(receiver, "Receiver Task", 2048, NULL, 1, &receiver_task_handle);
    xTaskCreate(sender, "Sender Task", 2048, NULL, 1, NULL);
}