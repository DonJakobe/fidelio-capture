
int buildAdj(struct image *img, int dist) {
    int i, j;
    int zero = 1;

    if ( (img->lght == NULL) | (img->shdw == NULL) ) {
	return 1;
    }

    img->adj = alloc2dArray(img->adj, img->Nlght, img->Nshdw);

    i = 0;

    do {
	zero = 1;
	for (j=0; j<(img->Nlght); j++) {
	    if ( squareDist(img->shdw[i], img->lght[j]) < dist*dist ) {
		img->adj[j][i] = 1;
		zero = 0;
	    } else {
		img->adj[j][i] = 0;
	    }
	}
	if (zero == 1) {
	    img->shdw = rmFromList(img->shdw, i, img->Nshdw);
	    img->adj = rmCol(img->adj, i, img->Nlght, &(img->Nshdw));
	} else {
	    i++;
	}
    } while (i < img->Nshdw);

    if (img->shdw == NULL) {
	return 1;
    }

    i = 0;
    do {
	zero = 1;
	for (j=0; j<(img->Nshdw); j++) {
	    if (img->adj[i][j] == 1) {
		zero = 0;
	    }
	}
	if (zero == 1) {
	    img->lght = rmFromList(img->lght, i, img->Nlght);
	    img->adj = rmRow(img->adj, i, &(img->Nlght));
	} else {
	    i++;
	}
    } while (i < img->Nlght);    
    
    if (img->lght == NULL) {
	return 1;
    }
}

// r is the current row of the asymmetric (r x c)-matrix ab. c is the current column. 
// in one loop cycle of r all other rows >nr get checked for adjacency
// in one loop cycle of c all other columns >nc get checked for adjacency
void generateGraphs(struct image *img) {
    int i, j;
    int r=0, c=0;
    int pr=0, pc=0;
    int nr=0, nc=0;
    int rows = img->Nlght, cols = img->Nshdw;

    img->num = -1;

    do {
	if (nr == r && nc == c) {
	    nr++; nc++;
	    img->num++;
	    pr=0; pc=0;

	    addNewGraph(img);
	    img->met[img->num]->lght[0] = img->lght[r];
	    img->met[img->num]->shdw[0] = img->shdw[c];

	} else if (nr > r) {
	    for (i=nr; i<rows; i++) {	
		for (j=0; j<cols; j++) {
		    if ((img->adj[r][j] == 1) && (img->adj[i][j] == 1) ) {
			switchRows(img->adj, nr, i, cols);
			switchEle(img->lght, nr, i);
			nr++; pr++;
			img->met[img->num]->lght = addToList(img->met[img->num]->lght, img->lght[i], pr);
			img->met[img->num]->Nlght++;
			break;
		    }
		}
	    }
	    r++;
	} else if (nc > c) {
	    for (i=nc; i<cols; i++) {	
		for (j=0; j<rows; j++) {
		    if ((img->adj[j][c] == 1) && (img->adj[j][i] == 1) ) {
			switchCols(img->adj, nc, i, rows);
			switchEle(img->shdw, nc, i);
			nc++; pc++;
			img->met[img->num]->shdw = addToList(img->met[img->num]->shdw, img->shdw[i], pc);
			img->met[img->num]->Nshdw++;
			break;
		    }
		}
	    }
	    c++;
	} 

    } while ( (nr < rows) | (nc < cols) );
    img->num++;

    for (i=0; i<(img->num); i++) {
	img->met[i]->Nvtc = img->met[i]->Nlght + img->met[i]->Nshdw;
	img->met[i]->vtc = cat1dArrays(img->met[i]->lght, img->met[i]->shdw, img->met[i]->Nlght, img->met[i]->Nshdw);
    }
}    

void buildWeights(struct graph *met, int upper) {
    int i, j;

    met->weights = alloc2dArray(met->weights, met->Nvtc, met->Nvtc);

    for (i=0; i<(met->Nvtc); i++) {
	for (j=0; j<(i+1); j++) {
	    if ( (i != j) && ( (met->weights[i][j] = 100 - (100*squareDist(met->vtc[i], met->vtc[j])) / (upper*upper)) > 0 ) ) {
		met->weights[j][i] = met->weights[i][j];
	    } else {
		met->weights[i][j] = 0;
		met->weights[j][i] = 0;
	    }
	}
    }
}

void degrees(struct graph *met) {
    int i;
    met->deg = malloc(met->Nvtc * sizeof(int));
    
    for (i=0; i<(met->Nvtc); i++) {
	met->deg[i] = sum1dArray(met->weights[i], met->Nvtc);
    }
}

void meanDegree(struct graph *met) {
   met->mDegree = sum1dArray(met->deg, met->Nvtc) / met->Nvtc;
}

void meanWeight(struct graph *met) {
    int i, j;
    int sum=0;

    int N = met->Nvtc;

    for (i=1; i<N; i++) {
	for (j=0; j<i; j++) {
	    sum += met->weights[i][j];
	}
    }
    met->mWeight = sum / (N*N - N) * 2;
}

void density(struct graph *met) {
    int i=0, j;
    int *order = malloc(met->Nvtc * sizeof(int));
    order = getOrder(order, met->deg, met->Nvtc);
    met->dens = 0;

    //print1dArray(order, met->Nvtc);

    while ( (i < (met->Nvtc)) && (met->deg[order[i]] > met->mDegree) ) {
	j = 0;
	while ( (j < (met->Nvtc)) && (met->deg[order[j]] > met->mDegree) ) {
	    met->dens += met->weights[order[i]][order[j]];
	    j++;
	}
	i++;

	//printf("vtx %i: (%i|%i) | index %i | degree = %i | weight = %i \n", i, getX(met->vtc[order[i]]), getY(met->vtc[order[i]]), met->vtc[order[i]], met->deg[order[i]], met->weights[order[i]][order[i+1]]);
    }

    met->dens = (float) met->dens / (float) (i*i);

    free(order);
}

void getVertexPositions(struct graph *met) {
    int i;
    met->x = malloc(met->Nvtc * sizeof(int));
    met->y = malloc(met->Nvtc * sizeof(int));
    for (i=0; i<(met->Nvtc); i++) {
	met->x[i] = getX(met->vtc[i]);
	met->y[i] = getY(met->vtc[i]);
    }
}

int degreeOfDisconnectivity(struct graph *met, int **weights) {
    int i, j, k;
    int con;
    int dcon=0;

    for (i=0; i<(met->Nvtc); i++) {
	con = 0;
	for (j=0; j<(met->Nvtc); j++) {
	    for (k=0; k<(met->Nvtc); k++) {
		if ( (i != j) && (weights[i][k] > 0) && (weights[j][k] > 0) ) {
		    con = 1;
		    break;
		}
	    }
	    if (con = 1) break;
	}
	if (con = 0) dcon++;
    }
    return dcon;
}

void connectivity(struct graph *met) {
    int **weights = alloc2dArray(weights, met->Nvtc, met->Nvtc);
    weights = cpy2dArray(met->weights, weights, met->Nvtc, met->Nvtc);

    free2dArray(weights, met->Nvtc);
}
