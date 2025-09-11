# Memory API

## Introduction

This lesson will look more closely at memory allocation in a UNIX system. As we go over the core concepts, keep the following questions in mind:
* **Memory is often allocated and managed through which interfaces?**
* **What are the common mistakes can you expect when working with memory?**

You will will be working with some C programs, so be sure you are familiar with the concepts found in the C primer lesson.

## Types of Memory

**Stack memory** and **heap memory** are allocated in a C program.

### Stack Memory

**Stack** memory is handled by the compiler. This happens when create functions, instantiate variables, etc. The compiler allocates enough stack space to run the function. The code snippet below allocates stack memory for `func()` and the integer `x`.

```c
void func() {
  int x; // declares an integer on the stack
  ...
}
```

Upon completion, the compiler deallocates this memory back to the system. Stack memory is short-term in nature.

### Heap Memory

**Heap memory** is long-lived when compared to stack memory. Another important distinction is that the programmer is responsible the allocation and deallocation of this memory. The code sample below allocates stack memory just as before, but using `malloc()` allocates heap memory for the integer.

Here’s how to allocate an integer on the **heap**:

```c
void func() {
  int *x = (int *)malloc(sizeof(int));
  ...
}
```

If the allocation of heap memory was successful, the memory address is returned. If not, the program returns `NULL`. Because allocation and deallocation is done by the user, this can be more challenging. We will spend most of our time looking a heap memory.

### Questions

1. Fill in the blanks to complete the statements below.
   
   Click the button below to submit.
   * Allocations and deallocations of **heap memory** are managed explicitly by the programmer.
   * Allocations and deallocations of **stack memory** are managed implicitly by the compiler.

   > * **Heap memory** is **explicitly** allocated and deallocated by the programmer.
   > * The compiler manages the allocation and deallocation of **stack memory implicitly**.

   <br>

2. Rearrange the blocks below to create a function that allocates memory on the stack for a variable `pinky`
   
   Drag the code blocks to the area below to construct your solution. Then, click the button below to submit.
   
   ```c
   void func() {
     int pinky;
   }
   ```

   Declaring the variable and variable type above declare memory on the **stack**. The compiler makes sure there’s enough space in the stack and deallocates it when the function returns.


3. Rearrange the blocks below to create a function that allocates memory on the heap for a variable `brain`.
   
   Drag the code blocks to the area below to construct your solution. Then, click the button below to submit.
   
   ```c
   void func() {
     int *brain = (int *)malloc(sizeof(int));
   }
   ```

   The above shows how you explicitly allocate an integer variable on **heap memory** by declaring an integer pointer (`int *brain`) and using `malloc()` to request space on the heap.

## `malloc()`

The `malloc()` function allocates space on the heap and returns a pointer to it (if successful) or returns `NULL` (if it fails). To learn more about using `malloc()` bring up its manual page with the following command.

```
man malloc
```

Using `malloc()` requires the inclusion of the `<stdlib.h>` header file. When calling `malloc()`, pass it a parameter of that represents the size of the memory block in bytes. You want to be precise about the requested size but also avoid hard coding a value.

```c
double *myDouble = (double *) malloc(sizeof(double));
```
The compiler calculates the size of double with the `sizeof()` function for you.

### Create a pointer to an integer using `malloc()`.

#### `malloc` reading question

Drag the code blocks to the area below to construct your solution. Then, click the button below to submit.

Please indent correctly.


**The correct answer is**:

```c
#include <stdio.h>
#include <stdlib.h>
int main () {
  int *myAddress = (int *) malloc(sizeof(int));
  printf(myAddress);
  return(0);
}
```
Include the `<stdlib.h>` library
Use of `sizeof()` and the correct data type (int in this example) when setting the size of the memory

## Passing Variables to `malloc()`

You can pass a variable to `sizeof()` instead of a data type. The code snippet below creates an array of ten integers. It then passes this variable to `sizeof()`. The compiler allocates 40 bytes of memory.

```c
int x[10];
printf("%d\n", sizeof(x));
```

**code**

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   
  // add your code below this line
  
  int x[10];
  printf("%ld\n", sizeof(x));
  
  // add your code above this line
   
   return(0);
}
```

**compile program**

```
gcc pass_var.c -Wall -o pass_var
```

**run program**

```
40
```


You may find that the end result is not be what you expect. Enter the code below into the IDE.

```c
int *x = malloc(10 * sizeof(int));
printf("%ld\n", sizeof(x));
```

**code**

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   
  // add your code below this line
  
  int *x = malloc(10 * sizeof(int));
  printf("%ld\n", sizeof(x));
  
  // add your code above this line
   
   return(0);
}
```

