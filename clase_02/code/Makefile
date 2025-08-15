# Compilador y banderas de compilación
CC = gcc
# CFLAGS define las opciones para el compilador:
# -g:         Incluye información de depuración en el ejecutable.
# -Wall:      Habilita la mayoría de las advertencias comunes (muy recomendado).
# -Wextra:    Habilita advertencias adicionales que -Wall no cubre.
# -std=c99:   Usa el estándar C99 para el lenguaje.
CFLAGS = -g -Wall -Wextra -std=c99

# Banderas para el enlazador (linker)
LDFLAGS =

# Encuentra automáticamente todos los archivos fuente .c en el directorio
SOURCES = $(wildcard *.c)
# Genera los nombres de los ejecutables a partir de los archivos fuente
# (ej. de "cpu.c" se genera el objetivo "cpu")
TARGETS = $(patsubst %.c,%,$(SOURCES))

# .PHONY evita conflictos con archivos que se llamen 'all' o 'clean'
.PHONY: all clean

# El objetivo 'all' es el predeterminado y compila todos los programas
all: $(TARGETS)

# Regla de patrón estática para compilar cualquier ejecutable a partir de su .c
# $@ es el nombre del objetivo (ej. 'cpu')
# $< es el nombre del primer prerrequisito (ej. 'cpu.c')
$(TARGETS): %: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# Banderas específicas para el objetivo 'threads'
# Se añade -pthread solo al compilar y enlazar 'threads'
threads: LDFLAGS += -pthread

# Objetivo para limpiar los archivos ejecutables generados
clean:
	rm -f $(TARGETS)
