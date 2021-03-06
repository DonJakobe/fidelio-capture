
struct image {
    int index;
    unsigned char *data;
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
    int Nlght;
    int Nshdw;
    int Nvtc;
    int *lght;
    int *shdw;
    int *vtc;
    int **weights;
    int *deg;
    int *x;
    int *y;
    float posX;
    float posY;
    float posVar;
    float vx;
    float vy;
    float R;
    float dens;
    int mWeight;
    int mDegree;
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
		img->data = calloc(LENGTH, sizeof(unsigned char));

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

void initGraph(struct graph *met) {
    free(met->lght);
    free(met->shdw);
    free(met->vtc);
    free(met->x);
    free(met->y);
    met->weights = free2dArray(met->weights, met->Nvtc);
    free(met->deg);
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
	    initGraph(img->met[i]);
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
    img->met[img->num]->Nvtc = 2;
    img->met[img->num]->vtc = NULL;
    img->met[img->num]->deg = NULL;
    img->met[img->num]->prev = NULL;
    img->met[img->num]->next = NULL;
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

void assignContinuity(struct image *img, struct graph *met, int dist, int depth) {
    int deg, j;

    met->continuity = 0;
    
    for (deg=1; deg<(depth+1); deg++) {
	img = img->prev;
	for (j=0; j<(img->num); j++) {
	    if ( ((met->posX - img->met[j]->posX) * (met->posX - img->met[j]->posX) +
		  (met->posY - img->met[j]->posY) * (met->posY - img->met[j]->posY)) < (deg*deg * dist*dist) ) {
		met->prev = img->met[j];
		if (img->met[j] == NULL) img->met[j]->next = met;
		met->continuity = deg;
		break;
	    }
	}
	if (met->continuity > 0) break;
    }
}

void getVelocity(struct graph *met0) {
    float vx, vy;
    float Rx, Ry;

    float tsum=0, t2sum=0;
    float xsum=0, x2sum=0;
    float ysum=0, y2sum=0;
    float xtsum=0, ytsum=0;

    int n=0, t=0;

    struct graph *met = met0;

    while (met->prev != NULL) {
	tsum += t;
	t2sum += t*t;

	xsum += met->posX;
	x2sum += met->posX * met->posX;

	ysum += met->posY;
	y2sum += met->posY * met->posY;

	xtsum += met->posX * t;
	ytsum += met->posY * t;

	t -= met->continuity;
	n++;
	met = met->prev;
    }

    vx = (n*xtsum - tsum*xsum) / (n*t2sum - tsum*tsum);
    vy = (n*ytsum - tsum*ysum) / (n*t2sum - tsum*tsum);
    Rx = ((n*xtsum-xsum*tsum)*(n*xtsum-xsum*tsum))/((n*x2sum-xsum*xsum)*(n*t2sum-tsum*tsum));
    Ry = ((n*ytsum-ysum*tsum)*(n*ytsum-ysum*tsum))/((n*y2sum-ysum*ysum)*(n*t2sum-tsum*tsum));

    met0->vx = vx;
    met0->vy = vy;
    met0->R = Rx*Ry;
}
    
int backTraceMeteor(struct graph *met0) {
    int i=0;
    struct graph *met;
    met = met0;

    printf("X\t\tY\t\txyVar\t\tdens\t\tnum \n");

    while (met != NULL) {
	printf("%f\t", met->posX);
	printf("%f\t", met->posY);
	printf("%f\t", met->posVar);
	printf("%f\t", met->dens);
	printf("%i\t", met->Nvtc);
	printf("\n");
	met = met->prev;
	i++;
    }
    printf("\n");
    return i;
}

void printImage(struct image *img) {
    int i;
    printf("\n");
    /*
    print2dArray(img->adj, img->Nlght, img->Nshdw);
    printf("\n");
    */

    for (i=0; i<(img->num); i++) {
	//printf("meteor =%i= || postion: X = %.2f, Y = %.2f (Var=%.2f) | velocity: vx = %.3f, vy = %.3f (R=%.4f) | mean weight = %i | mean degree = %i | density = %f | continuity = %i\n", i, img->met[i]->posX, img->met[i]->posY, img->met[i]->posVar, img->met[i]->vx, img->met[i]->vy, img->met[i]->R, img->met[i]->mWeight, img->met[i]->mDegree, img->met[i]->dens, img->met[i]->continuity);
	printf("LIGHT: ");
	print1dArray(img->met[i]->lght, img->met[i]->Nlght);
	printf("SHADOW: ");
	print1dArray(img->met[i]->shdw, img->met[i]->Nshdw);
	printf("\n");
	/*
	print1dArray(img->met[i]->x, img->met[i]->Nvtc);
	print1dArray(img->met[i]->y, img->met[i]->Nvtc);
	print2dArray(img->met[i]->weights, img->met[i]->Nvtc, img->met[i]->Nvtc);
	*/
	//if (img->met[i]->deg != NULL) print1dArray(img->met[i]->deg, img->met[i]->Nvtc);
	printf("\n");
    }
}
	
