#include <stdio.h>
#include <stdlib.h>

int x = 3;
int *p3;

int main(int argc, char *argv[]) {
    int y;
    p3 = &x;
    double z = 1.5;
    int *p1 = &y;
    *p1 = -1;
    double *p2 = &z;
    *p2 = *p3 + z;
    printf("y = %d, z = %.2lf\n", y, z);
    *p3 = *p1 + *p2;
    printf("x = %d, y = %d, z = %.2lf\n", x, y, z);
    return 0;
}