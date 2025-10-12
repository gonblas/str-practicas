# Ejercicio 1

Investigue y analice las posibilidades que brinda FreeRTOS para la creación y el manejo
de tareas.

Identifique cada una de las características que deben ser consideradas al momento de
definir una tarea.

---

En FreeRTOS, existen diferentes funciones que permiten la creación y el manejo de tareas.

- **xTaskCreate()**: Esta función se utiliza para crear una nueva tarea. Se le debe proporcionar un puntero a la función que implementa la tarea, un nombre para la tarea, la pila necesaria, parámetros opcionales y la prioridad de la tarea.

- **vTaskDelete()**: Esta función se utiliza para eliminar una tarea. Se le debe proporcionar el identificador de la tarea que se desea eliminar.

- **vTaskDelay()**: Esta función permite que una tarea se bloquee durante un período de tiempo específico, permitiendo que otras tareas se ejecuten.

- **vTaskDelayUntil()**: Esta función permite que una tarea se bloquee hasta un momento específico en el tiempo, lo que es útil para tareas periódicas.

- **vTaskSuspend()**: Esta función suspende una tarea, impidiendo que se ejecute hasta que sea reanudada.

- **vTaskResume()**: Esta función reanuda una tarea que ha sido suspendida.

- **uxTaskPriorityGet()**: Esta función obtiene la prioridad actual de una tarea.

---

Vamos a detallar las características que deben ser consideradas al momento de definir una tarea en FreeRTOS. Para eso analizaremos la firma de la función `xTaskCreate()`:

```c
portBASE_TYPE xTaskCreate( pdTASK_CODE pvTaskCode,
                           const signed portCHAR * const pcName,
                           unsigned portSHORT usStackDepth,
                           void *pvParameters,
                           unsigned portBASE_TYPE uxPriority,
                           xTaskHandle *pxCreatedTask
                         );
```

1. **pvTaskCode**: Es un puntero a la función que implementa la tarea. Esta función debe tener el siguiente prototipo: `void vTaskFunction( void *pvParameters );`. La función debe contener un bucle infinito para que la tarea pueda ejecutarse continuamente.

2. **pcName**: Es un nombre descriptivo para la tarea. Este nombre es útil para la depuración y el monitoreo de tareas. FreeRTOS no utiliza este nombre para la gestión interna de tareas.

3. **usStackDepth**: Es la cantidad de memoria de pila (stack) que se asignará a la tarea. Se asigna en palabras, y no en bytes. Esto quiero decir que depende de la arquitectura del microcontrolador. Por ejemplo, en una arquitectura de 32 bits, cada palabra tiene 4 bytes.

4. **pvParameters**: Es un puntero a los parámetros que se pasarán a la tarea cuando se inicie. Esto permite que la misma función de tarea pueda ser reutilizada con diferentes datos.

5. **uxPriority**: Es la prioridad de la tarea. FreeRTOS utiliza un esquema de prioridades basado en números enteros, donde un número más alto indica una mayor prioridad. Las tareas con mayor prioridad se ejecutan antes que las tareas con menor prioridad.

6. **pxCreatedTask**: Es un puntero a una variable donde se almacenará el identificador de la tarea creada. Este identificador puede ser utilizado posteriormente para manipular la tarea (por ejemplo, para eliminarla o cambiar su prioridad).

7. **Returned value**: Puede devolver dos posibles valores:
    - `pdPASS`: Indica que la tarea fue creada exitosamente.
    - `errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY`: Indica que no se pudo asignar la memoria necesaria para la tarea, lo que puede ocurrir si no hay suficiente memoria disponible.
