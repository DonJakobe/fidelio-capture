
#include <string.h>

int counter=0;

static int sub[length];
int *lght=NULL;
int *shdw=NULL;

const int limit = 30;
static int cutoff = 10;

int *initList(int *list);
int *addToList(int *list, int item, int size);
int *rmFromList(int *list, int item, int cols);
void switchEle(int *list, int item1, int item2);
//int *cat1dArrays();
//int sum1dArray();
int **alloc2dArray(int **arr, int rows, int cols);
int **free2dArray(int **arr, int rows);
int **alloc2dArray(int **arr, int rows, int cols);
int **free2dArray(int **arr, int rows);
int **rmRow(int **arr, int row0, int *rows);
int **rmCol(int **arr, int col0, int rows, int *cols);
void switchRows(int **arr, int row1, int row2, int cols);
void switchCols(int **arr, int col1, int col2, int rows);
int **expandRaggedArray(int **arr, int item0, int rows);
void print1dArray(int *list, int dim);
void print2dArray(int **arr, int rows, int cols);
void print2dRagged(int **arr, int rows, int *size);


#include "pixel.h"
#include "array.h"
#include "graph.h"


void cluster(void) {
    int i, j;
    int v, u;
    int **vu=NULL;

    initFrame(frm);
    lght = initList(lght);
    shdw = initList(shdw);

    identifyPix(limit, &v, &u, sub); // build lists of bright (>0) and dark (<0) pixels from sub

    vu = alloc2dArray(vu, v, u); // dynamically reserve memory for matrix
    vu = buildAdj(&v, &u, cutoff, vu); // build adjacency matrix between bright (>0) and dark (<0) pixels
    
    if (vu == NULL) {
	return;
    }

    vu = sortAdj(vu, v, u, frm); // sort vv-matrix to VV-matrix

    printf("\nV x U (sorted):\n");
    print2dArray(vu, v, u);

    printf("LIGHT ");
    print1dArray(frm->numLght, frm->num);
    print2dRagged(frm->lghtPix, frm->num, frm->numLght);

    printf("\n");

    printf("SHADOW ");
    print1dArray(frm->numShdw, frm->num);
    print2dRagged(frm->shdwPix, frm->num, frm->numShdw);

    vu = free2dArray(vu, v);
    vu = NULL;
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
	
	substractFrames(frm->data, frm->prev->data, sub);
	cluster();
	
	if(frm->index == 150) {
	    freeBuffer(frm);
	    if (lght != NULL) free(lght);
	    if (shdw != NULL) free(shdw);
	    exit(0);
	}

	return 0;
}

