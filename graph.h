
void buildAdj(int a, int b, int d, int *pixA, int *pixB, int **ab) {
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

void sortAdj(int v, int **vv) {
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
		    switchRows(vv, j, n, v);
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

