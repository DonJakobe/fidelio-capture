
int getX(int index) {
    return index % width;
}

int getY(int index) {
    return index / height;
}

int *substractFrames(char *frameA, char *frameB) {
    int i;
    static int diff[length];
    
    for (i=0; i<length; i++){
	diff[i] = (int) (frameA[i]) - (int) (frameB[i]);
    }
    return diff;
}

void identifyPix(struct image *img, int *diff, int lim) {
    int i;

    for (i=0; i<length; i++) {
	if (diff[i] > lim) {
	    img->lght = addToList(img->lght, i, img->Nlght);
	    img->Nlght++;
	}
	else if (diff[i] < -lim) {
	    img->shdw = addToList(img->shdw, i, img->Nshdw);
	    img->Nshdw++;
	}
    }
}

int squareDist(int i1, int i2) {
    return (getX(i1)-getX(i2)) * (getX(i1)-getX(i2)) + (getY(i1)-getY(i2)) * (getY(i1)-getY(i2));
}

