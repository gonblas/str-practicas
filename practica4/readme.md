# Practica 4

### Ejercicio 1

Para compilar y ejecutar el programa ej1:

```bash
make 1
```

Esto hará lo siguiente:
- Compilará ej1.c con las opciones necesarias.
- Ejecutará el programa ej1.

### Ejercicio 2

Para compilar y ejecutar los programas del ej2:

```bash
make 2
```

Esto hará lo siguiente:
- Compilará ej2_monitoring.c y ej2_sensor.c.
- Mostrará instrucciones para ejecutar ambos programas en dos terminales separadas. es necesario:
    - Abrir dos terminales separadas.
    - En la primera terminal, ejecutar:
    ```bash
      ./ej2_sensor
    ```
    - En la segunda terminal, ejecutar (requiere permisos de superusuario):
    ```bash
      sudo ./ej2_monitoring
    ```