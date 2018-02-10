
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
void sortAdj(struct image *img) {
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
}    

void buildWeights(struct graph *met) {
    int i, j;
    int N;
    int *vtc; //Pixel (lghtPix and shdwPix belonging to one meteor)

    vtc = cat1dArrays(met->lght, met->shdw, met->Nlght, met->Nshdw);
    met->weights = alloc2dArray(met->weights, met->Ntot, met->Ntot);

    for (i=0; i<(met->Ntot); i++) {
	for (j=0; j<(i+1); j++) {
	    if ( (i != j) && (squareDist(vtc[i], vtc[j]) < cutoff*cutoff) ) {
		met->weights[i][j] = 100 - (100*squareDist(vtc[i], vtc[j])) / (cutoff*cutoff);
		met->weights[j][i] = met->weights[i][j];
	    } else {
		met->weights[i][j] = 0;
		met->weights[j][i] = 0;
	    }
	}
    }
    free(vtc);
}

void density(struct graph *met) {
    int i, j;
    int sum=0;

    for (i=1; i<(met->Ntot); i++) {
	for (j=0; j<i; j++) {
	    sum += met->weights[i][j];
	}
    }
    met->dens = (float) sum / (float) (met->Ntot*met->Ntot - met->Ntot);
}

