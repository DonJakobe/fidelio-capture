
#include <stdlib.h>
#include <stdio.h>

#include "array.h"

int main() {
    int i, j;
    int **a;
    int **b;
    int c[4][4] = {1,2,3,4,2,5,6,7,3,6,8,9,4,7,9,0};
    int *d=NULL;
    
    printf("malloc0: %p\n", malloc(0));

    a = (int **) malloc(4*sizeof(int *));
    b = (int **) malloc(4*sizeof(int *));
    for (i=0; i<4; i++) {
	a[i] = (int *) malloc(4*sizeof(int));
	b[i] = (int *) malloc(4*sizeof(int));
    }

    d = (int *) malloc(4*sizeof(int *));

    for (i=0; i<4; i++) {
	addToList(d, i, i);
	for (j=0; j<4; j++) {
	    a[i][j] = c[i][j];
	}
    }

    print2dArray(a, 4, 4);

    //expandList(a, 55, 0);
    //print2dArray(a, 5, 4);

    printf("FF: %i\n", a[3][0]);
    printf("*FF: %p\n",&a[3][0]);

    printf("[[%p]]\n", a);
    for(i=0; i<5; i++) {
	printf("[%p] ", a[i]);
	for(j=0; j<4; j++) {
	    printf("%p ", &a[i][j]);
	}
	printf("\n");
    }

    int r = 4;
    rmRow(a, 1, &r);
    print2dArray(a,3,4);

    //print1dArray(a[0], 5);
    printf("\n");

    //addToList(a[4], 2, 1);

    //print2dArray(a, 5, 4);

    print1dArray(d, 4);
    rmFromList(d, 1, 4);
    print1dArray(d, 3);
}


