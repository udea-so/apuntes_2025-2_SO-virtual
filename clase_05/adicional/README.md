# Elementos adicionales

## The MIPS Register Set

| Name | Register Number | Usage |
|---|---|---|
| `$0` | 0 | the constant value 0 |
| `$at` | 1 | assembler temporary |
| `$v0-$v1` | 2-3 | procedure return values |
| `$a0-$a3` | 4-7 | procedure arguments |
| `$t0-$t7` | 8-15 | temporaries |
| `$s0-$s7` | 16-23 | saved variables |
| `$t8-$t9` | 24-25 | more temporaries |
| `$k0-$k1` | 26-27 | OS temporaries |
| `$gp` | 28 | global pointer |
| `$sp` | 29 | stack pointer |
| `$fp` | 30 | frame pointer |
| `$ra` | 31 | procedure return address |

## Ejemplos

### Ejemplo 1

Llamada a una función para ver el efecto en los registros `$a_i`, `$v_i`

```c
int sumar(int a, int b);

// Función principal
int main() {
    int resultado = sumar(10, 5);
    return 0;
}

// Definición de la función 'sumar'
int sumar(int a, int b) {
    return a + b;
}
```

Codigo mips

```s
#----------------------------------------------------
# SECCIÓN DE TEXTO (CÓDIGO EJECUTABLE)
#----------------------------------------------------
.text
.globl main

#----------------------------------------------------
# FUNCIÓN PRINCIPAL (el que llama)
#----------------------------------------------------
main:
    # --- Preparación de la llamada a la función ---
    li $a0, 10          
    li $a1, 5           

    # --- Llamada a la función ---
    jal sumar    
    li $v0, 10            
    syscall               

#----------------------------------------------------
# FUNCIÓN 'sumar' (el llamado)
#----------------------------------------------------
sumar:   
    add $v0, $a0, $a1
    jr $ra
```

### Ejemplo 2

Mostrar el caso de una función recursiva (Esto pensando en los cambios en el contexto de los SO)...
- [ ] To Do...



## Enlaces

* https://ucsb-cs64.github.io/w20/
* https://www.cs.cornell.edu/~tomf/notes/cps104/mips.html
* https://safari.ethz.ch/ddca/spring2024/doku.php?id=schedule
* https://cpulator.01xz.net/?sys=mipsr5-spim
* https://cpulator.01xz.net/doc/