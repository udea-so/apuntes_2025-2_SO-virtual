# Lab 1

Look over the code on the left. The program forks a process and has three different branches. Add the following line of code to various parts of the program to help you answer the questions below.

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    int id;

    id = fork();
    if (id == 0) {
      // Branch A
      
    }
    else if (id > 0) {
      // Branch B
      
    }
    else {
      // Branch C
      
    }

    return 0;
}
```

Lab Question
Which branch is for the parent branch?

Branch B

Branch A

Branch C

Which is branch is for the child process?
Branch B
Branch A
Branch C


Which branch is for when the fork fails?
Branch A
Branch C
Branch B