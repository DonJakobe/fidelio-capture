
#include <string.h>

int counter=0;

const int limit = 30;
static int cutoff = 10;

#include "pixel.h"
#include "array.h"
#include "graph.h"


void cluster(void) {
    int i, j;
    int *sub=NULL;
    initFrame(frm);

    sub = substractFrames(frm->data, frm->prev->data);
    identifyPix(frm, sub, limit); // build lists of bright (>0) and dark (<0) pixels from sub

    if ( buildAdj(frm, cutoff) == 1) return; // build adjacency matrix between bright (>0) and dark (<0) pixels
    
    sortAdj(frm); // sort vv-matrix to VV-matrix

    printImage(frm);
}

/*
void buildWeights(void) {
    int i, j, k;
    int N;
    int *Pix; //Pixel (lghtPix and shdwPix belonging to one cluster)
    float **w; //weights between Pix, depending on their distance

    for (i=0; i<(frm->num); i++) {
	N = frm->numLght[i] + frm->numShdw[i];
	Pix = calloc(N, sizeof(int));
	
	for (j=0; j<N; j++) {
	    for (k=0; k<N; k++) {
		w = 
*/

int check(void) {
	if (frm->index == 1) counter++;
	printf("%i/frame %i ################################################\n", counter, frm->index);
	
	cluster();
	
	if(frm->index == 150) {
	    freeBuffer(frm);
	    exit(0);
	}

	return 0;
}

