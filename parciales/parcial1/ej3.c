#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
void TaskPrint(void *pvParameters);

SemaphoreHandle_t sems[3];

static const uint8_t seq[] = {0, 1, 2, 2, 1, 0};
#define LEN_SEQ 6
static int index = 0;

const TickType_t DELAY = pdMS_TO_TICKS(500);

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < 3; ++i) {
    sems[i] = xSemaphoreCreateBinary();
  }

  xSemaphoreGive(sems[seq[0]]);
  index = 0;
  xTaskCreate(TaskPrint, "Tarea 1", 128, (void *)(intptr_t)0, 1, NULL);
  xTaskCreate(TaskPrint, "Tarea 2", 128, (void *)(intptr_t)1, 1, NULL);
  xTaskCreate(TaskPrint, "Tarea 3", 128, (void *)(intptr_t)2, 1, NULL);

  vTaskStartScheduler();
}

void loop() {}

void TaskPrint(void *pvParameters)
{
  const int id = (int)(intptr_t)pvParameters;

  for (;;)
  {
    xSemaphoreTake(sems[id], portMAX_DELAY);
    Serial.println(String("Tarea ") + String(id + 1));
    index = (index + 1) % LEN_SEQ;
    int nextTask = seq[index];
    xSemaphoreGive(sems[nextTask]);
    vTaskDelay(DELAY);
  }
}