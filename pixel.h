
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
	    light = addToList(light, i, *nbright);
	    *nbright = *nbright + 1;
	}
	else if (frame[i] < -l) {
	    shadow = addToList(shadow, i, *ndark);
	    *ndark = *ndark + 1;
	}
    }
}