**compile program**

```
gcc pass_var.c -Wall -o pass_var
```

**run program**

```
8
```

The program prints `8` instead of `40`. That is because 8 is the size of a single integer on a 64-bit machine (you would see 4 on a 32-bit machine). However, the first line of code allocates memory for an array of `10` integers. There is a mismatch between the size of an integer pointer (`x`) and the size of memory allocated with malloc().


### `malloc()` Tips

Keep in mind the following things when working with `malloc()`:
* The `malloc()` command returns a valid pointer or `NULL` which serves as the address.
* When working with strings, use `malloc()` instead of `sizeof()`. The code snippet below adds `1` to the length of a string to account for the end-of-string character.
  
  ```c
  malloc(strlen(s) + 1)
  ```
* To be extra careful, you can **cast** the value of the return type. The code below casts the return value of `malloc()` as a `double`.
  
  ```c
  double *myDouble = (double *) malloc(sizeof(double));
  ```

#### Select the `malloc()` statement that is guaranteed to give you the exact size of an integer value.

Click the button below to submit.


- [ ] `int *number = malloc(int);`
- [x] `int *number = malloc(sizeof(int));`
- [ ] `int *number = malloc(myVariable);`
- [ ] `int *number = malloc(8);`

**The correct answer is**:

```
int *number = malloc(sizeof(int));
```

While you can pass all kinds of values to `malloc()`, it is best to use `sizeof()` followed by the data type. That way you ensure you are getting proper size.

## `free()`

## Deallocating Memory

Creating variables, functions, or other items is an obvious time when memory needs to be allocated. Deallocating memory, is more complex. Programmers need to decide if memory should be freed, when, and how to free it.

The `free()` function is used to deallocate memory. Pass it a `malloc()` pointer and the compiler will deallocate all of the memory associated with the pointer. You cannot specify freeing only part of the memory associated with a pointer. It is all or nothing.

The snippet below shows how `free()` is used to deallocate memory once it is no longer needed.

```c
int *x = malloc(5 * sizeof(int)); // allocate memory
...
free(x); // deallocate memory since it is no longer needed.
```
### Common Errors

The C language lacks many of the **automatic memory management** features found in other languages. Languages like Python have **garbage collection** that allocates and deallocates memory so the program works as intended. Manually managing memory means it is easy to make mistakes.

The next few pages will cover common errors associated with memory management.

### Question

Select all of the true statements about memory management and C.

**Hint**: there is more than one correct answer.
- [ ] You can specify the amount of memory to free by passing an integer to `free()`.
- [ ] The C language uses garbage collection to automate memory management.
- [x] Allocate memory with the `malloc()` command.
- [x] Deallocate memory with the `free()` command.

<br>

> The correct answers are:
> * Allocate memory with the `malloc()` command.
> * Deallocate memory with the `free()` command.
> 
> You must manually manage memory when programming in C. Other languages use garbage collection. When deallocating memory, you pass a pointer to `free()`. You cannot specify a number bytes to free.

## Forgetting to Allocate Memory

### Many routines need memory allocation before calling them.

For example, the routine `strcpy(dstPointer, srcPointer)` copies a string from one pointer (`srcPointer`) to another (`dstPointer`). In the first example, memory is allocated for the source pointer but not the destination pointer. The causes a problem when trying to copy a string between pointers.

```c
char *srcPointer = "memory management is hard";
char *dstPointer;        // forgot to allocate memory
strcpy(dstPointer, srcPointer); // program crashes
printf("%s\n", dstPointer);
```

**code**: `forget.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   
  // add your code below this line
  
  char *srcPointer = "memory management is hard";
  char *dstPointer;        // forgot to allocate memory
  strcpy(dstPointer, srcPointer); // program crashes
  printf("%s\n", dstPointer);
  
  // add your code above this line
   
  return(0);
}
```

**compile program**

```
gcc -Wall forget.c -o forget
```

**run program**

```
./forget 

/usr/share/rpc/bash-proxy.sh: line 12:   175 Segmentation fault      (core dumped) $1 "${@:2}"
```

