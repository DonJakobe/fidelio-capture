
struct image{
	int index;
        char *data;
	int **lightPix;
	int **shadowPix;
	int *numlight;
	int *numshadow;
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
		img->lightPix = NULL;
		img->shadowPix = NULL;
		img->numlight = NULL;
		img->numshadow = NULL;
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
	    free(img->lightPix[i]);
	    free(img->shadowPix[i]);
	}

	free(img->lightPix);
	free(img->shadowPix);
	free(img->numlight);
	free(img->numshadow);
	tmp = img->next;
	free(img);
	//printf("free img %p\n", tmp);
	img = tmp;

    } while (img != NULL);
}

void initFrame(struct image *img) {
    int i;

    for (i=0; i<(img->num); i++) {
	free(img->lightPix[i]);
	free(img->shadowPix[i]);
	img->lightPix[i] = NULL;
	img->shadowPix[i] = NULL;
    }
    
    if (img->num != 0) {
	free(img->lightPix);
	free(img->shadowPix);
	free(img->numlight);
	free(img->numshadow);
    }

    img->shadowPix = NULL;
    img->lightPix = NULL;
    img->numlight = NULL;
    img->numshadow = NULL;

    img->num = 0;
}

int getX(int index) {
    return index % width;
}

int getY(int index) {
    return index / height;
}

