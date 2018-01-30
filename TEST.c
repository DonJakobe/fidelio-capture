
#include <stdlib.h>
#include <stdio.h>

#include "array.h"

int main() {
    int i, j;
    int **a;
    int **b;
    int c[4][4] = {1,2,3,4,2,5,6,7,3,6,8,9,4,7,9,0};

    a = (int **) malloc(4*sizeof(int *));
    b = (int **) malloc(4*sizeof(int *));
    for (i=0; i<4; i++) {
	a[i] = (int *) malloc(4*sizeof(int));
	b[i] = (int *) malloc(4*sizeof(int));
    }

    for (i=0; i<4; i++) {
	for (j=0; j<4; j++) {
	    a[i][j] = c[i][j];
	}
    }

    printArray(a, 4, 4);

    switchRows(a, 2, 1, 4);

    printArray(a, 4, 4);

    cpy2dArray(a, b, 4);

    printArray(b, 4, 4);
}


