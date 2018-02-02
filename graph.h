
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
	    ab = rmCol(ab, i, *a, b);
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
	    ab = rmRow(ab, i, a);
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

	    frms->lightPix = expandList(frms->lightPix, light[r], num+1);
	    frms->shadowPix = expandList(frms->shadowPix, shadow[c], num+1);

	    frms->numlight = addToList(frms->numlight, 1, num+1);
	    //addToList(&(frms->numlight), 1, num+1);
	    frms->numshadow = addToList(frms->numshadow, 1, num+1);
	    //addToList(&(frms->numshadow), 1, num+1);
	    num++;
	} else if (nr > r) {
	    for (i=nr; i<rows; i++) {	
		for (j=0; j<cols; j++) {
		    if ((ab[r][j] == 1) & (ab[i][j] == 1) ) {
			switchRows(ab, nr, i, cols);
			nr++; pr++;
			frms->lightPix[num] = addToList(frms->lightPix[num], light[i], pr+1);
			//addToList(&(frms->lightPix[num]), light[i], pr+1);
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
			switchCols(ab, nc, i, rows);
			nc++; pc++;
			frms->shadowPix[num] = addToList(frms->shadowPix[num], shadow[i], pc+1);
			//addToList(&(frms->shadowPix[num]), shadow[i], pc+1);
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

