#include <stdio.h>
#include <stdlib.h>

const int length = 10;
char daten1[] = {1, 0, 1, 0, 1, 1, 1, 1, 1, 1};
char daten2[] = {1, 0, 1, 255, 1, 1, 1, 100, 1, 3};

#include "met.h"

void substract(struct image *frm1, struct image *frm2, struct image *sub){
    int i;
    sub->prev = NULL;
    sub->next = NULL;
    sub->data = malloc(length);

    for (i = 0; i < 10; i++) {
	sub->data[i] = frm1->data[i] - frm2->data[i];
    }
}


int main(){
    int i;
    struct image *bild1 = malloc(sizeof(struct image));
    struct image *bild2 = malloc(sizeof(struct image));
    struct image *result = malloc(sizeof(struct image));
    
    bild1->index = 0;
    bild1->prev = bild2;
    bild1->next = bild2;
    bild1->data = daten1;

    bild2->index = 1;
    bild2->prev = bild1;
    bild2->next = bild1;
    bild2->data = daten2;

    printf("index = %i \n", bild1->data[0]);

    substract(bild1, bild2, result);

    for (i = 0; i < 10; i++) {
	printf("subtraction yields: %i \n", result->data[i]);
    }	
}


