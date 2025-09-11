#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

int main() {
        int *ptr = NULL;
        int i =0;
        //dynamic allocation for 1 integer value. 
        ptr = (int *)malloc(sizeof(int));
        //place value on memory created
        *ptr = 5;
        // Read value from memory
        printf("%d\n", *ptr);

        //Expand existing memory for 4 more integers
        // size of 1 integer* 5
        // Reallocate memory
   ptr = (int *) realloc(ptr, sizeof(int)*5);

   //place 4 numbers on expanded memory
   // 1 2 3 4
        for (i = 1; i < 5; i++) {
                ptr[i] = i;
        }

   // Read value from re-allocated memory
        //It should show numbers 5,1,2,3,4
        for (i = 1; i < 5; i++) {
                printf("%d\n", ptr[i]);
        }

        //Free allocated memory
        free(ptr);

        return 0;
}
