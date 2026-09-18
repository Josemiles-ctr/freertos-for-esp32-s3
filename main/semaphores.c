#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "semaphore.h"

SemaphoreHandle_t semaphore=NULL;

void producer(void * params){
    semaphore=xSemaphoreCreateBinary();
    while (1)
    {
        xSemaphoreGive(semaphore);
        printf("Producer Given out semaphore\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}
void consumer(void * parama){
    while (1)
    {
        xSemaphoreTake(semaphore, portMAX_DELAY);
        printf("Consumer Received Semaphore\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}
void start_semaphores(){
    xTaskCreate(producer, "Producer Task", 2048, NULL, 1, NULL);
    xTaskCreate(consumer, "Consumer Task", 2048, NULL, 1, NULL);
}