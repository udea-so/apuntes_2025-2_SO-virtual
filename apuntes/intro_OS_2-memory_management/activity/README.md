# Exercise 1

Write a C program that:
* Requests the length, N, of an array as user input.
* Prompts the user to enter each integer array value
* Uses the malloc() function to dynamically allocate memory to hold N integer numbers entered by the user
* Checks if memory has been properly allocated
* Prints the sum of all of the array values.
* Frees up used memory when finished

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  
  // YOUR CODE HERE!
  
  return 0;
}
```

Your output should look like the output below when run.

```
Enter value of N [1-10]: 3
Enter 3 integer number(s)
Enter #1: 1
Enter #2: 2
Enter #3: 3
Sum: 6
```


```
gcc malloc1.c -o malloc1
```