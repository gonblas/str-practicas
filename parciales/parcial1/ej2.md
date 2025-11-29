**2) Complete las prioridades de las tareas. Además, complete la política de cada una de las tareas y el quantum. Realice una explicación del porqué de su respuesta.**

En el diagrama se observa que, durante el primer período, el orden de ejecución es TASK_1 -> TASK_2 -> TASK_3, mientras que en el segundo período el orden cambia a TASK_3 -> TASK_1 -> TASK_2.
Si existiera una diferencia de prioridades, la tarea con mayor prioridad debería ejecutarse primero en todos los períodos. Como esto no ocurre, puede concluirse que las tres tareas tienen la misma prioridad.
Por lo tanto, asignamos a todas: 

TASK_1 -> Priority = 100  
TASK_2 -> Priority = 100  
TASK_3 -> Priority = 100

**¿Que planificador se utiliza?**

Como todas las tareas tienen la misma prioridad, ninguna puede interrumpir a otra por prioridad más alta. Sin embargo, en la línea de tiempo se observa que las tareas sí son interrumpidas antes de finalizar su ejecución, lo que indica que la política utilizada no es FIFO (que ejecutaría una tarea completa sin cortes) sino **Round Robin (RR)**.

En Round Robin, el procesador asigna a cada tarea un tiempo fijo de ejecución llamado: **Quantum o time slice**. Durante ese tiempo, la tarea ejecuta de forma ininterrumpida. Cuando el quantum se agota, la tarea se detiene y vuelve a la cola, cediendo el procesador a la siguiente tarea del mismo nivel de prioridad. En el gráfico se ve claramente que las tareas ejecutan de a 2 unidades de tiempo antes de ser interrumpidas, incluso cuando aún les queda computación pendiente.
Por lo tanto, el quantum es:

Quantum = 2

En particular:
- TASK_3 también es interrumpida a las 2 unidades, pero más adelante se ve un tramo de 4 unidades seguidas. Esto no contradice el quantum: en ese momento era la única tarea que quedaba sin completar, por lo que ejecutó su quantum, volvió a entrar inmediatamente en la cola, y recibió el procesador de nuevo sin esperar, sumando dos quantums consecutivos.
- En el segundo período, TASK_2 aparece ejecutando solo 1 unidad. Esto no significa que cambió el quantum, sino que ya había consumido 1 unidad de su quantum anterior antes de ser interrumpida, por lo que solo le quedaba 1 unidad para terminar.


**¿Por qué el primer período empieza con TASK_1 y no con otra?**

Dado que las tareas tienen la misma prioridad y todas liberan su instancia al mismo tiempo (start = 0, release periódica cada 10), el planificador necesita un criterio de desempate.

Lo habitual es que seleccione la tarea:
- según el orden de creación, o
- según el orden de aparición en la cola del sistema

Por eso el primer período comienza con TASK_1, luego sigue TASK_2 y finalmente TASK_3.
