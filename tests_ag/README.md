# Problema Productor-Consumidor con Semáforos

## 1. Introducción

Este proyecto implementa el clásico **problema del productor-consumidor** utilizando semáforos en C. Es un ejemplo fundamental en sistemas operativos que demuestra cómo sincronizar múltiples hilos (threads) que comparten un recurso limitado: un buffer circular.

**Escenario:**

- Un **productor** genera datos y los coloca en un buffer compartido.
- Uno o más **consumidores** extraen datos del buffer para procesarlos.
- El buffer tiene un tamaño limitado, por lo que debemos evitar:
  - Que el productor escriba cuando el buffer está lleno.
  - Que los consumidores lean cuando el buffer está vacío.
  - Condiciones de carrera (race conditions) al acceder al buffer simultáneamente.

**Solución:** Usamos **semáforos** para coordinar el acceso al buffer y garantizar la sincronización correcta.

---

## 2. Conceptos Clave

### 2.1 Threads (Hilos)

Los **threads** son unidades de ejecución dentro de un proceso que comparten el mismo espacio de memoria. Esto permite ejecutar múltiples tareas concurrentemente.

**Funciones principales de la API pthread:**

| Función | Descripción |
|---------|-------------|
| `pthread_create(thread, attr, start_routine, arg)` | Crea un nuevo hilo que ejecuta la función `start_routine` con el argumento `arg`. |
| `pthread_join(thread, value_ptr)` | Espera a que el hilo especificado termine su ejecución. |

### 2.2 Semáforos

Un **semáforo** es una variable entera que se utiliza para controlar el acceso a recursos compartidos mediante dos operaciones atómicas:

**Operaciones básicas:**

| Función | Descripción |
|---------|-------------|
| `sem_init(sem, pshared, value)` | Inicializa el semáforo con un valor inicial. `pshared=0` indica que el semáforo es compartido entre hilos del mismo proceso. |
| `sem_wait(sem)` | **Decrementa** el semáforo. Si el valor es 0, el hilo se bloquea hasta que el valor sea mayor que 0. |
| `sem_post(sem)` | **Incrementa** el semáforo, desbloqueando un hilo en espera (si existe). |

### 2.3 Mutex (Exclusión Mutua)

Aunque usamos un semáforo como mutex en este código, un **mutex** es un mecanismo de sincronización que garantiza que solo un hilo pueda acceder a una sección crítica a la vez.

**Funciones principales:**

| Función | Descripción |
|---------|-------------|
| `pthread_mutex_lock(mutex)` | Adquiere el mutex. Si ya está bloqueado, el hilo espera. |
| `pthread_mutex_unlock(mutex)` | Libera el mutex. |

---

## 3. Explicación del Código

### Estructura del Programa

El programa utiliza **tres semáforos** para sincronizar el acceso al buffer:

```c
sem_t empty;  // Cuenta los espacios vacíos en el buffer
sem_t full;   // Cuenta los espacios llenos en el buffer
sem_t mutex;  // Protege el acceso al buffer (exclusión mutua)
```

### Inicialización de Semáforos

```c
Sem_init(&empty, max);  // Inicialmente, todos los espacios están vacíos
Sem_init(&full, 0);     // Inicialmente, no hay espacios llenos
Sem_init(&mutex, 1);    // Mutex binario (0 o 1)
```

### Función Productor

```c
void *producer(void *arg) {
    for (i = 0; i < loops; i++) {
        Sem_wait(&empty);    // Espera un espacio vacío
        Sem_wait(&mutex);    // Adquiere el mutex
        do_fill(i);          // Coloca el dato en el buffer
        Sem_post(&mutex);    // Libera el mutex
        Sem_post(&full);     // Señala que hay un espacio lleno
    }
    // Envía señales de terminación (-1) a los consumidores
    for (i = 0; i < consumers; i++) {
        Sem_wait(&empty);
        Sem_wait(&mutex);
        do_fill(-1);
        Sem_post(&mutex);
        Sem_post(&full);
    }
    return NULL;
}
```

**Flujo:**

1. Espera a que haya un espacio vacío (`empty`).
2. Adquiere el mutex para acceso exclusivo.
3. Inserta el dato en el buffer.
4. Libera el mutex.
5. Señala que hay un nuevo dato disponible (`full`).

### Función Consumidor

```c
void *consumer(void *arg) {
    int tmp = 0;
    while (tmp != -1) {
        Sem_wait(&full);     // Espera un espacio lleno
        Sem_wait(&mutex);    // Adquiere el mutex
        tmp = do_get();      // Extrae el dato del buffer
        Sem_post(&mutex);    // Libera el mutex
        Sem_post(&empty);    // Señala que hay un espacio vacío
        printf("%lld %d\n", (long long int) arg, tmp);
    }
    return NULL;
}
```

**Flujo:**

1. Espera a que haya un dato disponible (`full`).
2. Adquiere el mutex para acceso exclusivo.
3. Extrae el dato del buffer.
4. Libera el mutex.
5. Señala que hay un nuevo espacio vacío (`empty`).
6. Procesa el dato (en este caso, lo imprime).

### Buffer Circular

El buffer se implementa como un arreglo circular con dos índices:

- `fill`: Posición donde el productor inserta el siguiente dato.
- `use`: Posición desde donde el consumidor extrae el siguiente dato.

```c
void do_fill(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % max;  // Avanza circularmente
}

int do_get() {
    int tmp = buffer[use];
    use = (use + 1) % max;    // Avanza circularmente
    return tmp;
}
```

---

