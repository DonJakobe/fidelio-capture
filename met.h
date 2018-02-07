
struct image{
	int index;
        char *data;
	int **lghtPix;
	int **shdwPix;
	int *numLght;
	int *numShdw;
	int num;
        struct image *prev;
        struct image *next;
};

struct image *buildBuffer(int size){

	int i;

	struct image *start = malloc(sizeof(struct image));
	struct image *tmp = NULL;
	
	struct image *img = start;

	for (i = 1; i <= size; i++) {

		img->prev = tmp;
		img->index = i;
		img->lghtPix = NULL;
		img->shdwPix = NULL;
		img->numLght = NULL;
		img->numShdw = NULL;
		img->num = 0;
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

	for (i=0; i<(img->num); i++) {
	    free(img->lghtPix[i]);
	    free(img->shdwPix[i]);
	}

	free(img->lghtPix);
	free(img->shdwPix);
	free(img->numLght);
	free(img->numShdw);
	tmp = img->next;
	free(img);
	//printf("free img %p\n", tmp);
	img = tmp;

    } while (img != NULL);
}

void initFrame(struct image *img) {
    int i;

    for (i=0; i<(img->num); i++) {
	free(img->lghtPix[i]);
	free(img->shdwPix[i]);
	img->lghtPix[i] = NULL;
	img->shdwPix[i] = NULL;
    }
    
    if (img->num != 0) {
	free(img->lghtPix);
	free(img->shdwPix);
	free(img->numLght);
	free(img->numShdw);
    }

    img->shdwPix = NULL;
    img->lghtPix = NULL;
    img->numLght = NULL;
    img->numShdw = NULL;

    img->num = 0;
}

