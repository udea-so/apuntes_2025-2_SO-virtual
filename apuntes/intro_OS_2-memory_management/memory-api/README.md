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
