
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

		img->next = malloc(sizeof(struct image));
		img->prev = tmp;
		img->index = i;
		img->lightPix = NULL;
		img->shadowPix = NULL;
		img->numlight = NULL;
		img->numshadow = NULL;
		img->num = 0;
		img->data = malloc(length);

		tmp = img;

		if(i == size){
			img->next = start;
			start->prev = img;
			break;
		}
		img = img->next;
	}
	return start;
}

void initFrame(struct image *img) {
    int i;
    
    for (i=0; i<(img->num); i++) {
	free(img->lightPix[i]);
	free(img->shadowPix[i]);
    }
    
    free(img->lightPix);
    img->lightPix = NULL;
    free(img->shadowPix);
    img->shadowPix = NULL;

    free(img->numlight);
    img->numlight = NULL;
    free(img->numshadow);
    img->numshadow = NULL;
}

int getX(int index) {
    return index % width;
}

int getY(int index) {
    return index / height;
}


