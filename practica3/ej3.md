# Ejercicio 3

Investigue y analice las herramientas que provee FreeRTOS para la sincronización de
tareas.

---

## Colas (Queues)

Las colas en FreeRTOS son estructuras de datos que permiten la comunicación y sincronización entre tareas. Una cola puede almacenar múltiples elementos, y las tareas pueden enviar y recibir elementos de la cola de manera segura.

- **xQueueCreate()**: Esta función crea una nueva cola. Se le debe proporcionar el número máximo de elementos que la cola puede contener y el tamaño de cada elemento.

- **xQueueSend()**: Esta función envía un elemento a la cola. Si la cola está llena, la tarea que intenta enviar el elemento puede bloquearse hasta que haya espacio disponible.

- **xQueueReceive()**: Esta función recibe un elemento de la cola. Si la cola está vacía, la tarea que intenta recibir un elemento puede bloquearse hasta que haya un elemento disponible.

- **xQueuePeek()**: Esta función permite ver el elemento en la parte frontal de la cola sin eliminarlo.

- **uxQueueSpacesAvailable()**: Esta función devuelve el número de espacios disponibles en la cola.

## Semáforos (Semaphores)

El kernel de FreeRTOS proporciona semáforos binarios, semáforos de recuento y exclusiones mutuas con fines de exclusión mutua y sincronización.

Los semáforos binarios solo pueden tener dos valores. Son una buena opción para implementaciones de sincronización (ya sea entre tareas o entre tareas e interrupciones). Los semáforos de recuento tienen más de dos valores. Permiten compartir recursos entre muchas tareas o realizar las operaciones de sincronización más complejas.

Las exclusiones mutuas son semáforos binarios que incluyen un mecanismo de herencia de prioridades. Esto significa que si una tarea de alta prioridad se bloquea al intentar obtener una exclusión mutua que actualmente está en manos de una tarea de menor prioridad, la prioridad de la tarea que tiene el token se eleva temporalmente a la de la tarea bloqueada. Este mecanismo está diseñado para garantizar que la tarea de mayor prioridad se mantenga en estado bloqueado el menor tiempo posible, a fin de minimizar la inversión de prioridades que ha tenido lugar.

### Semáforos binarios

- **xSemaphoreCreateBinary()**: Esta función crea un semáforo binario.

- **xSemaphoreTake()**: Esta función toma (bloquea) el semáforo. Si el semáforo no está disponible, la tarea puede bloquearse hasta que esté disponible.

- **xSemaphoreGive()**: Esta función libera (desbloquea) el semáforo.

### Semáforos de recuento

- **xSemaphoreCreateCounting()**: Esta función crea un semáforo de recuento. Se le debe proporcionar el valor máximo y el valor inicial del semáforo.

- **xSemaphoreTake()**: Esta función toma (decrementa) el semáforo. Si el valor del semáforo es cero, la tarea puede bloquearse hasta que el semáforo sea mayor que cero.

- **xSemaphoreGive()**: Esta función libera (incrementa) el semáforo.

## Task Notifications

Las notificaciones de tareas son una forma ligera y eficiente de comunicación entre tareas y entre tareas e interrupciones. Cada tarea tiene una notificación asociada que puede contener un valor de 32 bits. Las notificaciones de tareas pueden ser utilizadas para enviar datos, señales o eventos a una tarea específica.

- **xTaskNotify()**: Esta función envía una notificación a una tarea específica. Se le puede proporcionar un valor y un modo de operación (por ejemplo, establecer, incrementar, etc.).

- **xTaskNotifyAndQuery()**: Esta función envía una notificación a una tarea específica y consulta el valor actual de la notificación.

- **xTaskNotifyWait()**: Esta función permite que una tarea espere una notificación. La tarea puede bloquearse hasta que reciba una notificación.

- **ulTaskNotifyTake()**: Esta función permite que una tarea tome (decrementar) su notificación. Si la notificación es cero, la tarea puede bloquearse hasta que la notificación sea mayor que cero.
