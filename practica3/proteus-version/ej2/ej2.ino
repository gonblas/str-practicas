// Desarrolle una aplicación de planificación que contenga 3 tareas. Las mismas deben 
// competir por imprimir en la terminal un mensaje con el nombre de cada tarea. 
// Realice pruebas variando las prioridades de cada una de las tareas, generando así 
// diferentes escenarios en el mensaje de salida de la terminal. 

#include <Arduino_FreeRTOS.h>

void TaskPrint(void *pvParameters);

void setup() {
  Serial.begin(9600);

  xTaskCreate(
    TaskPrint,          // Function that implements the task.
    "Task1",            // Text name for the task.
    128,                // Stack size in words, not bytes.
    (void*)"Tarea 1",   // Parameter passed into the task.
    1,                  // Priority at which the task is created.
    NULL);              // Pointer to the task created in the system.

  xTaskCreate(
    TaskPrint,
    "Task2",
    128,
    (void*)"Tarea 2",
    3,
    NULL);

  xTaskCreate(
    TaskPrint,
    "Task3",
    128,
    (void*)"Tarea 3",
    2,
    NULL);

  vTaskStartScheduler();
}

void loop() {}

void TaskPrint(void *pvParameters) {
  char* taskName = (char*) pvParameters;

  for (;;) {
    Serial.println(String(taskName));
    vTaskDelay(100);
  }
}