#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int x = 3, y;
    int *p1;
    int *p2 = &x;
    p1 = &y;
    *p1 = *p2 + 2;
    p1 = p2; // p1 = &x;
    *p1 = *p2 + 2;
    int *p3 = 1000;
    printf("x = %d, y = %d\n", x, y);
    return 0;
}