
#include <string.h>

int counter=0;

static int sub[length];
int *lght=NULL;
int *shdw=NULL;

const int limit = 50;
const int dist = 10;

#include "array.h"
#include "graph.h"
#include "pixel.h"


void cluster(void) {
    int i, j;
    int v, u;
    int **vu=NULL;

    initFrame(frms);
    lght = initList(lght);
    shdw = initList(shdw);

    identifyPix(limit, &v, &u, sub); // build lists of bright (>0) and dark (<0) pixels from sub

    vu = alloc2dArray(vu, v, u); // dynamically reserve memory for matrix

    vu = buildAdj(&v, &u, dist, vu); // build adjacency matrix between bright (>0) and dark (<0) pixels
    
    if (vu == NULL) {
	return;
    }

    sortAdj(vu, v, u); // sort vv-matrix to VV-matrix

    printf("\nV x U (sorted):\n");
    print2dArray(vu, v, u);

    printf("LIGHT ");
    print1dArray(frms->numLght, frms->num);
    print2dRagged(frms->lghtPix, frms->num, frms->numLght);

    printf("\n");

    printf("SHADOW ");
    print1dArray(frms->numShdw, frms->num);
    print2dRagged(frms->shdwPix, frms->num, frms->numShdw);

    vu = free2dArray(vu, v);
    vu = NULL;
}



int check(void) {
	if (frms->index == 1) counter++;
	printf("%i/frame %i ################################################\n", counter, frms->index);
	
	substractFrames(frms->data, frms->prev->data, sub);
	cluster();
	
	if(frms->index == 150) {
	    freeBuffer(frms);
	    if (lght != NULL) free(lght);
	    if (shdw != NULL) free(shdw);
	    exit(0);
	}

	return 0;
}

