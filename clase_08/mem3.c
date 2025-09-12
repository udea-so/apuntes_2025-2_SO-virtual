#include <stdio.h>
#include <stdlib.h>

int x = 3;


int main(int argc, char *argv[]) {
    int *p1;
    p1 = &x;
    int *p2 = (int *)malloc(sizeof(int));
    *p2 = 5;
    free(p2);  // Liberar la memoria   
    p2 = NULL;
    p2 = p1;
    printf("x = %d, *p1 = %d, *p2 = %d\n", x, *p1, *p2);    
    return 0;
}
