
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
    int num=-1;

    do {
	if (nr == r & nc == c) {
	    nr++; nc++;
	    num++;
	    pr=0; pc=0;

	    img->met = realloc(img->met, (num+1) * sizeof(struct cluster *));
	    img->met[num] = malloc(sizeof(struct cluster));
	    img->met[num]->lght = NULL;
	    img->met[num]->shdw = NULL;

	    img->met[num]->lght = addToList(img->met[num]->lght, img->lght[r], 0);
	    img->met[num]->shdw = addToList(img->met[num]->shdw, img->shdw[c], 0);
	    img->met[num]->Nlght = 1;
	    img->met[num]->Nshdw = 1;

	} else if (nr > r) {
	    for (i=nr; i<rows; i++) {	
		for (j=0; j<cols; j++) {
		    if ((img->adj[r][j] == 1) & (img->adj[i][j] == 1) ) {
			switchRows(img->adj, nr, i, cols);
			switchEle(img->lght, nr, i);
			nr++; pr++;
			img->met[num]->lght = addToList(img->met[num]->lght, img->lght[i], pr);
			img->met[num]->Nlght++;
			break;
		    }
		}
	    }
	    r++;
	} else if (nc > c) {
	    for (i=nc; i<cols; i++) {	
		for (j=0; j<rows; j++) {
		    if ((img->adj[j][c] == 1) & (img->adj[j][i] == 1) ) {
			switchCols(img->adj, nc, i, rows);
			switchEle(img->shdw, nc, i);
			nc++; pc++;
			img->met[num]->shdw = addToList(img->met[num]->shdw, img->shdw[i], pc);
			img->met[num]->Nshdw++;
			break;
		    }
		}
	    }
	    c++;
	} 

    } while ( (nr < rows) | (nc < cols) );
    num++;
    img->num = num;
}    

