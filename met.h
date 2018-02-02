
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

//not tested
void freeBuffer(struct image *img, int size) {
    int i;

    for (i=0; i<size; i++) {
	printf("next: %p, next->next->prev %p\n", img->next, img->next->next->prev);
	free(img->data);
	//free(img->prev->next);
	free(img->prev);
	img = img->next;
    }
}

void initFrame(struct image *img) {
    int i;

    for (i=0; i<(img->num); i++) {
	//printf("lpi:%p, spi:%p\n", img->lightPix[i], img->shadowPix[i]);
	free(img->lightPix[i]);
	free(img->shadowPix[i]);
	img->lightPix[i] = NULL;
	img->shadowPix[i] = NULL;
    }
    
    //printf("lp:%p, sp:%p\n", img->lightPix, img->shadowPix);
    free(img->lightPix);
    img->lightPix = NULL;
    free(img->shadowPix);
    img->shadowPix = NULL;

    printf("nl:%p, ns:%p\n", img->numlight, img->numshadow);
    free(img->numlight);
    img->numlight = NULL;
    free(img->numshadow);
    img->numshadow = NULL;

    img->num = 0;
}

int getX(int index) {
    return index % width;
}

int getY(int index) {
    return index / height;
}


