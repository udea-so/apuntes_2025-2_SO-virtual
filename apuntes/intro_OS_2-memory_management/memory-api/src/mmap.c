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
