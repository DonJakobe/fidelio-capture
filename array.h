
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

void switchRows(int **a, int a1, int a2, int dim) {
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
}
