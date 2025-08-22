# Exercises 

## Exercise 1

### Q1

Write a program that calls `fork()`. Before calling `fork()`, have the `main()` process access the variable `num` and set its value to `100`.
* The parent process should print the value of `num` in the format value in `parent process: 100`
* The child process should also print the value of `num` in the same format on the following line.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int num;

int main(int argc, char *argv[]) {

  // add code below this line    
  num = 100;
  int id = fork();

  if (id == 0) {
    printf("value in child process: %d\n", num);
  } else if (id > 0) {
    printf("value in parent process: %d\n", num);
  } else {
    printf("fork did not work as intended\n");
    exit(1);
  } 
  // add code above this line
  
  return 0;
}
```

### Q2
What is the value of the variable num in the child process?
* The value of num is not changed in the child process so it will be 100, the initial value.

### Q3
What happens to `num` when it is accessed and changed in both the parent and the child processes?
Select an answer and click the button below to submit.
* The child process retains its own value for `x`. (Rta)
* The child process inherits the variable value of `x` from the parent, so the variables are the same.
* The child process returns a NULL value for `x`.
* The program crashes.

## Exercise 2

Write another program using `fork()`.
* The child process should print `Hello from the child`
* The parent process should print `Goodbye from the parent`.
* Make sure that the child process always prints first without calling `wait()` in the parent process.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  // insert your code below this line
  int id = fork();
  if (id == 0) {
    printf("Hello from the child\n");
  } 
  else if (id > 0) {
    sleep(1);
    printf("Goodbye from the parent\n");
  } 
  else {
    printf("fork did not work as intended\n");
    exit(1);
  }     
  // insert your code above this line

  return 0;
}
```

