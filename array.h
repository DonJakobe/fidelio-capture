
int *addToList(int *list, int item, int cols) {
    //printf("aTL-pre: p:%p, i:%i, c:%i\n", list, item, cols);
    list = (int *) realloc(list, (cols+1)*sizeof(int));
    //printf("aTL-post: p:%p, i:%i, c:%i\n", list, item, cols+1);
    list[cols] = item;
    return list;
}

int *initList(int *list) {
    free(list);
    list = NULL;
}

int *rmFromList(int *list, int item, int cols) {
    int i=0, k=0;
    do{
	if (i == item) {
	    k++;
	}
	list[i] = list[k];
	i++;
	k++;
    } while (k < cols);
    list = (int *) realloc(list, (cols-1)*sizeof(int));
    return list;
}

void expandList(int **list, int firstItem, int rows) {
    list[rows] = (int *) malloc(sizeof(int));
    list[rows][0] = firstItem;
}


void free2dArray(int **a, int rows) {
    int i;

    for (i=0; i<rows; i++) {
	free(a[i]);
    }

    free(a);
}

void cpy2dArray(int **a, int **b, int dim) {
    int i, j;
    
    for (i=0; i<dim; i++) {
	for (j=0; j<dim; j++) {
	    b[i][j] = a[i][j];
	}
    }
}

void switchSymmRows(int **a, int a1, int a2, int dim) {
    int i;
    int *tmp = (int *) malloc(dim*sizeof(int));
    int m = a[a2][a2];

    for (i=0; i<dim; i++) {
	tmp[i] = a[a1][i];
	a[a1][i] = a[a2][i];
	a[i][a1] = a[a2][i];
	a[a2][i] = tmp[i];
	a[i][a2] = tmp[i];
    }    
    
    a[a1][a1] = m;
    a[a2][a2] = tmp[a1];
    a[a1][a2] = tmp[a2];
    a[a2][a1] = tmp[a2];

    free(tmp);
}

void switchRows(int **a, int a1, int a2, int cols) {
    int i;
    int tmp;
    
    for (i=0; i<cols; i++) {
	tmp = a[a1][i];
	a[a1][i] = a[a2][i];
	a[a2][i] = tmp;
    }
}

void rmRow(int **a, int a0, int *rows) {
    int i=0, k=0;
    free(a[a0]);
    do{
	if (i == a0) {
	    k++;
	}
	a[i] = a[k];
	i++;
	k++;
    } while (k < *rows);
    *rows = *rows - 1;
    printf("i%i, k%i, pfree%p\n", i, k, a[i]);
}

void rmCol(int **arr, int b0, int rows, int cols) {
    int i;
    for (i=0; i<rows; i++) {
	arr[i] = rmFromList(arr[i], b0, cols);
    }
}

/*
void rmRow(int **a, int *rows, int cols) {
    int i=0, j, k, l;
    int zero;

    if ( (*rows == 0) | (cols == 0) ) {
	return;
    }

    do {
	zero = 1;
	for (j=0; j<cols; j++) {
	    if (a[i][j] == 1) {
		zero = 0;
	    }
	}
	if (zero == 1) {
	    for (l=0; l<cols; l++) {
		if (i == (*rows-1)) {
		    a[i] = NULL;
		} else {
		    for (k=i; k<(*rows-1); k++) {
			a[k][l] = a[k+1][l];
		    }
		}
	    }
	    *rows = *rows - 1;
	} else {
	    i++;
	}
    } while (i<*rows);
}
*/
	    

void switchCols(int **a, int a1, int a2, int rows) {
    int i;
    int tmp;
    
    for (i=0; i<rows; i++) {
	tmp = a[i][a1];
	a[i][a1] = a[i][a2];
	a[i][a2] = tmp;
    }
}

void cpyRow(int **a, int **b, int a1, int b1, int dim) {
    int i;

    for (i=0; i<dim; i++) {
	b[b1][i] = a[a1][i];
	b[i][b1] = a[i][a1];
    }
}

void zeroRow(int **a, int a1, int dim) {
    int i;

    for (i=0; i<dim; i++) {
	a[a1][i] = 0;
	a[i][a1] = 0;
    }
}

void print2dArray(int **a, int rows, int cols) {
    int i, j;

    printf("\n");

    for (i=0; i<rows; i++) {
	for (j=0; j<cols; j++) {
	    printf("%i ", a[i][j]);
	}
	printf("\n");
    }
}

void print1dArray(int *a, int dim) {
    int i;

    printf("\n");

    for (i=0; i<dim; i++) {
	printf("%i ", a[i]);
    }
    printf("\n");
}
