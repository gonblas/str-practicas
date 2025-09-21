# Ejercicio 3

Encuentre la parametrización correcta para que la simulación de Cheddar resulte de la siguiente forma, usando el algoritmo de planificación POSIX 1003.1b/Highest Priority First para la CPU:

## Inciso A

Para resolver este ejercicio, debemos configurar el **scheduler** con un **quantum de 3**, y asignar a las tareas `rt_task_1` y `rt_task_2` el **scheduling Round-Robin (RR)**. Esto permite que `rt_task_2` pueda ser interrumpida por `rt_task_1` cuando se le agote su quantum. Por otro lado, la `no_rt_task`, al tener una prioridad menor, nunca interrumpirá a las otras dos tareas.

## Inciso B

Para este ejercicio, basta con configurar el **scheduler indicado** y asignar a las tareas el **scheduling FIFO**.
