
#include <stdlib.h>
#include <stdio.h>

#include "array.h"

int main() {

    int *a = NULL;
    //a = malloc(sizeof(int));
    //a[0] = 5;
    addToList(&a, 4, 0);

    //a = realloc(a, 2*sizeof(int));
    addToList(&a, 7, 1);

    a[1] = 6;

    printf("number: %i\n", a[0]);
    printf("number: %i\n", a[1]);

    free(a);

    return 0;
}


