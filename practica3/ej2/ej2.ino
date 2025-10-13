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
    (void*)"Task1",     // Parameter passed into the task.
    1,                  // Priority at which the task is created.
    NULL);              // Pointer to the task created in the system.

  xTaskCreate(
    TaskPrint,
    "Task2",
    128,
    (void*)"Task2",
    10,
    NULL);

  xTaskCreate(
    TaskPrint,
    "Task3",
    128,
    (void*)"Task3",
    5,
    NULL);

  vTaskStartScheduler();
}

void loop() {}

void TaskPrint(void *pvParameters) {
  char* taskName = (char*) pvParameters;

  for (;;) {
    Serial.println("Hello from FreeRTOS Task: " + String(taskName));
    vTaskDelay(100);
  }
}