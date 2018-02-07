
int **buildAdj(int *a, int *b, int d, int **ab) {
    int i=0, j;
    int zero = 1;

    if ( (lght == NULL) | (shdw == NULL) ) {
	free2dArray(ab, *a);
	ab = NULL;
	return ab;
    }

    do {
	zero = 1;
	for (j=0; j<*a; j++) {
	    if ( squareDist(shdw[i], lght[j]) < d*d ) {
		ab[j][i] = 1;
		zero = 0;
	    } else {
		ab[j][i] = 0;
	    }
	}
	if (zero == 1) {
	    shdw = rmFromList(shdw, i, *b);
	    ab = rmCol(ab, i, *a, b);
	} else {
	    i++;
	}
    } while (i < *b);

    if (shdw == NULL) {
	free2dArray(ab, *a);
	ab = NULL;
	return ab;
    }

    i = 0;
    do {
	zero = 1;
	for (j=0; j<*b; j++) {
	    if (ab[i][j] == 1) {
		zero = 0;
	    }
	}
	if (zero == 1) {
	    lght = rmFromList(lght, i, *a);
	    ab = rmRow(ab, i, a);
	} else {
	    i++;
	}
    } while (i < *a);    

    if (lght == NULL) {
	free2dArray(ab, *a);
	ab = NULL;
	return ab;
    }

    return ab;
}

// r is the current row of the asymmetric (r x c)-matrix ab. c is the current column. 
// in one loop cycle of r all other rows >nr get checked for adjacency
// in one loop cycle of c all other columns >nc get checked for adjacency
int **sortAdj(int **ab, int rows, int cols, struct image *img) {
    int i, j;
    int r=0, c=0;
    int pr=0, pc=0;
    int nr=0, nc=0;
    int num=-1;

    do {
	if (nr == r & nc == c) {
	    nr++; nc++;
	    pr=0; pc=0;

	    img->lghtPix = expandRaggedArray(img->lghtPix, lght[r], num+1);
	    img->shdwPix = expandRaggedArray(img->shdwPix, shdw[c], num+1);

	    img->numLght = addToList(img->numLght, 1, num+1);
	    img->numShdw = addToList(img->numShdw, 1, num+1);
	    num++;
	} else if (nr > r) {
	    for (i=nr; i<rows; i++) {	
		for (j=0; j<cols; j++) {
		    if ((ab[r][j] == 1) & (ab[i][j] == 1) ) {
			switchRows(ab, nr, i, cols);
			switchEle(lght, nr, i);
			nr++; pr++;
			img->lghtPix[num] = addToList(img->lghtPix[num], lght[i], pr);
			img->numLght[num]++;
			break;
		    }
		}
	    }
	    r++;
	} else if (nc > c) {
	    for (i=nc; i<cols; i++) {	
		for (j=0; j<rows; j++) {
		    if ((ab[j][c] == 1) & (ab[j][i] == 1) ) {
			switchCols(ab, nc, i, rows);
			switchEle(shdw, nc, i);
			nc++; pc++;
			img->shdwPix[num] = addToList(img->shdwPix[num], shdw[i], pc);
			img->numShdw[num]++;
			break;
		    }
		}
	    }
	    c++;
	} 

    } while ( (nr < rows) | (nc < cols) );
    num++;
    img->num = num;
    return ab;
}    