Compiling and running the above code should result in a segmentation fault. Properly allocating memory for dstPointer will fix the bug.

```c
char *srcPointer = "memory management is hard";
char *dstPointer = (char *) malloc(strlen(srcPointer) + 1); // allocate memory
strcpy(dstPointer, srcPointer);
printf("%s\n", dstPointer);
```

**code**: `forget.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   
  // add your code below this line
  
  char *srcPointer = "memory management is hard";
  char *dstPointer = (char *) malloc(strlen(srcPointer) + 1); // allocate memory
  strcpy(dstPointer, srcPointer);
  printf("%s\n", dstPointer);
  
  // add your code above this line
   
  return(0);
}
```

**compile program**

```
gcc -Wall forget.c -o forget
```

**run program**

```
memory management is hard
```

### Question 

What happens when you try to run a program where memory has not been properly allocated?

Click the button below to submit.
- [x] Segmentation fault
- [ ] Invalid data type
- [ ] Undeclared error message
- [ ] No such file or directory

> When trying to use a pointer with unallocated memory, you see a segmentation fault.

### Not Allocating Enough Memory

When trying to use an allocation of memory that is too small, you experience a **buffer overflow**. This is common when allocating strings as you need to take into account the end-of-line character in the string (`strlen(srcPointer + 1)`).

```c
char *srcPointer = "memory management is hard";
char *dstPointer = (char *) malloc(strlen(srcPointer)); // slightly too small
strcpy(dstPointer, srcPointer);
printf("%s\n", dstPointer);
```

**code**: `not_enough.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   
  // add your code below this line
  
  char *srcPointer = "memory management is hard";
  char *dstPointer = (char *) malloc(strlen(srcPointer)); // allocate memory
  strcpy(dstPointer, srcPointer);
  printf("%s\n", dstPointer);
  
  // add your code above this line
   
  return(0);
}
```


**compile program**

```
gcc -Wall not_enough.c -o not_enough
```

**run program**

```
memory management is hard
```

You can compile and run the above program without any errors. The copy function may write one byte too many over the alloted space. In some cases, the `malloc()` library provides a bit of additional space regardless. In other cases, the program can crash. Regardless, be mindful of the end-of-line character when allocating memory

## Forgetting to Initialize Allocated Memory

Running `malloc()` allocates memory, but it does not initialize the memory itself. The following code snippet creates a pointer to an array. No values are in the array, so reading element `6` is an **uninitialized read**. In this case, the program still works, but you should avoid reading uninitialized data.

```c
int *arr;
int sz = 10;
arr = (int *)malloc(sz * sizeof(int));
printf("%d\n", arr[6]);  // access uninitialized data
```

**code**: `not_enough.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   
  // add your code below this line
  
  int *arr;
  int sz = 10;
  arr = (int *)malloc(sz * sizeof(int));
  printf("%d\n", arr[6]);  // access uninitialized data
  
  // add your code above this line
   
   return(0);
}
```


**compile program**

```
gcc -Wall not_enough.c -o not_enough
```

**run program**

```
0
```

### What is a buffer overflow?

- [x] Trying to access memory that goes beyond what has been allocated.
- [ ] When too much memory has been allocated.
- [ ] When memory has been allocated but not yet initialized.
- [ ] When memory has been initialized but not yet allocated.

> A buffer overflow occurs when too little memory has been allocated and the program is trying to access memory that exceeds the alloted amount.

## Forgetting to Free Memory

Another common error is **forgetting to free memory** after it is no longer needed. This leads to something called a **memory leak**.

Memory leaks are not noticeable at first, but over time more and more of the system’s memory is used by the offending program. Performance begins to suffer. You need to restart the system to reset the memory.

Be vigilant to release memory once you are done with it. Memory leaks can exist in languages with garbage collection as well.

Adopting a garbage-collected language doesn’t help in this case: if you still have a reference to some region of memory, no garbage collector will ever free it, so memory leaks persist even in more recent languages.

You may think that with a short-lived program you do not need to free memory. The OS will clean up the memory upon exiting. While this is true in one sense, it is a good idea to get into the habit of following best practices.

If you explicitly allocate memory, you should deallocate it as well.

### Other Errors When Freeing Memory

#### Freeing Memory Before You’re Done With It

A **dangling pointer** occurs when memory is freed while the program still needs it. Calling `malloc()` after calling `free()` can cause this error. The program can crash or overwrite good memory.

