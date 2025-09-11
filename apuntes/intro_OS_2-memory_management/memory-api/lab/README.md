# Lab

This lab is going to go over some of the memory allocation commands in C. We will be using a pointer to an array of characters. When printing this pointer as an unsigned integer, the return value will represent the location in memory of the pointer. Watch how this number changes (or does not change) as memory functions are performed. The character pointer txt is already declared for you.

**code**: `lab1.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   char *txt;

   // Add your code below this line

   
   
   // Add your code above this line
   
   return(0);
}

```

## Malloc

Start by using `malloc` to allocate memory. We want to start with the string `"Hello"`. This is five characters long, but we need to take into account the end of line character. Because of this, use `6v when allocating memory (the length of `"Hello" + 1`). Use strcpy to set the value of `txt` to `"Hello"`. Next print the value of `txt` and then print it as an unsigned integer.

```c
// Add your code below this line

txt = (char *) malloc(6);
strcpy(txt, "Hello");
printf("String: %s,  Address: %u\n", txt, txt);
   
// Add your code above this line
```

## Realloc

Using `realloc` increases the allocated memory to an arbitrarily larger size. This is done only for demonstrative purposes. Use `25` as the new memory size. Next, concatenate `" World"` to `txt` to update the value of the `string`. Then print the value and address of `txt`.

```c
// Add your code below this line

txt = (char *) malloc(6);
strcpy(txt, "Hello");
printf("String: %s,  Address: %u\n", txt, txt);

txt = (char *) realloc(txt, 25);
strcat(txt, " World");
printf("String: %s,  Address: %u\n", txt, txt);
   
// Add your code above this line
```
## Free

Finally, we are going to deallocate the memory for `txt` with the `free` command. After doing so, print the value and address of `txt`.

```c
// Add your code below this line

txt = (char *) malloc(6);
strcpy(txt, "Hello");
printf("String: %s,  Address: %u\n", txt, txt);

txt = (char *) realloc(txt, 25);
strcat(txt, " World");
printf("String: %s,  Address: %u\n", txt, txt);

free(txt);
printf("String: %s,  Address: %u\n", txt, txt);
   
// Add your code above this line
```

## Compile and run your program.

```
gcc -Wall lab1.c -o lab1
```

### compile

```
./lab1
```

### run

```
String: Hello,  Address: 1131815520
String: Hello World,  Address: 1131819664
String: ,  Address: 1131819664
```

You should see output similar to this (note the address value will be different):

```
String: Hello,  Address: 615785056
String: Hello World,  Address: 615789200
String: ,  Address: 615789200
```
Notice how the unsigned integer value for `txt` changes after reallocating more memory to the pointer. In addition, the pointer `txt` no longer has a string value after deallocating the memory with `free`.

### Question

Drag the blocks into the box below to create the main function that has a pointer of type double. Allocate memory for 100 doubles... **Important**, not all of the blocks will be used.

> The correct answer is:
> 
> ```c
> int main() {
>   double *ptr;
>   ptr = (double*) malloc(100 * sizeof(double));
>   return 0;
> }
> ```
> Start by declaring the `main` function. Then declare the pointer `ptr`. Do not use `realloc` to initially allocate memory. This command should be used after memory has already been allocated. Since you want a pointer for doubles, use `sizeof(double)`. However, you want memory for `100` doubles, so it should be `100 * sizeof(double)`.


