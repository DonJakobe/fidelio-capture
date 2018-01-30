
void substractFrames(char *frameA, char *frameB, int *diff) {
    int i;
    
    for (i=0; i<length; i++){
	diff[i] = (int) (frameA[i]) - (int) (frameB[i]);
    }
}

void identifyPix(int l, int *nbright, int *ndark, int *frame, int *brightPix, int *darkPix) {
    int i;
    *nbright = 0;
    *ndark = 0;

    for (i=0; i<length; i++) {
	if (frame[i] > l) {
	  brightPix[*nbright] = i;
	  *nbright = *nbright + 1;
	}
	else if (frame[i] < -l) {
	    darkPix[*ndark] = i;
	    *ndark = *ndark + 1;
	}
    }
}