#### Freeing Memory Repeatedly

A **double free** occurs when a program frees the same memory twice. This may cause a crash because the memory-allocation library can become confused.

### Calling `free()` Incorrectly

Calling `free()` requires you to pass it a pointer. Using a different value as the parameter can cause problems.

**True or False**: Only release memory on long-running programs.
- [ ] True
- [ ] False

> False. Do not rely on the system to deallocate memory. The general rule should be: deallocate all memory that you explicitly allocate.

## Underlying OS Support: `brk/sbrk`

So far, we have been using `malloc()` and `free()` to allocate and release memory. These commands are library calls; they are not system calls. Managing virtual memory is built on top of system calls, which means `malloc()` and `free()` make system calls to allocate or release memory.

### `brk() / sbrk()`

`brk()` and `sbrk()` are two common system calls to manage memory. Higher-level functions like `malloc()` call `brk()` and `sbrk()`.

* **`brk()`** - changes the program’s **break** (the end of the heap). Pass `brk()` an argument which is the new program break address. The heap will increase or decrease based on the new break size.
* **`sbrk()`** - think of this as a wrapper for `brk()`. Instead of a passing a new address for the program break, you can pass an increment to adjust the size of the program break.
  
Let’s see how these two system calls work in the next program (`sbrk.c`).

```c
#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    void* programBreak = sbrk(0);
    printf("Original program break: %p\n", programBreak);
    programBreak = (void*) programBreak + 1;
    printf("New break value: %p\n", programBreak);
    brk(programBreak);
    printf("New program break: %p\n", sbrk(0));
    
    return(0);

}
```

* The first line creates `programBreak` whose value is `sbrk(0)`. `sbrk(0)` is the value of the program’s current break.
* The second line prints `programBreak` with a message that this is the current break.
* The third line creates a new value for `programBreak`.
* The fourth line prints this new value.
* The fifth line calls `brk(programBreak)` which updates the break to the value of `programBreak`.
* The sixth line prints `sbrk(0)` which is the value of the program break. The address from lines 5 and 6 should be the same.

**Compile**

```
gcc -Wall sbrk.c -o sbrk
```

**Run**

```
./sbrk
```

**Outuput**

```
Original program break: 0x6070945c7000
New break value: 0x6070945c7001
New program break: 0x6070945c7001
```

Your output should look similar to the output below, but your addresses will be different.

```
Original program break: 0x562bd736f000
New break value: 0x562bd736f001
New program break: 0x562bd736f001
```

> [!warning]
> You should never directly call `brk()` or `sbrk()`. Instead, call `malloc()` and `free()` and let them handle the systems calls. This is the safer way to manage memory.

### Question

What is the relationship between `malloc()/free()` and `brk/sbrk`?
- [ ] `malloc()` and `free()` manage physical memory while `brk` and `sbrk` manage virtual memory.
- [x] `malloc()` and `free()` are library calls that sit on top of the system calls `brk` and `sbrk`.
- [ ] Your programs should directly call `brk` and `sbrk` and let them call `malloc()` and `free()`.
- [ ] `malloc()` and `free()` are system calls that sit on top of the library calls `brk` and `sbrk`.

> Both `malloc()` and `free()` are library calls that manage virtual memory. When physical memory needs to be changed, these library calls invoke the system calls `brk` and `sbrk`.

## Underlying OS Support: `mmap`

Another way to allocate system memory is with `mmap()`. This establishes a region of anonymous memory, which cab be treated like a heap. Successfully running `mmap()` will return a pointer to the mapped area.

Let’s look at a quick example in the code to the left, `mmap.c`.

```c
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    #define PAGESIZE 4096
  
    void *pointer1 = mmap (NULL, PAGESIZE,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
    
    void *pointer2 = mmap (NULL, PAGESIZE,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
  
    printf("First page: %p\n", pointer1);
    printf("Second page: %p\n", pointer2);
  
    return 0;
}
```

**compile program**

```
gcc -Wall mmap.c -o mmap
```

**run program**

```
./mmap
```

**ouput**

```
First page: 0x776962d26000
Second page: 0x776962d25000
```

