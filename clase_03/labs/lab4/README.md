## Lab 4
Start by compiling and running the program in the IDE. 

```c
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main() {
  int id = fork();
  int n;
  
  if (id == 0) {
    n = 1;
  } else {
    n = 6;
  }
  
  int i;
  for (i = n; i < n + 5; i++) {
    printf("%d ", i);
  }

  return 0;
}
```

You should see the following output:

```
6 7 8 9 10 1 2 3 4 5 
```

Modify the program by adding `wait(NULL)`; so that it prints the numbers 1 to 10 in ascending order.



