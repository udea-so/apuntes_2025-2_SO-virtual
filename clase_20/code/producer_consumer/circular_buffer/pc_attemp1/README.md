# Problema productor-consumidor con buffer circular (Intento 1)

## Descripción

Esta implementación **falla** pues se produce producen los siguientes problemas:
1. Cuando hay mas de un productor puede y un solo consumidor, puede se se reescriban datos en el buffer. La solución a este problema se explica en el siguiente [link](../pc_attemp2/README.md)
2. El programa se queda dormido, Nunca se acaba (Caso cuando el numero de productores es mayor de uno).

**Nota**: La implementación del libro solo funciona para un solo productor y varios consumidores, la forma como esta concebida **no funciona** para varios consumidores pues el programa se queda dormido. Esto se debe a la forma de controlar culminacón del programa.
