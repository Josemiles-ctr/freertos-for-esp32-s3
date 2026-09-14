#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t mutex;

void mutex_task1(void *pvParameters) {
    mutex = xSemaphoreCreateMutex();
    while (1) {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            printf("Task 1: Acquired the mutex\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            printf("Task 1: Releasing the mutex\n");
            xSemaphoreGive(mutex);
        }else {
            printf("Task 1: Failed to acquire the mutex\n");
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
void mutex_task2(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            printf("Task 2: Acquired the mutex\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            printf("Task 2: Releasing the mutex\n");
            xSemaphoreGive(mutex);
        }else {
            printf("Task 2: Failed to acquire the mutex\n");
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}