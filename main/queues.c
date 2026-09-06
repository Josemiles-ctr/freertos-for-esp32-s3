#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <stdio.h>
#include <string.h>
QueueHandle_t queue;

void producer_task(void *pvParameters){
    int counter=0;
   while(1){
        if (xQueueSend(queue, &counter, portMAX_DELAY) != pdPASS) {
            printf("Failed to send to queue!\n");
        } else {
            printf("Producer sent: %d\n", counter);
        }
        counter++;
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}
void consumer_task(void *pvParameters){
    int received_value;
    while(1){
        if (xQueueReceive(queue, &received_value, portMAX_DELAY) == pdPASS) {
            printf("Consumer received: %d\n", received_value);
        } else {
            printf("Failed to receive from queue!\n");
        }
    }
}

void taskCreator(char name[]){
    queue = xQueueCreate(5, sizeof(int));
    if (strcmp(name, "producer") == 0) {
        xTaskCreate(producer_task, "Producer Task", 2048, NULL, 1, NULL);
    } else if (strcmp(name, "consumer") == 0) {
        xTaskCreate(consumer_task, "Consumer Task", 2048, NULL, 1, NULL);
    } else {
        printf("Invalid task type: %s\n", name);
    }
}