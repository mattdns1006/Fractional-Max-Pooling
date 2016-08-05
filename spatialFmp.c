#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Matrix
{
	long w;
	long h;
	float *matrix;
};

struct Matrix *newMatrix(long w, long h)
{
	struct Matrix *m = malloc(sizeof(struct Matrix));
	m->w = w;
	m->h = h;
	m->matrix = (float*)malloc(w*h*sizeof(float));
	unsigned int i, j,idx;
	for(j=0; j< m->h; j++){
		for(i=0; i< m->w; i++){
			idx = i + j*m->w;
			m->matrix[idx] = sin(idx);
		}
	}
	return m;
};

void matrixPrint(struct Matrix *m){
	int idx, i,j;
	int gap = 4;

	for(j=0; j< m->h; j++){
		for(i=0; i< m->w; i++){
			idx = i + j*m->w;
			//printf("(%d, %d) ",i,j);
			printf("%*f",gap,m->matrix[idx]);
		}
		printf("\n");
	}
}


int main(void){

	int poolSize = 2;
	long inputSize = 100;
	float *input, *output, *gradInput;
	float fmp = 0.7;
	long outputSize = floor(inputSize*fmp);
	float u = 0.5;
	printf("inSize = %ld, ouSize = %ld, fraction = %f. \n",inputSize,outputSize,fmp);

	size_t inBytes = sizeof(float)*inputSize;
	size_t outBytes = sizeof(float)*outputSize;
	input = (float*)malloc(inBytes);
	output = (float*)malloc(outBytes);
	gradInput = (float*)malloc(inBytes);

	struct Matrix *m1 = newMatrix(20,8);
	matrixPrint(m1);


	free(input);
	free(output);
	free(gradInput);
	return 0;
}
