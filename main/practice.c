#include "timers.h"
#include "tasks.h"
void app_main(){
    StartTimers();
    taskCreator("producer");
    taskCreator("consumer"); 
 } 