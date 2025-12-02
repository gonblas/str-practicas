#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t sem[3];
volatile int index = 0;

const int seq[] = {0, 1, 2, 2, 1, 0};
#define SEQ_LEN 6
#define PRIORITY 1
#define DELAY pdMS_TO_TICKS(50)

void TaskPrint(void* params);

void setup() {
  Serial.begin(9600);
  
  for(int i=0; i<3; i++) {
    sem[i] = xSemaphoreCreateBinary();
  }

  xSemaphoreGive(sem[seq[index]]);

  vTaskCreate(TaskPrint, "Tarea 1", 1000, (void*) (intptr_t)0, PRIORITY, NULL);
  vTaskCreate(TaskPrint, "Tarea 2", 1000, (void*) (intptr_t)1, PRIORITY, NULL);
  vTaskCreate(TaskPrint, "Tarea 3", 1000, (void*) (intptr_t)2, PRIORITY, NULL);

  vTaskStartScheduler();
}


void loop () { }

void TaskPrint(void* params) {
  int id = (int)(intptr_t) params;
  for(;;) { 
    xSemaphoreTake(sem[index]);
    Serial.println(String("Tarea "), String(id+1));
    index = (index+1) % SEQ_LEN;
    xSemaphoreGive(sem[seq[index]]);
    vTaskDelay(DELAY);
  }
}