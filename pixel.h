
int getX(int index) {
    return index % width;
}

int getY(int index) {
    //printf("h%i", height);
    return index / width;
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

void getPosition(struct graph *met) {
    int i, j;
    float meanX=0, meanY=0;
    float meanX2=0, meanY2=0;

    int N = met->Nvtc;
    
    for (j=0; j<N; j++) {
	meanX += (float) getX(met->vtc[j]);
	meanX2 += (float) getX(met->vtc[j]) * getX(met->vtc[j]);
	meanY += (float) getY(met->vtc[j]);
	meanY2 += (float) getY(met->vtc[j]) * getY(met->vtc[j]);
    }
    met->posX = meanX/N;
    met->posY = meanY/N;
    met->posVar = (meanX2/N - meanX*meanX/(N*N)) * (meanY2/N - meanY*meanY/(N*N));
}
