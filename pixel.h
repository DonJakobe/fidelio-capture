
int getX(int index) {
    return index % width;
}

int getY(int index) {
    //printf("h%i", height);
    return index / width;
}

int *substractFrames(unsigned char *frameA, unsigned char *frameB) {
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
    int i;
    float meanX=0, meanY=0;
    float meanX2=0, meanY2=0;

    int N = met->Nvtc;
    
    for (i=0; i<N; i++) {
	meanX += (float) getX(met->vtc[i]);
	meanX2 += (float) getX(met->vtc[i]) * getX(met->vtc[i]);
	meanY += (float) getY(met->vtc[i]);
	meanY2 += (float) getY(met->vtc[i]) * getY(met->vtc[i]);
    }
    met->posX = meanX/N;
    met->posY = meanY/N;
    met->posVar = (meanX2/N - meanX*meanX/(N*N)) * (meanY2/N - meanY*meanY/(N*N));
}
