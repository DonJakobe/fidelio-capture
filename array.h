/*
void addToList(int **list, int item, int size) {
    *list = realloc(*list, (size+1)*sizeof(int));
    (*list)[size] = item;
}
*/

int *addToList(int *list, int item, int size) {
    list = realloc(list, (size+1)*sizeof(int));
    list[size] = item;
    return list;
}


int *initList(int *list) {
    free(list);
    list = NULL;
    return list;
}

// remove the i-th item from one-dimensional array (i = 0, 1, 2, ...)
int *rmFromList(int *list, int item, int cols) {
    int i=0, k=0;
    if (item < (cols-1)) { //exception when removing the last element
	do{
	    if (i == item) {
		k++;
	    }
	    list[i] = list[k];
	    i++;
	    k++;
	} while (k < cols);
    }
    list = realloc(list, (cols-1)*sizeof(int));
    return list;
}

int **expandList(int **list, int firstItem, int rows) {
    list = realloc(list, (rows+1)*sizeof(int *));
    list[rows] = malloc(sizeof(int));
    list[rows][0] = firstItem;
    return list;
}

int **alloc2dArray(int **arr, int rows, int cols) {
    int i;
    arr = malloc(rows*sizeof(int *));
    for (i=0; i<rows; i++) {
	arr[i] = malloc(cols*sizeof(int));
    }
    return arr;
}

int **free2dArray(int **a, int rows) {
    int i;

    for (i=0; i<rows; i++) {
	free(a[i]);
	a[i] = NULL;
    }

    free(a);
    a = NULL;
    return a;
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
    int *tmp = malloc(dim*sizeof(int));
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
    tmp = NULL;
}

void switchRows(int **a, int a1, int a2, int cols) {
    int i;
    int tmp;
    
    //printf("a1%i, a2%i, cols%i\n", a1, a2, cols);
    for (i=0; i<cols; i++) {
	//printf("a[a1][%i]: %p a[a2][%i]: %p\n", i, &a[a1][i], i, &a[a2][i]);
	tmp = a[a1][i];
	a[a1][i] = a[a2][i];
	a[a2][i] = tmp;
    }
    //printf("\n");
}

int **rmRow(int **a, int a0, int *rows) {
    int i=0, k=0;
    int *tmp = a[a0];
    if (a0 < (*rows-1)) {
	do{
	    if (i == a0) {
		k++;
	    }
	    a[i] = a[k];
	    i++;
	    k++;
	} while (k < *rows);
    }
    free(tmp);
    a = realloc(a, (*rows-1)*sizeof(int *));
    *rows = *rows - 1;
    return a;
}

int **rmCol(int **arr, int b0, int rows, int *cols) {
    int i;
    for (i=0; i<rows; i++) {
	arr[i] = rmFromList(arr[i], b0, *cols);
    }
    *cols = *cols - 1;
    return arr;
}

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

void printAdd2dArray(int **arr, int rows, int cols) {
    int i, j;

    printf("\n");

    for (i=0; i<rows; i++) {
	printf("%p : ", arr[i]);
	for (j=0; j<cols; j++) {
	    printf("%p ", &arr[i][j]);
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
