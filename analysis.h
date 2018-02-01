
#include <string.h>

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
    int **vu;
    int **vv;

    initFrame(frms);
    light = initList(light);
    shadow = initList(shadow);

    //printf("l%p, s%p\n", light, shadow);
    identifyPix(limit, &v, &u, sub); // build lists of bright (>0) and dark (<0) pixels from sub
    //printf("v%i, u%i\n", v, u);
    //printf("l%p, s%p\n", light, shadow);
    //print1dArray(light, v);
    //print1dArray(shadow, u);

    if ( (light == NULL) | (shadow == NULL)) {
	printf("ESCAPE\n");
	return;
    }
    // dynamically reserve memory for matrices
    
    vu = (int **) malloc(v*sizeof(int *));

    for (i=0; i<v; i++) {
	vu[i] = (int *) malloc(u*sizeof(int));
    }

    buildAdjOLD(v, u, dist, light, shadow, vu); // build adjacency matrix between bright (>0) and dark (<0) pixels

    print2dArray(vu, v, u);
    printf("FOOOOO");
    
    buildAdj(&v, &u, dist, vu); // build adjacency matrix between bright (>0) and dark (<0) pixels

    print2dArray(vu, v, u);

    //rmRow(vu, &v, u);
    

    //printf("\nV x U:\n");
    //print2dArray(vu, v, u);
    //printf("\nV x V:\n");
    //print2dArray(vv, v, v);
    //sortAdj(vu, v, u, frms->num); // sort vv-matrix to VV-matrix

    /*
    printf("\nV x V (sorted):\n");
    print2dArray(vv, v, v);
    printf("\nMETLIST:\n");
    print2dArray(frms->metlist, v, v);
    printf("\nNPIX:\n");
    print1dArray(frms->npix, frms->nmet);
    printf("\n\nNMET: %i\n", frms->nmet);
    */

    //free2dArray(vu, v);
    //free2dArray(vv, v);
}



int check(void) {
	printf("frame %i\n", frms->index);
	
	substractFrames(frms->data, frms->prev->data, sub);
	group();

	return 0;
}



