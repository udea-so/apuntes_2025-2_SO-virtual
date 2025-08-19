# Lab 3

Use the program to the left to help you answer the following questions.

```c
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main() {
  if (fork() == 0) {
    printf("Hello from child\n");
  }
  else   {
    printf("Hello from parent\n");
  }

  return 0;
}
```

Lab Question
Where do you add wait(NULL); in the program so that the output is:

```
Hello from child
Hello from parent
```

* Put wait(NULL); in the if branch.
* Put wait(NULL); after the else branch.
* Put wait(NULL); in the else branch.
* Put wait(NULL); before the if branch.