Here we are allocating a block of memory to `pointer1` and another to `pointer2`. Here is what the parameters do:
* `NULL` - Tells the compiler we don’t care where the memory is allocated.
* `PAGESIZE` - Tells the compiler how much memory to allocate. In this example, it is 4,096 bytes.
* `PROT_READ | PROT_WRITE` - Provides protection for reading reading and writing to region that has been mapped. You can read and write to the memory in this example.
* `MAP_PRIVATE` - The is marked as “private” because it is not shared with another process.
* `MAP_ANONYMOUS` - A file has not been mapped, so it is marked as "anonymous".

This difference between addresses should be small. Update the code for `pointer1` so that its allocated memory is much larger than `pointer2`. You should see a bigger difference between the memory addresses.

```c
void *pointer1 = mmap (NULL, 40 * PAGESIZE,
                       PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
```

**compile program**

```
gcc -Wall mmap.c -o mmap
```

**run program**

```
./mmap
```

**output**

```
First page: 0x7e8f3d7c6000
Second page: 0x7e8f3d7f4000
```

If you are looking for a way to allocate memory and not use `malloc()`, `mmap()` is a much better choice than `brk` and `sbrk`.

### Question

Select the `mmap()` parameter that lets you read and write to the allocated memory.
- [x] `PROT_READ | PROT_WRITE`
- [ ] `MAP_READ | MAP_WRITE`
- [ ] `READ_PROT | WRITE_PROT`
- [ ] `READ | WRITE`

> To allow for reading and writing to the allocated memory, use `PROT_READ` and `PROT_WRITE`

## `calloc()` and `realloc()`

### `calloc()`

The `calloc()` command is similar to `malloc()` in that it is used to allocate memory. Unlike `malloc()`, `calloc()` takes two parameters. The first is the size of memory allocation and the second is number of elements. Looks at the code snippet below. Each line of code allocates memory for an array of 10 integers; `malloc()` uses multiplication to represent the number of elements, while `calloc()` uses a second parameter.

```c
// both lines of code allocates memory for an array of 10 integers

int *arrMalloc = malloc(sizeof(int) * 10);
int *arrCalloc = calloc(sizeof(int), 10);
```
Copy and paste the following code in to the IDE. Compile and run the program.

```c
int *arr = calloc(sizeof(int), 10);
  
int i;
for (i = 0; i < 10; i++) {
  printf("[%d]", arr[i]);
}
```

**code**: `calloc.c`

```c
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  
  // add your code below this line

  int *arr = calloc(sizeof(int), 10);
  
  int i;
  for (i = 0; i < 10; i++) {
    printf("[%d]", arr[i]);
  }

  // add your code above this line

  return 0;
}
```

**compile program**

```
gcc -Wall calloc.c calloc
```

**run program**

```
./calloc
```

**output**

```
[0][0][0][0][0][0][0][0][0][0]
```

The program should print out a representation of the array. Notice how each element has been initialized to `0`. This is done by `calloc()` during allocation.

### `realloc()`


If you find yourself need more (or less) memory than you originally allocated, the `realloc()` command will help in this regard. In the example below. the variable `arr` starts as an array of 5 integers (as shown by the first loop). The same array is expanded to 10 integers through the use of `realloc()`.

```c
int *arr = calloc(sizeof(int), 5);
  
int i;
for (i = 0; i < 5; i++) {
  printf("[%d]", arr[i]);
}
  
arr = realloc(arr, sizeof(int) * 10);
  
for (i = 0; i < 5; i++) {
  printf("[%d]", arr[i]);
}
```

**compile program**

```
gcc -Wall calloc.c calloc
```


**run program**

```
./calloc
```

**output**

```
[0][0][0][0][0][0][0][0][0][0]
```

When you are reallocating memory with `realloc()`, keep in mind that the pointer to the new memory allocation could change. All this means is the was not enough space for the new block of memory at the current location. The compiler will find a new block and transfer any information to the new block. This may cause a problem if you have other pointers that point to the reallocated pointer.

### Question

Fill in the blanks below.
- **`free`** - Releases memory back to the system.
- **`calloc`** - Allocates memory using only a single parameter.
- **`malloc`** - Allocates memory using two parameters.
- **`realloc`** - Reallocates memory.


> The correct answers are:
> - **`free`** - Releases memory back to the system.
> - **`calloc`** - Library call that allocates memory using only a single parameter
> - **`malloc`** - Library call that allocates memory using two parameters.
> - **`realloc`** - Reallocates memory.
> 
> Both `brk` and `sbrk` are system calls, not library calls; release is not a memory command.

