
#include <stdlib.h>
#include <stdio.h>

#include "array.h"

int main() {

    /*
    int *a = NULL;
    //a = malloc(sizeof(int));
    //a[0] = 5;
    a = addToList(a, 4, 0);

    //a = realloc(a, 2*sizeof(int));
    a = addToList(a, 7, 1);

    printf("number: %i\n", a[0]);
    printf("number: %i\n", a[1]);

    a = rmFromList(a, 0, 2);

    printf("number: %i\n", a[0]);

    free(a);
    */

    int i, j;
    int r = 3, c = 3;
    int **b = malloc(r*sizeof(int*));

    for (i=0; i<r; i++) {
	b[i] = malloc(c*sizeof(int));
	for (j=0; j<c; j++) {
	    b[i][j] = i*j;
	}
    }
    
    print2dArray(b, r, c);

    b = rmCol(b, 1, r, &c);

    /*
    for (i=0; i<r; i++) {
	b[i] = rmFromList(b[i], 1, c);
    }
    
    c--;
    */

    print2dArray(b, r, c);

    b = rmRow(b, 0, &r);

    print2dArray(b, r, c);

    for (i=0; i<r; i++) {
	free(b[i]);
    }

    free(b);

    return 0;
}


