# Ejemplos de variables de condicion

## Problema

Dado el siguiente fragmento de código con hilos:

```c
void *child(void *arg) {
  printf("child\n");
  // XXX how to indicate we are done?
  return NULL;
}

int main(int argc, char *argv[]) {
  printf("parent: begin\n");
  pthread_t c;
  Pthread_create(&c, NULL, child, NULL); //create child
  // XXX how to wait for child?
  printf("parent: end\n");
  return 0;
}
```

¿Como hacer que la salida siempre sea la misma y de la forma?

```
parent: begin
child
parent: end
```

## Soluciones

### Solucion 1 - Ineficiente

Esta solución ([ejemplo1.c](ejemplo1.c)) sirve pero el hilo padre desperdicia de CPU debido debido al spin-loop.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
gcc -Wall -lpthread -o ejemplo1 ejemplo1.c
*/

volatile int done = 0;

void *child(void *arg) {
  printf("child\n");
  done = 1;
  return NULL;
}

int main(int argc, char *argv[]) {
  printf("parent: begin\n");
  pthread_t c;
  pthread_create(&c, NULL, child, NULL); // create child
  while (done == 0)
	; // spin
  printf("parent: end\n");
  return 0;
}
```

### Solucion 2 - Solución empleando variables de condicion

Esta es una solución mejor, pues el hilo padre espera hasta que se de una *condición* antes de continuar. Para esto se hacen uso de Variables de condicion (CV) las cuales permiten que se realicen ciertas acciones o bloques de código si se cumplen determinadas condiciones.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "mythreads.h"

/*
gcc -Wall -lpthread -o ejemplo2 -I. ejemplo2.c
*/

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

// Prototipos de las funciones
void thr_exit(void);
void *child(void *);
void thr_join(void);


// Funcion main

int main(int argc, char *argv[]) {
  printf("parent: begin\n");
  pthread_t p;
  Pthread_create(&p, NULL, child, NULL);
  thr_join();
  printf("parent: end\n");
  return 0;
}

// Definiciones de las funciones

void thr_exit(void) {
  Pthread_mutex_lock(&m);
  done = 1;
  Pthread_cond_signal(&c);
  Pthread_mutex_unlock(&m);
}

void *child(void *arg) {
  printf("child\n");
  thr_exit();
  return NULL;
}

void thr_join(void) {
  Pthread_mutex_lock(&m);
  while (done == 0) {
	  Pthread_cond_wait(&c, &m);
  }
  Pthread_mutex_unlock(&m);
}
```

En el ejemplo anterior se emplean funciones claves `wait` y `signal`

## Sobre las funciones `wait` y `signal`

En la biblioteca de hilos POSIX (Pthreads) se definen las funciones `pthread_cond_wait` y `pthread_cond_signal` para el manejo de variables de condición (CV). Estas son importantes pues permiten que varios hilos se puedan coordinar entre sí para acceder a recursos compartidos o ejecutar ciertas tareas en un orden específico.


### Funcion `pthread_cond_wait`

Sirve para suspender temporalmente la ejecución de un hilo hasta que se cumpla una condición específica.

> #### Sintaxis
> 
> ```c
> int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
> ```
> **Donde**:
> * **`cond`**: puntero a una variable de condición (`pthread_cond_t`) que se espera que cambie a un estado que permita continuar el hilo.
> * **`mutex`**: puntero a un mutex (`pthread_mutex_t`) que se desbloquea temporalmente cuando el hilo entra en espera y se vuelve a bloquear automáticamente cuando el hilo se despierta.

### Funcion `pthread_cond_signal`

Esta función se usa para despertar o notificar a uno de los hilos que están en espera en una variable de condición.

> #### Sintaxis
> 
> ```c
> int pthread_cond_signal(pthread_cond_t *cond)
> ```
>
> **Donde**:
> * **`cond`**: puntero a la variable de condición (`pthread_cond_t`) que se quiere señalizar para que despierte a un hilo en espera.
