
#include <stdlib.h>
#include <stdio.h>

#include "array.h"

int main() {
    int i, j;
    int **a;
    int c[4][4] = {1,2,3,4,2,5,6,7,3,6,8,9,4,7,9,0};
    int *d=NULL;
    int **e=NULL;
    
    
    a = (int **) malloc(4*sizeof(int *));
    for (i=0; i<4; i++) {
	a[i] = (int *) malloc(4*sizeof(int));
    }
    

    //d = (int *) malloc(4*sizeof(int *));

    for (i=0; i<4; i++) {
	//addToList(&d, i, i);
	for (j=0; j<4; j++) {
	    a[i][j] = c[i][j];
	}
    }

    print2dArray(a, 4, 4);

    switchRows(a, 1, 2, 4);
    switchCols(a, 1, 2, 4);

    print2dArray(a, 4, 4);

    a = free2dArray(a, 4);

    /*
    a = expandList(a, 55, 4);
    a[4] = addToList(a[4], 56, 1);
    a[4] = addToList(a[4], 57, 2);
    a[4] = addToList(a[4], 58, 3);
    print2dArray(a, 5, 4);
    //a = free2dArray(a, 5);

    for (i=0; i<5; i++) {
	free(a[i]);
    }
    free(a);
    */


    /*
    int rows = 4;
    int cols = 4;
    //a = rmRow(a, 1, &rows);
    a = rmCol(a, 1, rows, &cols);
    print2dArray(a,4,3);

    a = free2dArray(a, 4);
    */

    //addToList(a[4], 2, 1);

    //print2dArray(a, 5, 4);

    //printf("p%p\n", e);
    //e = expandList(e, 1, 0);

    //printf("ele %i\n", e[0][0]);

    //print2dArray(e, 1, 1);
    //addToList(&d, 5, 0);
    //printf("ele %i\n", d[0]);
    //print1dArray(d, 4);
    //free(d);

    return 0;
}


