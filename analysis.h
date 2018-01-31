
#include <string.h>

static int sub[length];
static int bright[length];
static int dark[length];

const int limit = 50;
const int dist = 4;

#include "array.h"
#include "graph.h"
#include "pixel.h"


void group(void) {
    int i;
    int v;
    int u;
    int **vu;
    int **vv;
    free2dArray(frms->metlist, frms->nbright);

    identifyPix(limit, &v, &u, sub, bright, dark); // build lists of bright (>0) and dark (<0) pixels from sub

    frms->nbright = v;
    frms->ndark = u;

    printf("MEMORY: %i\n", sizeof(frms->metlist[0][0]));
    printf("MEMORY: %i\n", sizeof(frms->metlist[0]));
    printf("MEMORY: %i\n", sizeof(frms->metlist));
    free(frms->npix);

    // dynamically reserve memory for matrices
    vu = (int **) malloc(v*sizeof(int *));
    vv = (int **) malloc(v*sizeof(int *));
    frms->metlist = (int **) malloc(v*sizeof(int *));

    for (i=0; i<v; i++) {
	vu[i] = (int *) malloc(u*sizeof(int));
	vv[i] = (int *) calloc(v, sizeof(int));
	frms->metlist[i] = (int *) calloc(v, sizeof(int));
    }
    
    frms->npix = (int *) calloc(v, sizeof(int));
    
    buildAdj(v, u, dist, bright, dark, vu); // build adjacency matrix between bright (>0) and dark (<0) pixels
    buildAdj2(v, u, vu, vv); // build vv-matrix

    printf("\nV x U:\n");
    print2dArray(vu, v, u);
    printf("\nV x V:\n");
    print2dArray(vv, v, v);
    
    sortAdj(v, vv); // sort vv-matrix to VV-matrix

    printf("\nV x V (sorted):\n");
    print2dArray(vv, v, v);
    printf("\nMETLIST:\n");
    print2dArray(frms->metlist, v, v);
    printf("\nNPIX:\n");
    print1dArray(frms->npix, frms->nmet);
    printf("\n\nNMET: %i\n", frms->nmet);

    free2dArray(vu, v);
    free2dArray(vv, v);
}



int check(void) {
	printf("frame %i\n", frms->index);
	
	substractFrames(frms->data, frms->prev->data, sub);
	group();

	return 0;
}



