# Lab 2


Copy the provided code samples and run in them in the program to the left. Use the output to help you answer the following questions.



```c
#include <stdio.h>
#include <unistd.h>

int main()
{
  
  // add your code below this line
  
  
  
  // add your code above this line

  return 0;
}
```


How many times will the program print hello if you add the following code to the IDE?

  fork();
  fork();
  printf("hello\n");



How many times will the program print hello if you add the following code to the IDE?

  fork();
  fork();
  fork();
  printf("hello\n");


------

The program would print the output 8 times. To help with discussion, the two fork() commands will be referred to as L1 (Line 1), L2 (Line 2), and L3 (Line 3).


fork(); //Line 1
fork(); //Line 2
fork(); //Line 3
The graphic below shows all of the printf() calls from the for() commands.


     L1
   /   \
  L2   L2
 / \   / \
L3 L3 L3 L3
So forking will print hello 7 times, plus the another print from the main process. That is a total of 8 lines of output.

----

Lab Question
What is the general rule for how many time the program will print hello when you call fork() $n$
 number of times?

- $2^n$
- $2*n$
- $n^2$
- $n+2$