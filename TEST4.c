#define height 3
#define width 3
#define length 345600

#include <stdlib.h>
#include <stdio.h>

int main() {
    int i;
    FILE *file = fopen("video.bwv", "rb");
    unsigned char *c = calloc(length+1, 1);

    //fread(&c, 1, 1, file);
    fread(c, sizeof(char), length, file);
    fread(c, sizeof(char), 10, file);

    for (i=0; i<(10); i++) {
	printf("%d ", c[i]);
    }
    
    return 0;
}
