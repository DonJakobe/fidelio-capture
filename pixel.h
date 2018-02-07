
int getX(int index) {
    return index % width;
}

int getY(int index) {
    return index / height;
}

void substractFrames(char *frameA, char *frameB, int *diff) {
    int i;
    
    for (i=0; i<length; i++){
	diff[i] = (int) (frameA[i]) - (int) (frameB[i]);
    }
}

void identifyPix(int l, int *nbright, int *ndark, int *frame) {
    int i;
    *nbright = 0;
    *ndark = 0;

    for (i=0; i<length; i++) {
	if (frame[i] > l) {
	    lght = addToList(lght, i, *nbright);
	    *nbright = *nbright + 1;
	}
	else if (frame[i] < -l) {
	    shdw = addToList(shdw, i, *ndark);
	    *ndark = *ndark + 1;
	}
    }
}

int squareDist(int i1, int i2) {
    return (getX(i1)-getX(i2)) * (getX(i1)-getX(i2)) + (getY(i1)-getY(i2)) * (getY(i1)-getY(i2));
}

