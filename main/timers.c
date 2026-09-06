#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#define one_shot_timer_period pdMS_TO_TICKS(1000)
#define auto_reload_timer_period pdMS_TO_TICKS(500)

TimerHandle_t xOneShotTimer, xAutoReloadTimer;
BaseType_t oneShotTimerStarted, autoReloadTimerStarted;

void TimerCallback(TimerHandle_t xtimer){
    uint32_t ulExecutionCount;
    ulExecutionCount = (uint32_t)pvTimerGetTimerID(xtimer);
    ulExecutionCount++;
    vTimerSetTimerID(xtimer, (void *) ulExecutionCount);
    if (xtimer==xOneShotTimer){
        printf("The ID count for one shot timer is %lu\n", ulExecutionCount);
    }
    else {
        printf("The ID count for auto reload timer is %lu\n", ulExecutionCount);
    }
    
    if (ulExecutionCount==5){
        xTimerStop(xtimer, 0);
    }
}

void StartTimers(){
    xOneShotTimer= xTimerCreate(
        "oneShotTimer",
        one_shot_timer_period,
        pdFALSE,
        0,
        TimerCallback
    );
    xAutoReloadTimer= xTimerCreate(
        "autoReloadTimer",
        auto_reload_timer_period,
        pdTRUE,
        0,
        TimerCallback
    );
    if (xOneShotTimer !=NULL && xAutoReloadTimer !=NULL){
        oneShotTimerStarted = xTimerStart(xOneShotTimer, 0);
        autoReloadTimerStarted= xTimerStart(xAutoReloadTimer, 0);
        
    }else{
        printf("Failed to create Timers\n");
    }
}

