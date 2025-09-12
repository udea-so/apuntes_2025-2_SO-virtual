#include <stdio.h>
#include <stdlib.h>

#define TAM 4

int A[TAM];

int main(int argc, char *argv[]) {
    int i = 0;
    int B[] = {1,2,3,4};

    for(i = 0; i < TAM; i++) {
        A[i] = B[(TAM - 1) -i];
    }    
    int *p = (int *)malloc(TAM * sizeof(int));
    for(i = 0; i < TAM; i++) {
        p[i] = A[i];
    }

    free(p);    
    p = NULL;

    return 0;
}
