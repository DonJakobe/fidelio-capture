
#include <string.h>

static int sub[length];
static int bright[length];
static int dark[length];

const int limit = 80;
const int dist = 3;

#include "array.h"

void substract(void) {
    int i;
    
    for (i=0; i<length; i++){
	sub[i] = (frms->data[i]) - (frms->prev->data[i]);
    }
}

void identifyPix(int *v, int *u) {
    int i;

    for (i=0; i<length; i++) {
	if (sub[i] > limit) {
	  bright[*v] = i;
	  *v = *v + 1;
	}
	else if (sub[i] < -limit) {
	    dark[*u] = i;
	    *u = *u + 1;
	}
    }
}

void buildAdj(int v, int u, int **vu) {
    int i, j;
    for (i=0; i<v; i++) {
	for (j=0; j<u; j++) {
	    if ( ((getX(bright[i])-getX(dark[j]))*(getX(bright[i])-getX(dark[j])) +
		    (getY(bright[i])-getY(dark[j]))*(getY(bright[i])-getY(dark[j])))
		    < dist*dist ) {
		vu[i][j] = 1;
	    } else {
		vu[i][j] = 0;
	    }
	}
    }
}

void buildAdj2(int v, int u, int **vu, int **vv) {
    int i, j, k;
    for (i=0; i<v; i++) {
	for (j=0; j<u; j++) {
	    if (vu[i][j] == 1) {
		vv[i][i] = 1;
		for (k=0; k<v; k++) {
		    if (vu[k][j] == 1) {
			vv[i][k] = 1;
		    }
		}
	    }
	}
    }
}

void list(void) {
    int i, j, k;
    int v=0;
    int u=0;
    int n=0;
    int m=-1;
    int p;
    int **vu;
    int **vv;
    int **VV;
    int **metlist; // table with the indices of all pixels belonging to one meteor
    int *npix; // total number of pixels belonging to that meteor
    int nmet;

    free2dArray(frms->metlist, v);
    free(frms->npix);

    identifyPix(&v, &u); // build lists of bright (>0) and dark (<0) pixels

    // dynamically reserve memory for matrices
    vu = (int **) malloc(v*sizeof(int *));
    vv = (int **) malloc(v*sizeof(int *));
    VV = (int **) malloc(v*sizeof(int *));
    frms->metlist = (int **) malloc(v*sizeof(int *));

    for (i=0; i<v; i++) {
	vu[i] = (int *) malloc(u*sizeof(int));
	vv[i] = (int *) malloc(v*sizeof(int));
	VV[i] = (int *) malloc(v*sizeof(int));
	frms->metlist[i] = (int *) malloc(v*sizeof(int));
	memset(frms->metlist[i], 0, sizeof(frms->metlist[i]));
    }
    
    frms->npix = (int *) malloc(v*sizeof(int));
    memset(frms->npix, 0, v*sizeof(int));


    buildAdj(v, u, vu); // build adjacency matrix between bright (>0) and dark (<0) pixels

    printf("vu\n");
    printArray(vu, v, u);

    // initialize adjacency matrix between bright pixels connected by one dark pixel (vv-matrix)
    for (i=0; i<v; i++) {
	for (j=0; j<v; j++) {
	    vv[i][j] = 0;
	}
    }

    buildAdj2(v, u, vu, vv); // build vv-matrix

    printf("vv\n");
    printArray(vv, v, v);

    // sort vv-matrix to VV-matrix
    cpy2dArray(vv, VV, v);

    for (i=0; i<v; i++) {
	if (n == i) {
	    n++;
	    m++;
	    p=0;
	    frms->metlist[m][p] = bright[i];
	    frms->npix[m]++;
	}

	for (j=n; j<v; j++) {
	    for (k=0; k<v; k++) {
		if ( (VV[i][k] == 1) & (VV[j][k] == 1) ) {
		    printf("i/j/n: %i/%i/%i\n", i, j, n);
		    switchRows(VV, j, n, v);
		    n++;
		    p++;
		    frms->metlist[m][p] = bright[j];
		    frms->npix[m]++;
		    break;
		}
	    }
	}
    }  

    frms->nmet = m + 1;

    printf("METLIST:\n");
    printArray(frms->metlist, v, v);
    printf("NPIX:\n");
    for (i=0; i<v; i++) {
	printf("%i ", frms->npix[i]);
    }
    printf("\nNMET: %i\n", frms->nmet);

    printf("VV\n");
    printArray(VV, v, v);

    free2dArray(vu, v);
    free2dArray(vv, v);
    free2dArray(VV, v);
}



int check(void) {
	printf("frame %i\n", frms->index);
	
	substract();
	list();

	return 0;
}



