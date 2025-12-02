#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

void TaskPrint(void *prParameters);

SemaphoreHandle_t sems[3];

static int index = 0;
static int seq[] = {0,1,2,2,1,0};
#define SEQ_LEN 6

// Cada 50ms
#define DELAY 50 / portTICK_PERIOD_MS

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  for(int i=0; i<3; i++) {
    sems[i] = xSemaphoreCreateBinary();
  }

  index = 0;
  xSemaphoreGive(sems[seq[index]]);
  xTaskCreate(TaskPrint, "Tarea 1", 1000, (void*) (intptr_t) 0, 5, NULL);
  xTaskCreate(TaskPrint, "Tarea 2", 1000, (void*) (intptr_t) 1, 5, NULL);
  xTaskCreate(TaskPrint, "Tarea 3", 1000, (void*) (intptr_t) 2, 5, NULL);
  
  vTaskStartScheduler();
}


void loop() { }

void TaskPrint(void *prParameters) {
  int id = (int)(intptr_t) prParameters;

  for(;;) {
    xSemaphoreTake(sems[id], portMAX_DELAY);
    Serial.println(String("Tarea " + String(id+1)));
    index = (index+1) % SEQ_LEN;
    xSemaphoreGive(sems[seq[index]]);
    vTaskDelay(DELAY);
  }
}