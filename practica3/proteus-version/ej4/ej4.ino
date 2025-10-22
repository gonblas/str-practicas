#include <Arduino_FreeRTOS.h>

void TaskPrint(void *pvParameters);
void TaskManager(void *pvParameters);

TaskHandle_t hT1, hT2, hT3;

void setup()
{
  Serial.begin(9600);

  xTaskCreate(
      TaskPrint,
      "Tarea 1",
      128,
      (void *)"Tarea 1",
      1,
      &hT1);

  xTaskCreate(
      TaskPrint,
      "Tarea 2",
      128,
      (void *)"Tarea 2",
      1,
      &hT2);

  xTaskCreate(
      TaskPrint,
      "Tarea 3",
      128,
      (void *)"Tarea 3",
      1,
      &hT3);

  xTaskCreate(
      TaskManager,
      "TaskManager",
      128,
      NULL,
      1,
      NULL);

  vTaskStartScheduler();
}


void loop() {}

void TaskPrint(void *pvParameters)
{
  char *taskName = (char *)pvParameters;

  for (;;)
  {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    Serial.println(String(taskName));
  }
}

void TaskManager(void *pvParameters)
{
  const TickType_t d = pdMS_TO_TICKS(500);
  for (;;)
  { 
    Serial.println("-------Secuencia A-------");
    xTaskNotifyGive(hT1); vTaskDelay(d);
    xTaskNotifyGive(hT3); vTaskDelay(d);
    xTaskNotifyGive(hT2); vTaskDelay(d);

    Serial.println("-------Secuencia B-------");
    xTaskNotifyGive(hT2); vTaskDelay(d);
    xTaskNotifyGive(hT2); vTaskDelay(d);
    xTaskNotifyGive(hT3); vTaskDelay(d);
    xTaskNotifyGive(hT1); vTaskDelay(d);

    Serial.println("-------Secuencia C-------");
    xTaskNotifyGive(hT3); vTaskDelay(d);
    xTaskNotifyGive(hT3); vTaskDelay(d);
    xTaskNotifyGive(hT3); vTaskDelay(d);
    xTaskNotifyGive(hT1); vTaskDelay(d);
    xTaskNotifyGive(hT2); vTaskDelay(d);
  }
}