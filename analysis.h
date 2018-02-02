
#include <string.h>

int counter=0;

static int sub[length];
int *light=NULL;
int *shadow=NULL;

const int limit = 50;
const int dist = 4;

#include "array.h"
#include "graph.h"
#include "pixel.h"


void group(void) {
    int i, j;
    int v;
    int u;
    int **vu=NULL;


    initFrame(frms);
    light = initList(light);
    shadow = initList(shadow);

    identifyPix(limit, &v, &u, sub); // build lists of bright (>0) and dark (<0) pixels from sub

    vu = alloc2dArray(vu, v, u); // dynamically reserve memory for matrix

    buildAdj(&v, &u, dist, vu); // build adjacency matrix between bright (>0) and dark (<0) pixels
    
    if ( (light == NULL) | (shadow == NULL)) return;

    //print2dArray(vu, v, u);

    sortAdj(vu, v, u, frms->num); // sort vv-matrix to VV-matrix

    printf("\nV x U (sorted):\n");
    print2dArray(vu, v, u);
    printf("numl nums");
    print1dArray(frms->numlight, frms->num);
    print1dArray(frms->numshadow, frms->num);
    printf("num: %i\n", frms->num);

    vu = free2dArray(vu, v);
}



int check(void) {
	if (frms->index == 1) counter++;
	printf("%i/frame %i\n", counter, frms->index);
	
	substractFrames(frms->data, frms->prev->data, sub);
	group();
	
	if(frms->index == 150) {
	    //freeBuffer(frms, buffer_size);
	    exit(0);
	}

	return 0;
}



