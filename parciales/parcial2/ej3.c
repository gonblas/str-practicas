#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define HIGH_PRIORITY 2
#define LOW_PRIORITY 1
#define MS_HIGH_DELAY pdMS_TO_TICKS(100)
#define MS_LOW_DELAY pdMS_TO_TICKS(50)


static int counter = 0;
void TaskHighPriority(void *pvParameters);
void TaskLowPriority(void *pvParameters);

SemaphoreHandle_t mutex;


void setup() {
  Serial.begin(9600);

  mutex = xSemaphoreCreateMutex();

  xTaskCreate(TaskHighPriority, "HighPriority", 128, NULL, HIGH_PRIORITY, NULL);
  xTaskCreate(TaskLowPriority, "1", 128, (void *)(intptr_t)0, LOW_PRIORITY, NULL);
  xTaskCreate(TaskLowPriority, "2", 128, (void *)(intptr_t)1, LOW_PRIORITY, NULL);

  vTaskStartScheduler();
}


void loop() {}


void TaskHighPriority(void *pvParameters) {
  for (;;) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    counter++;
    xSemaphoreGive(mutex);
    vTaskDelay(MS_HIGH_DELAY);
  }
}

void TaskLowPriority(void *pvParameters) {
const int id = (int)(intptr_t)pvParameters;
  for (;;) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    Serial.println(String("Task ") + String(id) + String(": Counter = ") + String(counter));
    counter+=2;
    xSemaphoreGive(mutex);
    vTaskDelay(MS_LOW_DELAY);
  }
}