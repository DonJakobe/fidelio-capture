
struct image{
	int index;
        char *data;
	int **metlist;
	int *npix;
	int nmet;
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
		img->metlist = NULL;
		img->npix = NULL;
		img->nmet = 0;
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

int getX(int index) {
    return index % width;
}

int getY(int index) {
    return index / height;
}
