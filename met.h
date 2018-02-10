
struct image {
    int index;
    char *data;
    int Nlght;
    int Nshdw;
    int *lght;
    int *shdw;
    int **adj;
    int num;
    struct graph **met;
    struct image *prev;
    struct image *next;
};

struct graph {
    float posX;
    float posY;
    int Nlght;
    int Nshdw;
    int Ntot;
    int *lght;
    int *shdw;
    int **weights;
    float dens;
    int continuity;
    struct graph *prev;
    struct graph *next;
};

struct image *buildBuffer(int size){

	int i;

	struct image *start = malloc(sizeof(struct image));
	struct image *tmp = NULL;
	
	struct image *img = start;

	for (i = 1; i <= size; i++) {

		img->prev = tmp;
		img->index = i;
		img->Nlght = 0;
		img->Nshdw = 0;
		img->lght = NULL;
		img->shdw = NULL;
		img->adj = NULL;
		img->num = 0;
		img->met = NULL;
		img->data = malloc(length);

		if(i == size){
			img->next = start;
			start->prev = img;
			tmp = NULL;
			break;
		}

		img->next = malloc(sizeof(struct image));
		tmp = img;
		img = img->next;
	}
	return start;
}

void freeBuffer(struct image *img) {

    int i;
    struct image *tmp = img;
    img->prev->next = NULL;

    do {
	free(img->data);
	free(img->lght);
	free(img->shdw);
	if (img->adj != NULL) img->adj = free2dArray(img->adj, img->Nlght);

	for (i=0; i<(img->num); i++) {
	    free(img->met[i]->lght);
	    free(img->met[i]->shdw);
	    img->met[i]->weights = free2dArray(img->met[i]->weights, img->met[i]->Nlght + img->met[i]->Nshdw);
	    free(img->met[i]);
	}

	free(img->met);

	tmp = img->next;
	free(img);
	img = tmp;

    } while (img != NULL);
}

void addNewGraph(struct image *img) {
    img->met = realloc(img->met, (img->num+1) * sizeof(struct graph *));
    img->met[img->num] = malloc(sizeof(struct graph));
    img->met[img->num]->lght = malloc(sizeof(int));
    img->met[img->num]->shdw = malloc(sizeof(int));
    img->met[img->num]->Nlght = 1;
    img->met[img->num]->Nshdw = 1;
    img->met[img->num]->prev = NULL;
    img->met[img->num]->next = NULL;
}
    

void initGraph(struct graph *met) {
    free(met->lght);
    free(met->shdw);
    met->weights = free2dArray(met->weights, met->Ntot);
}

void initFrame(struct image *img) {
    int i;

    free(img->lght);
    img->lght = NULL;
    free(img->shdw);
    img->shdw = NULL;

    for (i=0; i<(img->num); i++) {
	initGraph(img->met[i]);
    }

    free(img->met);
    img->met = NULL;

    img->Nlght = 0;
    img->Nshdw = 0;
    img->num = 0;
}

void assignContinuity(struct image *img, int dist, int depth) {
    int deg, i, j;
    struct image *ref;

    for (i=0; i<(img->num); i++) {
	img->met[i]->continuity = 0;
	ref = img->prev;
	for (deg=1; deg<(depth+1); deg++) {
	    for (j=0; j<(ref->num); j++) {
		if ( ((img->met[i]->posX - ref->met[j]->posX) * (img->met[i]->posX - ref->met[j]->posX) +
		      (img->met[i]->posY - ref->met[j]->posY) * (img->met[i]->posY - ref->met[j]->posY)) < (deg*deg * dist*dist) ) {
		    img->met[i]->prev = ref->met[j];
		    if (ref->met[j] == NULL) ref->met[j]->next = img->met[i];
		    img->met[i]->continuity = deg;
		    break;
		}
	    }
	    if (img->met[i]->continuity > 0) break;
	    else ref = ref->prev;
	}
    }
}

void traceMeteor(struct graph *met0) {
    struct graph *met;
    met = met0;

    while (met != NULL) {
	printf("%f \t", met->posX);
	printf("%f \t", met->posY);
	printf("%f \t", met->dens);
	printf("\n");
	met = met->prev;
    }
}
    

void printImage(struct image *img) {
    int i;
    printf("\n");
    print2dArray(img->adj, img->Nlght, img->Nshdw);
    printf("\n");

    for (i=0; i<(img->num); i++) {
	printf("meteor =%i= || postion: X = %f, Y = %f | density = %f | continuity = %i\n", i, img->met[i]->posX, img->met[i]->posY, img->met[i]->dens, img->met[i]->continuity);
	/*
	printf("LIGHT: ");
	print1dArray(img->met[i]->lght, img->met[i]->Nlght);
	printf("SHADOW: ");
	print1dArray(img->met[i]->shdw, img->met[i]->Nshdw);
	printf("\n");
	print2dArray(img->met[i]->weights, img->met[i]->Nlght + img->met[i]->Nshdw, img->met[i]->Nlght + img->met[i]->Nshdw);
	*/
	printf("\n");
    }
}
	
