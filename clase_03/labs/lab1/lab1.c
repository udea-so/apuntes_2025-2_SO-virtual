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