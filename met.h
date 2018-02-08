
struct image {
    int index;
    char *data;
    int Nlght;
    int Nshdw;
    int *lght;
    int *shdw;
    int **adj;
    int num;
    struct cluster **met;
    struct image *prev;
    struct image *next;
};

struct cluster {
    int index;
    int Nlght;
    int Nshdw;
    int *lght;
    int *shdw;
    int **weights;
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

void initFrame(struct image *img) {
    int i;

    free(img->lght);
    img->lght = NULL;
    free(img->shdw);
    img->shdw = NULL;

    for (i=0; i<(img->num); i++) {
	free(img->met[i]->lght);
	free(img->met[i]->shdw);
	img->met[i]->weights = free2dArray(img->met[i]->weights, img->met[i]->Nlght + img->met[i]->Nshdw);
    }

    free(img->met);
    img->met = NULL;

    img->Nlght = 0;
    img->Nshdw = 0;
    img->num = 0;
}

void printImage(struct image *img) {
    int i;
    printf("\n");
    print2dArray(img->adj, img->Nlght, img->Nshdw);
    printf("\n");

    for (i=0; i<(img->num); i++) {
	printf("meteor =%i=\n", i);
	printf("LIGHT: ");
	print1dArray(img->met[i]->lght, img->met[i]->Nlght);
	printf("SHADOW: ");
	print1dArray(img->met[i]->shdw, img->met[i]->Nshdw);
	printf("\n");
	print2dArray(img->met[i]->weights, img->met[i]->Nlght + img->met[i]->Nshdw, img->met[i]->Nlght + img->met[i]->Nshdw);
	printf("\n");
    }
}
	
