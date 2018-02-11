
#include <string.h>

static int limit = 50;
static int cutoff = 10;
static int wcutoff = 5;

#include "pixel.h"
#include "array.h"
#include "graph.h"


void cluster(struct image *img) {
    int *sub=NULL;

    initFrame(img);

    sub = substractFrames(img->data, img->prev->data);
    identifyPix(img, sub, limit); // build lists of bright (>0) and dark (<0) pixels from sub

    if ( buildAdj(img, cutoff) == 1) return; // build adjacency matrix between bright (>0) and dark (<0) pixels
    
    sortAdj(img); // sort vv-matrix to VV-matrix
    metPos(img);
    assignContinuity(img, 20, 3);
}

void analyseGraphs(struct image *img) {
    int i;
    
    for (i=0; i<(img->num); i++) {
	img->met[i]->Ntot = img->met[i]->Nlght + img->met[i]->Nshdw;

	buildWeights(img->met[i], wcutoff);
	density(img->met[i]);
	backTraceMeteor(img->met[i]);
    }
}

int analyseFrame(void) {

    printf("frame %i ################################################\n", frm->index);
   
    cluster(frm);
    analyseGraphs(frm);
    printImage(frm);
    
    if(frm->index == 150) {
	freeBuffer(frm);
	exit(0);
    }
    
    return 0;
}

