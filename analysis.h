
#include <string.h>

int counter=0;

const int limit = 50;
static int cutoff = 10;

#include "pixel.h"
#include "array.h"
#include "graph.h"


void cluster(struct image *img) {
    int i, j;
    int *sub=NULL;
    initFrame(img);

    sub = substractFrames(img->data, img->prev->data);
    identifyPix(img, sub, limit); // build lists of bright (>0) and dark (<0) pixels from sub

    if ( buildAdj(img, cutoff) == 1) return; // build adjacency matrix between bright (>0) and dark (<0) pixels
    
    sortAdj(img); // sort vv-matrix to VV-matrix

}


int check(void) {
    if (frm->index == 1) counter++;
    printf("%i/frame %i ################################################\n", counter, frm->index);
    
    cluster(frm);
    buildWeights(frm);
    printImage(frm);
    
    if(frm->index == 150) {
	freeBuffer(frm);
	exit(0);
    }
    
    return 0;
}

