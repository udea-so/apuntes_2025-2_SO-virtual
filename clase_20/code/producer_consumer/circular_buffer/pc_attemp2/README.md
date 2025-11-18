# Problema productor-consumidor con buffer circular (Intento 2)

## Descripción

Esta implementación soluciona el problema 1 de la implementacion [**pc_attemp1**](../pc_attemp1/README.md), sin embargo **falla**, pues se produce producen los siguientes problemas:
1. El programa se queda dormido; esto se puede evidenciar en la notas de clase debido a la forma como se manejo el semaforo que hace de mutex. La prueba con la que fallo fue con:
* **Numero de productores**: 1
* **Numero de consumidores**: 1
* **Numero de Loops**: 50

La solución a este problema se encuentra en el siguiente [link](../pc_work/README.md)

**Nota**: La implementación del libro solo funciona para un solo productor y varios consumidores, la forma como esta concebida **no funciona** para varios consumidores pues el programa se queda dormido. Esto se debe a la forma de controlar culminacón del programa.