## 4. Cómo Ejecutar y Probar el Código

### Requisitos

- **Compilador GCC** con soporte para pthreads
- **Sistema operativo:** Linux, macOS o Windows con MinGW/WSL

### Compilación

```bash
make
```

Esto generará el ejecutable `producer_consumer_works`.

### Ejecución

El programa acepta tres argumentos:

```bash
./producer_consumer_works <buffersize> <loops> <consumers>
```

**Parámetros:**

- `buffersize`: Tamaño del buffer circular.
- `loops`: Número de elementos que el productor generará.
- `consumers`: Número de hilos consumidores.

### Ejemplos de Prueba

#### Ejemplo 1: Buffer pequeño, un consumidor

```bash
./producer_consumer_works 1 10 1
```

**Salida esperada:**

```
0 0
0 1
0 2
...
0 9
0 -1
```

#### Ejemplo 2: Buffer más grande, múltiples consumidores

```bash
./producer_consumer_works 5 20 3
```

**Salida esperada:**

```
0 0
1 1
2 2
0 3
...
```

Los números a la izquierda indican el ID del consumidor (0, 1, 2).

#### Ejemplo 3: Condición de estrés

```bash
./producer_consumer_works 1 1000 5
```

Esto prueba la sincronización con un buffer muy pequeño y muchos consumidores.

### Limpieza

```bash
make clean
```

---

## 5. Preguntas de Comprensión

Responde las siguientes preguntas para verificar tu comprensión:

### Preguntas Conceptuales

1. **¿Qué pasaría si eliminamos el semáforo `mutex`?**
   - ¿Podría haber condiciones de carrera? ¿Por qué?

2. **¿Por qué el semáforo `empty` se inicializa con `max` y `full` con `0`?**

3. **¿Qué representa el valor `-1` en el código?**
   - ¿Por qué el productor envía exactamente `consumers` valores de `-1`?

4. **¿Qué sucede si el productor intenta insertar cuando el buffer está lleno?**
   - ¿En qué línea se bloquea el productor?

5. **¿Qué sucede si un consumidor intenta extraer cuando el buffer está vacío?**
   - ¿En qué línea se bloquea el consumidor?

### Preguntas de Experimentación

6. **Ejecuta el programa con `buffersize=1` y `buffersize=10`. ¿Notas alguna diferencia en el orden de salida?**

7. **¿Qué pasa si ejecutas con `consumers=1` vs `consumers=5`?**
   - ¿Cómo se distribuye el trabajo entre los consumidores?

8. **Modifica el código para que el productor genere datos más lentamente (usa `sleep(1)` en el loop). ¿Qué observas?**

### Preguntas de Diseño

9. **¿Cómo modificarías el código para tener múltiples productores?**
   - ¿Qué cambios serían necesarios?

10. **¿Podrías implementar este problema usando solo mutexes y variables de condición (sin semáforos)?**
    - ¿Cuáles serían las ventajas y desventajas?

---

## 6. Recursos Adicionales

### Documentación Oficial

- [POSIX Threads (pthreads) - Manual](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Semaphores - Manual](https://man7.org/linux/man-pages/man7/sem_overview.7.html)
- [pthread_create](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [sem_wait / sem_post](https://man7.org/linux/man-pages/man3/sem_wait.3.html)

### Libros Recomendados

- **"Operating Systems: Three Easy Pieces"** - Remzi H. Arpaci-Dusseau y Andrea C. Arpaci-Dusseau
  - Capítulo 30: Condition Variables
  - Capítulo 31: Semaphores
  - [Disponible gratis online](https://pages.cs.wisc.edu/~remzi/OSTEP/)

- **"The Linux Programming Interface"** - Michael Kerrisk
  - Capítulos sobre POSIX Threads y Semáforos

### Tutoriales y Artículos

- **Producer-Consumer Problem - GeeksforGeeks**  
  [https://www.geeksforgeeks.org/producer-consumer-problem-using-semaphores-set-1/](https://www.geeksforgeeks.org/producer-consumer-problem-using-semaphores-set-1/)

- **POSIX Threads Programming - Lawrence Livermore National Laboratory**  
  [https://hpc-tutorials.llnl.gov/posix/](https://hpc-tutorials.llnl.gov/posix/)

- **Semaphores in Linux - TutorialsPoint**  
  [https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_semaphores.htm](https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_semaphores.htm)

- **Semaphores - Wikipedia (Español)**  
  [https://es.wikipedia.org/wiki/Sem%C3%A1foro_(inform%C3%A1tica)](https://es.wikipedia.org/wiki/Sem%C3%A1foro_(inform%C3%A1tica))

### Herramientas de Depuración

- **Valgrind (Helgrind):** Detecta condiciones de carrera y problemas de sincronización

  ```bash
  valgrind --tool=helgrind ./producer_consumer_works 5 10 2
  ```

- **GDB:** Depurador para analizar el comportamiento de los threads

  ```bash
  gdb ./producer_consumer_works
  ```

---

## Notas Finales

Este ejemplo es una implementación didáctica del problema productor-consumidor. En sistemas reales, considera:

- **Manejo de errores:** Validación de argumentos, verificación de malloc, etc.
- **Portabilidad:** El código usa `#ifdef` para manejar diferencias entre Linux y macOS.
- **Escalabilidad:** Para aplicaciones de alto rendimiento, considera estructuras de datos lock-free.

¡Experimenta con diferentes configuraciones y observa cómo los semáforos garantizan la sincronización correcta!

---

**Autor:** Una IA  
**Licencia:** Uso académico
