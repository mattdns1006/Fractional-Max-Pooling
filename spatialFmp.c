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


struct Sequence 
{
	long nIn;
	long nOut;
	int poolSize;
	long *sequence;
};

struct Sequence *newSequence(long nIn, long nOut, int poolSize)
{
	struct Sequence *s = malloc(sizeof(struct Sequence));
	s->nIn = nIn;
	s->nOut = nOut;
	s->poolSize = poolSize;
	s->sequence = (long*)malloc(sizeof(long)*(nOut+1));
	float alpha;
	alpha = (float)(nIn - poolSize)/(float)(nOut - 1);
	long i;
	float u = 0.5;
	s->sequence[0] = 0;
	s->sequence[nOut+1] = nIn - 1;
	for(i=1;i <= s->nOut ;i++){
		s->sequence[i] = ceil(alpha*(i+u))-1;
	}
	return s;
};

void sequencePrint(struct Sequence *s){
	int gap = 5;
	long i;
	printf("Indices Sequence\n");
	for(i=0;i<=s->nOut;i++){
		printf("%*ld ",gap,i);
		printf("%*ld ",gap, s->sequence[i]);
	printf("\n");
	}
	printf("\n");
}

void forwardInput(struct Matrix *input, struct Matrix *output, struct Sequence *sequence){
	long i,j,idx,idx2;
	long i1,j1;
	long startW, startH;
	int gap =5;
	int poolSize = sequence-> poolSize;
	float maxVal;

	for(j=0;j<output->h;j++){
		for(i=0;i<output->w;i++){

			idx = i + j*output->w;
			startW = i;
			startH = j;
			maxVal = -100;
			output->matrix[idx] = maxVal;
				
		}
		printf("\n");
	}
	printf("\n");
}


int main(void){

	int poolSize = 2;
	long inputW = 15;
	long inputH = inputW; // Make everything square to begin with
	float fmp = 0.6;
	long outputH = floor(inputH*fmp);
	long outputW = floor(inputW*fmp);
	float u = 0.5;
	
	struct Matrix *input = newMatrix(inputW,inputH);
	struct Matrix *output = newMatrix(outputW,outputH);
	matrixPrint(input);
	matrixPrint(output);

	struct Sequence *sequenceH = newSequence(inputH,outputH,poolSize);
	sequencePrint(sequenceH);

	forwardInput(input,output,sequenceH);
	matrixPrint(output);


	return 0;
}
