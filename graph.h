
void buildAdj(int *a, int *b, int d, int **ab) {
    int i=0, j;
    int zero = 1;

    if ( (light == NULL) | (shadow == NULL)) return;
    
    do {
	zero = 1;
	for (j=0; j<*a; j++) {
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
	    *b = *b - 1;
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

// r is the current row of the asymmetric (r x c)-matrix ab. c is the current column. 
// in one loop cycle of r all other rows >n get checked for adjacency
// in one loop cycle of c all other columns >n get checked for adjacency
void sortAdj(int **ab, int rows, int cols, int num) {
    int i, j;
    int r=0, c=0;
    num=0;
    int pr=0, pc=0;
    int nr=0, nc=0;


    num=-1;

    while (1) {
	//printf("r%i, nr%i, c%i, nc%i\n", r, nr, c, nc);
	if (nr == r & nc == c) {
	    nr++; nc++;
	    pr=0; pc=0;

	    //printf("plightPix:%p, pshadowPix:%p, r%i, c%i\n", frms->lightPix, frms->shadowPix, r, c);
	    frms->lightPix = expandList(frms->lightPix, light[r], num+1);
	    frms->shadowPix = expandList(frms->shadowPix, shadow[c], num+1);

	    //printf("plightPix:%p, pshadowPix:%p, r%i, c%i\n", frms->lightPix, frms->shadowPix, r, c);
			printf("prePOINTER: %p\n", frms->numlight);
	    frms->numlight = addToList(frms->numlight, 1, num+1);
			printf("postPOINTER: %p\n", frms->numlight);
	    //print1dArray(frms->numlight, num+2);
	    frms->numshadow = addToList(frms->numshadow, 1, num+1);
	    //print1dArray(frms->numshadow, num+2);
	    num++;
	} else if (nr > r) {
	    for (i=nr; i<rows; i++) {	
		for (j=0; j<cols; j++) {
		    if ((ab[r][j] == 1) & (ab[i][j] == 1) ) {
			//printf("r%i, nr%i, i%i\n", r, nr, i);
			switchRows(ab, nr, i, cols);
			nr++; pr++;
			frms->lightPix[num] = addToList(frms->lightPix[num], light[i], pr+1);
			frms->numlight[num]++;
			break;
		    }
		}
	    }
	    r++;
	} else if (nc > c) {
	    for (i=nc; i<cols; i++) {	
		for (j=0; j<rows; j++) {
		    if ((ab[j][c] == 1) & (ab[j][i] == 1) ) {
			//printf("c%i, nc%i, i%i\n", c, nc, i);
			switchCols(ab, nc, i, rows);
			nc++; pc++;
			frms->shadowPix[num] = addToList(frms->shadowPix[num], shadow[i], pc+1);
			frms->numshadow[num]++;
			break;
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
    frms->num = num;
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
