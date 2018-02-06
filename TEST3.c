#define height 3
#define width 3
#define length 9

#include <stdlib.h>
#include <stdio.h>

int *light=NULL;
int *shadow=NULL;

static struct image *frms;

static int sub[length];

const int limit = 5;
const int dist = 2;

#include "met.h"
#include "array.h"
#include "pixel.h"
#include "graph.h"

int main() {
    int i, j;
    int v, u;
    int **vu=NULL;
    
    int a[9] = {10,10,0,10,10,0,0,0,0};
    int b[9] = {0,0,0,0,10,10,0,10,10};

    frms = buildBuffer(2);

    initFrame(frms);
    initFrame(frms->next);

    for (i=0; i<(width*height); i++) {
	    frms->data[i] = a[i];
	    frms->next->data[i] = b[i];
    }

    substractFrames(frms->data, frms->prev->data, sub);

    identifyPix(limit, &v, &u, sub);

    for (i=0; i<9; i++) {
	printf("%i ", sub[i]);
    }
    printf("\n");

    vu = alloc2dArray(vu, v, u);

    vu = buildAdj(&v, &u, dist, vu);

    //print1dArray(shadow, 9);

    printf("v%i, u%i \n", v, u);

    print2dArray(vu, v, u);

    
    sortAdj(vu, v, u);

    print2dArray(vu, v, u);

    printf("num %i\n", frms->num);
    

    vu = free2dArray(vu, v);
    //for (i=0; i<v; i++) {
	//free(vu[i]);
    //}
    //free(vu);

    free(light);
    free(shadow);

    freeBuffer(frms);
    
    return 0;
}


