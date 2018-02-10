
#include <stdio.h>
#include <stdlib.h>

#define height 480
#define width 720
#define length 345600

static char *input;
//const int height = 480;
//const int width = 720;
//const int length = 345600;
const int buffer_size = 150;
const int n_elapsed = 50;

static struct image *frm = NULL;

int *initList(int *list);
int *addToList(int *list, int item, int size);
int *rmFromList(int *list, int item, int cols);
void switchEle(int *list, int item1, int item2);
//int *cat1dArrays();
//int sum1dArray();
int **alloc2dArray(int **arr, int rows, int cols);
int **free2dArray(int **arr, int rows);
int **rmRow(int **arr, int row0, int *rows);
int **rmCol(int **arr, int col0, int rows, int *cols);
void switchRows(int **arr, int row1, int row2, int cols);
void switchCols(int **arr, int col1, int col2, int rows);
void print1dArray(int *list, int dim);
void print2dArray(int **arr, int rows, int cols);

#include "met.h"
#include "analysis.h"

// write video file to frm-buffer
int load_file(void) {
	FILE *fp;
	int i;

	fp = fopen(input, "r");
	
	// write each frame of input to data array of cyclical buffer, one at a time ("buffer_size" times)
	for (i = 0; i < buffer_size; i++) {
		fread(frm->data, length, 1, fp); // write to current frame
		frm = frm->next; // jump to next frame in "frm"
	}

	fclose(fp); // close input
}

// write video to file 
int write_video(void) {
	int i;
	FILE *outfd = fopen("positiv.bwv", "a"); // open file in append mode

	// append frames to file
	for (i = 0; i < buffer_size; i++) {
		fwrite(frm->data, length, 1, outfd); // append current frame
		frm = frm->next; // jump to next frame
	}

	fclose(outfd); // close file
	return 0;
}

// main loop works similar to actual 
int mainloop(void) {
	int n = 0;
	while (1) {
		if (1 == analyseFrame())
			n++;
		else
			n = 0;
		

		if (!(n < n_elapsed)) {
			write_video();
			break;
		}

		frm = frm->next;

		//printf("elapsed: %i\n", n);
	}
}


int main(int argc,char* argv[]){
    input = argv[1];
	frm = buildBuffer(buffer_size); // generate cyclicalc buffer of size "buffer_size" frames
	load_file(); // invoke the load_file() function in order to fill generated buffer with frames from "input"

	mainloop(); // start the main loop
}

