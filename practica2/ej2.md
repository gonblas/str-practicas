# Ejercicio 2

En un sistema de tiempo real con las siguientes tareas:

| Tarea | Tiempo de ejecución C_i | Período / Plazo T_i = D_i |
| ----- | --------------------------- | ----------------------------- |
| A     | 1                           | 10                            |
| B     | 3                           | 12                            |
| C     | 7                           | 20                            |
| D     | 1                           | 5                             |

**(a)** Comprueba si existe una planificación de tiempo real viable.

**(b)** Desarrolla un plan cíclico para la ejecución de estas tareas, calculando el periodo principal y secundario y mostrando la tabla de tareas para el ejecutivo cíclico.

---

## Resolución

### (a)

La utilización total se calcula como:

$$
  U = \sum_{i=1}^{n} \frac{C_i}{T_i}
$$

Cálculo por tarea:

- A: $1/10 = 0.1$
- B: $3/12 = 0.25$
- C: $7/20 = 0.35$
- D: $1/5  = 0.2$

$$
  U = 0.1 + 0.25 + 0.35 + 0.2 = 0.9
$$

Comprobamos las condiciones para aplicar cada planificación:

- **Rate Monotonic (RMS):** Límite de Liu & Layland para 4 tareas:

  $$
    U_\text{RMS} = 4(2^{1/4}-1) \approx 0.7568
  $$

  Comparación:

  $$
    U = 0.9 > 0.7568
  $$

  Con RMS **no hay garantía de planificación**.

- **Earliest Deadline First (EDF):** Condición: $U \le 1$

  $$
    U = 0.9 \le 1
  $$

  Con EDF **sí es planificable**.

---

### (b)

Determinar período principal (hiperperíodo)

$$
  H = \text{MCM}(10, 12, 20, 5) = 60
$$

Determinar tamaño de periodo secundario

- Máximo tiempo de ejecución: $C_\text{max} = 7 → f \ge 7$
- Probar $f = 10$ (una opción razonable, mayor o igual a 7 y múltiplo práctico):

Verificación de la condición: $2f - MCD(T_i, f) \le D_i$

| Tarea | $C_i$ | $T_i$ | $2f - MCD(T_i, f)$       | $D_i$ | Cumple? |
| ----- | ----- | ----- | ------------------------ | ----- | ------- |
| A     | 1     | 10    | 20 - MCD(10,10)=20-10=10 | 10    | Si      |
| B     | 3     | 12    | 20 - MCD(12,10)=20-2=18  | 12    | No      |
| C     | 7     | 20    | 20 - MCD(20,10)=20-10=10 | 20    | Si      |
| D     | 1     | 5     | 20 - MCD(5,10)=20-5=15   | 5     | No      |

- Resultado: $f = 10$ **no cumple** para todas las tareas.
- Probar $f = 5$ (menor, pero $≥ C_{max} \rightarrow  C_{max}=7 \rightarrow 5<7$ ❌).
- Probar $f = 15 (≥ C_\text{max}=7)$:

  | Tarea | $2f - MCD(T_i,f)$       | $D_i$ | Cumple? |
  | ----- | ----------------------- | ----- | ------- |
  | A     | 30 - MCD(10,15)=30-5=25 | 10    | No      |
  | B     | 30 - MCD(12,15)=30-3=27 | 12    | No      |
  | C     | 30 - MCD(20,15)=30-5=25 | 20    | No      |
  | D     | 30 - MCD(5,15)=30-5=25  | 5     | No      |

> **Conclusión:** **No hay un tamaño de frame que cumpla la regla estricta para todas las tareas**, porque hay tareas muy cortas con deadlines pequeños y una tarea muy larga (C=7).
