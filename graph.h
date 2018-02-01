
void buildAdj(int *a, int *b, int d, int **ab) {
    int i=0, j;
    int zero = 1;
    
    do {
	zero = 1;
	for (j=0; j<*a; j++) {
	    //printf("i%i\n", i);
	    if ( ((getX(shadow[i])-getX(light[j]))*(getX(shadow[i])-getX(light[j])) +
		  (getY(shadow[i])-getY(light[j]))*(getY(shadow[i])-getY(light[j]))) < d*d ) {
		ab[j][i] = 1;
		zero = 0;
	    } else {
		ab[j][i] = 0;
	    }
	}
	if (zero == 1) {
	    shadow = rmFromList(shadow, i, *b);
	    rmCol(ab, i, *a, *b);
	    //printf("b%i\n", *b);
	    *b = *b - 1;
	    //printf("p%p\n", shadow);
	    //print1dArray(shadow, *b);
	} else {
	    i++;
	}
    } while (i < *b);

    if (shadow == NULL) return;

    i = 0;
    do {
	zero = 1;
	for (j=0; j<*b; j++) {
	    if (ab[i][j] == 1) {
		zero = 0;
	    }
	}
	if (zero == 1) {
	    light = rmFromList(light, i, *a);
	    rmRow(ab, i, a);
	} else {
	    i++;
	}
    } while (i < *a);	
}

void buildAdjOLD(int a, int b, int d, int *pixA, int *pixB, int **ab) {
    int i, j;
    for (i=0; i<a; i++) {
	for (j=0; j<b; j++) {
	    if ( ((getX(pixA[i])-getX(pixB[j]))*(getX(pixA[i])-getX(pixB[j])) +
		  (getY(pixA[i])-getY(pixB[j]))*(getY(pixA[i])-getY(pixB[j]))) < d*d ) {
		ab[i][j] = 1;
	    } else {
		ab[i][j] = 0;
	    }
	}
    }
}

void buildAdj2(int a, int b, int **ab, int **aa) {
    int i, j, k;
    for (i=0; i<a; i++) {
	for (j=0; j<a; j++) {
	    if (ab[i][j] == 1) {
		aa[i][i] = 1;
		for (k=0; k<a; k++) {
		    if (ab[k][j] == 1) {
			aa[i][k] = 1;
		    }
		}
	    }
	}
    }
}

// r is the current row of the asymmetric (r x c)-matrix ab. c is the current column. 
// in one loop cycle of r all other rows >n get checked for adjacency
// in one loop cycle of c all other columns >n get checked for adjacency
void sortAdj(int **ab, int rows, int cols, int num) {
    int i, j;
    int r=0, c=0;
    num=0;
    int pr=0, pc=0;
    int nr=0, nc=0;

    printf("BOOO");

    if ( (rows == 0) | (cols == 0) ) {
	frms->lightPix = NULL;
	frms->shadowPix = NULL;
	frms->numlight = NULL;
	frms->numshadow = NULL;
	frms->num = 0;
	return;
    }

    frms->lightPix = (int **) malloc(sizeof(int *));
    frms->lightPix[0] = (int *) malloc(sizeof(int));
    frms->shadowPix = (int **) malloc(sizeof(int *));
    frms->shadowPix[0] = (int *) malloc(sizeof(int));
    frms->numlight = (int *) calloc(1, sizeof(int));
    frms->numshadow = (int *) calloc(1, sizeof(int));
    //frms->lightPix[0][0] = light[r];
    //frms->shadowPix[0][0] = shadow[c];
    //frms->numlight[num] = 1;
    //frms->numshadow[num] = 1;

    num=-1;

    while (1) {
	if (nr == r & nc == c) {
	    nr++; nc++;
	    pr=0; pc=0;
	    expandList(frms->lightPix, light[r], num+1);
	    expandList(frms->shadowPix, shadow[c], num+1);
	    addToList(frms->numlight, 1, num+1);
	    print1dArray(frms->numlight, num+1);
	    addToList(frms->numshadow, 1, num+1);
	    print1dArray(frms->numshadow, num+1);
	    num++;
	} else if (nr > r) {
	    for (i=nr; i<rows; i++) {	
		for (j=0; j<cols; j++) {
		    if ((ab[r][j] == 1) & (ab[i][j] == 1) ) {
			switchRows(ab, nr, i, cols);
			nr++; pr++;
			addToList(frms->lightPix[num], light[i], pr+1);
			frms->numlight[num]++;
		    }
		}
	    }
	    r++;
	} else if (nc > c) {
	    for (i=nc; i<cols; i++) {	
		for (j=0; j<rows; j++) {
		    if ((ab[j][c] == 1) & (ab[j][i] == 1) ) {
			switchCols(ab, nc, i, rows);
			nc++; pc++;
			addToList(frms->shadowPix[num], shadow[i], pc+1);
			frms->numshadow[num]++;
		    }
		}
	    }
	    c++;
	}

	if ( (nr == rows) & (nc == cols) ) {
	   break;
	}
    }
    num++;
}    

/*
void sortAdj2(int v, int **vv) {
    int i, j, k;
    int n=0, m=-1, p=0;

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
		if ( (vv[i][k] == 1) & (vv[j][k] == 1) ) {
		    printf("i/j/n: %i/%i/%i\n", i, j, n);
		    switchSymmRows(vv, j, n, v);
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
}
*/
