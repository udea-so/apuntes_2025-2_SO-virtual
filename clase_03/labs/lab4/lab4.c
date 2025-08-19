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
