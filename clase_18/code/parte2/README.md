# Ejemplos de variables de condicion

## The Producer/Consumer (Bounded Buffer) Problem

### Funciones `put` y `get`

```
int buffer;
int count = 0; // initially, empty

void put(int value) {
  assert(count == 0);
  count = 1;
  buffer = value;
}

int get() {
  assert(count == 1);
  count = 0;
  return buffer;
}
```

El `assert` es una macro utilizada para verificar que una condición se cumpla. La macro evalua la condición y si esta es falsa `assert` imprimirá un mensaje de error y terminará el programa.

El código del productor y el consumidor se muestra a continuación:

**Productor**

```
void *producer(void *arg) {
  int i;
  int loops = (int) arg;
  for (i = 0; i < loops; i++) {
    put(i);
  }
}
```

**Consumidor**

```
void *consumer(void *arg) {
  while (1) {
    int tmp = get();
    printf("%d\n", tmp);
  }
}
```



### Implementación del problema usando variables de condición

#### Caso 0 - No se maneja primitivas de concurrencia

En este codigo ([main_singleBuffer-v0.c](main_singleBuffer-v0.c)) no se emplean ni variables de condicion ni mutex.

#### Caso 1 - Unica CV y sentencia if - Broken solution

En este codigo ([main_singleBuffer-v1.c](main_singleBuffer-v1.c)) ...

**Inicializacion**

```c
int loops; // must initialize somewhere...
cond_t cond;
mutex_t mutex;
```

**Productor**

```c
void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
	pthread_mutex_lock(&mutex);     	   // p1
	if (count == 1)                 	   // p2
  	  pthread_cond_wait(&cond, &mutex);    // p3
	put(i);                         	   // p4
	pthread_cond_signal(&cond);     	   // p5
	pthread_mutex_unlock(&mutex);   	   // p6
  }
}
```

**Consumidor**

```c
void *consumer(void *arg) {
  int i;
  while (1) {
	pthread_mutex_lock(&mutex);       	  // c1
	if (count == 0)                   	  // c2
  	  pthread_cond_wait(&cond, &mutex);    // c3
	tmp = get();                      	  // c4
	pthread_cond_signal(&cond);       	  // c5
	pthread_mutex_unlock(&mutex);     	  // c6
	printf("%d\n", tmp);
  }
}
```

**Conclusiones**:
* Un solo productor y un solo consumidor (OK)
* Un solo productor y varios consumidores (Falla)

#### Caso 2 - Unica CV y sentencia while

En este codigo ([main_singleBuffer-v2.c](main_singleBuffer-v2.c))...


**Inicializacion**

```c
int loops; // must initialize somewhere...
cond_t cond;
mutex_t mutex;
```

**Productor**

```c
void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
	pthread_mutex_lock(&mutex);     	   // p1
	while (count == 1)              	   // p2
  	  pthread_cond_wait(&cond, &mutex);    // p3
	put(i);                         	   // p4
	pthread_cond_signal(&cond);     	   // p5
	pthread_mutex_unlock(&mutex);   	   // p6
  }
}
```

**Consumidor**

```c
void *consumer(void *arg) {
  int i;
  while(1) {
	pthread_mutex_lock(&mutex);       	  // c1
	while (count == 0)                    // c2
  	  pthread_cond_wait(&cond, &mutex);   // c3
	tmp = get();                      	  // c4
	pthread_cond_signal(&cond);       	  // c5
	pthread_mutex_unlock(&mutex);     	  // c6
	printf("%d\n", tmp);
  }
}
```

**Conclusiones**:
* Señalizar es necesario.
* La señalizacion llevada a cabo debe ser *mas especifica*.

#### Caso 3 - Se usan dos variables de condicion y un While

En este codigo ([main_singleBuffer-v3.c](main_singleBuffer-v3.c)) ...



**Inicializacion**

```c
int loops; // must initialize somewhere...
cond_t empty, fill;
mutex_t mutex;
```

**Productor**

```c
void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
	pthread_mutex_lock(&mutex);
	while (count == 1)
  	  pthread_cond_wait(&empty, &mutex);
	put(i);
	pthread_cond_signal(&fill);
	pthread_mutex_unlock(&mutex);
  }
}
```

**Consumidor**

```c
void *consumer(void *arg) {
  int i;
  while(1) {
	pthread_mutex_lock(&mutex);
	while (count == 0)
  	  pthread_cond_wait(&fill, &mutex);
	int tmp = get();
	pthread_cond_signal(&empty);
	pthread_mutex_unlock(&mutex);
	printf("%d\n", tmp);
  }
}
```

#### Solución final - Agregar varios slots al buffer

En este codigo ([main_buffer](main_buffer-v3.c)) ...

**Funciones put y get**

```c
int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value) {
  buffer[fill_ptr] = value;
  fill_ptr = (fill_ptr + 1)%MAX;
  count++;
}

int get() {
  int tmp = buffer[use_ptr];
  use_ptr = (use_ptr + 1)%MAX;
  count--;
  return tmp;
}
```

**Inicializacion**

```c
int loops; // must initialize somewhere...
cond_t empty, fill;
mutex_t mutex;
```

**Productor**

```c
void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
	pthread_mutex_lock(&mutex);      	     // p1
	while (count == MAX)             	     // p2
  	  pthread_cond_wait(&empty, &mutex);     // p3
	put(i);                          	     // p4
	pthread_cond_signal(&fill);      	     // p5
	pthread_mutex_unlock(&mutex);    	     // p6
  }
}
```

**Consumidor**

```c
void *consumer(void *arg) {
  int i;
  while(1) {
	pthread_mutex_lock(&mutex);     	 // c1
	while (count == 0)              	 // c2
  	  pthread_cond_wait(&fill, &mutex);  // c3
	int tmp = get();                	 // c4
	pthread_cond_signal(&empty);    	 // c5
	pthread_mutex_unlock(&mutex);   	 // c6
	printf("%d\n", tmp);
  }
}
```