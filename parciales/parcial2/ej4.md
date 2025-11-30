**Enuncie y describa las funciones para la creación y el manejo de mutex en Posix Pthread.**

- **Creación de Mutex:** Las variables mutex permiten acceder a un recurso compartido sin conflictos. La misma puede crearse a partir de la siguiente función:

  ```c
  #include <pthread.h>
  int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
  ```

  Donde:

  - **mutex**: variable pthread_mutex_t
  - **attr**: variable pthread_mutexattr_t el cual permite enviar atributos del mutex como:

    - PTHREAD_MUTEX_NORMAL: Mutex estándar sin verificación adicional. Si un hilo intenta hacer lock dos veces sobre el mismo mutex, se produce deadlock.
    - PTHREAD_MUTEX_ERRORCHECK: Detecta errores comunes, como intentar hacer unlock sin poseer el mutex o realizar un doble lock. En lugar de colgar, retorna un código de error.
    - PTHREAD_MUTEX_RECURSIVE: Permite que el mismo hilo bloquee (lock) varias veces el mismo mutex sin caer en deadlock. Cada lock debe tener un unlock correspondiente.
    - PTHREAD_MUTEX_DEFAULT: Implementación por defecto del sistema, generalmente equivalente a PTHREAD_MUTEX_NORMAL, pero sin garantía explícita de comportamiento en casos de doble lock.

    Si attr = NULL, se crea un mutex con los atributos por defecto definidos por la implementación del sistema.

- **Manejo de mutex:**

  | Función                         | Para qué sirve                                                            |
  | ------------------------------- | ------------------------------------------------------------------------- |
  | `pthread_mutex_lock(&mutex)`    | Bloquea el mutex. Si otro hilo lo tiene, espera.                          |
  | `pthread_mutex_unlock(&mutex)`  | Desbloquea el mutex. Permite que otros hilos entren a la sección crítica. |
  | `pthread_mutex_trylock(&mutex)` | Intenta bloquear sin esperar; si está ocupado, devuelve error.            |
  | `pthread_mutex_destroy(&mutex)` | Elimina el mutex cuando deja de usarse.                                   |
