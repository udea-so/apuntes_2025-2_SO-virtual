#include <stdio.h>
#include <stdlib.h>

#define TAM 6

int main(int argc, char *argv[]) {
    int *p1 = (int *)malloc(TAM * sizeof(int));
    int *p2 = p1 + (TAM - 1);
    int i = 0;
    int j = TAM - 1;
    int impar = 1;
    while (i < j){
        /* code */
        *(p1 + i) = 2*i;
        *p2 = impar;
        impar += 2;
        p2--;
        i++;
        j--;
    }
    return 0;
}