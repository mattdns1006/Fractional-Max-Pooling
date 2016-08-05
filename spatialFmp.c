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
	int gap = 10;

	for(j=0; j< m->h; j++){
		for(i=0; i< m->w; i++){
			idx = i + j*m->w;
			printf("%*f ",gap,m->matrix[idx]);
		}
		printf("\n");
	}
	printf("\n\n");
}


long* generateIntervals(float u, long nIn, long nOut, int poolSize){
	float alpha;
	alpha = (float)(nIn - poolSize)/(float)(nOut - 1);
	long *sequence = (long*)malloc(sizeof(long)*nOut+1);
	long i;
	sequence[0] = 0;
	sequence[nOut+1] = nIn;
	for(i=1;i<=nOut ;i++){
		sequence[i] = ceil(alpha*(i+u))-1;
	}
	return sequence;
}


int main(void){

	int poolSize = 2;
	long inputW = 10;
	long inputH = 10;
	float fmp = 0.7;
	long outputH = floor(inputH*fmp);
	long outputW = floor(inputW*fmp);
	float u = 0.5;

	struct Matrix *input = newMatrix(inputW,inputH);
	struct Matrix *output = newMatrix(outputW,outputH);
	matrixPrint(input);
	matrixPrint(output);

	long *sequenceH, *sequenceW;
	sequenceW = generateIntervals(u,inputW,outputW,poolSize);
	sequenceH = generateIntervals(u,inputH,outputH,poolSize);

	return 0;
}
