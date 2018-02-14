
#include <string.h>

static int limit = 50;
static int cutoff = 10;
static int wcutoff = 4;
static int duration = 5;

#include "pixel.h"
#include "array.h"
#include "graph.h"


void cluster(struct image *img) {
    int *sub=NULL;

    initFrame(img);

    sub = substractFrames(img->data, img->prev->data);
    identifyPix(img, sub, limit); // build lists of bright (>0) and dark (<0) pixels from sub

    if ( buildAdj(img, cutoff) == 1) return; // build adjacency matrix between bright (>0) and dark (<0) pixels
    
    generateGraphs(img); // sort vv-matrix to VV-matrix
}

int analyseGraphs(struct image *img) {
    int i;
    
    for (i=0; i<(img->num); i++) {
	getVertexPositions(img->met[i]);
	getPosition(img->met[i]);
	assignContinuity(img, img->met[i], 20, 3);

	buildWeights(img->met[i], wcutoff);
	degrees(img->met[i]);
	meanDegree(img->met[i]);
	meanWeight(img->met[i]);

	density(img->met[i]);

	getVelocity(img->met[i]);
    }

    for (i=0; i<(img->num); i++) {
	backTraceMeteor(img->met[i]);
    }

    return 0;
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

