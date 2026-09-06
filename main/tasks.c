#include "queues.h"

void createTask(void *pvParameters) {
    char *taskName = (char *)pvParameters;
    taskCreator(taskName);
}