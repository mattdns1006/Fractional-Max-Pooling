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
			m->matrix[idx] = idx*2;
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
	long nInH;
	long nInW;
	long nOutH;
	long nOutW;
	int poolSize;
	long *sequenceW;
	long *sequenceH;
};

struct Sequence *newSequence(long nInW, long nOutW, long nInH, long nOutH, int poolSize)
{
	struct Sequence *s = malloc(sizeof(struct Sequence));

	s->nInW = nInW;
	s->nOutW = nOutW;
	s->nInH = nInH;
	s->nOutH = nOutH;
	s->poolSize = poolSize;
	size_t size = sizeof(long);

	s->sequenceW = (long*)malloc(size*(nOutW));
	s->sequenceH = (long*)malloc(size*(nOutH));

	float alphaW, alphaH;
	alphaW = (float)(nInW - poolSize)/(float)(nOutW - 1);
	alphaH = (float)(nInH - poolSize)/(float)(nOutH - 1);
	
	float u = 0.5;

	long i;

	s->sequenceW[0] = 0;
	for(i=1;i < s->nOutW ;i++){
		s->sequenceW[i] = ceil(alphaW*(i+u))-1;
	}

	s->sequenceH[0] = 0;
	for(i=1;i < s->nOutH ;i++){
		s->sequenceH[i] = ceil(alphaH*(i+u))-1;
	}
	return s;
};

void sequencePrint(struct Sequence *s){
	int gap = 5;
	long i;
	printf("Indices Sequences width \n");
	for(i=0;i<s->nOutW;i++){
		printf("%*ld ",gap,i);
		printf("%*ld ",gap, s->sequenceW[i]);
	printf("\n");
	}
	printf("Indices Sequences height \n");
	for(i=0;i<s->nOutH;i++){
		printf("%*ld ",gap,i);
		printf("%*ld ",gap, s->sequenceH[i]);
	printf("\n");
	}
	printf("\n");
}

void forwardInput(struct Matrix *input, struct Matrix *output, struct Sequence *sequence){
	long i,j;
	long idx,idx1;
	long i1,j1;
	long startW, startH;
	int gap =5;
	int poolSize = sequence-> poolSize;
	float maxVal,val;
	long *seqH = sequence->sequenceH;
	long *seqW = sequence->sequenceW;

	for(j=0;j<output->h;j++){
		for(i=0;i<output->w;i++){

			idx = i + j*output->w;
			//printf("i,j,idx = %lu %lu \n",i,j,idx);

			startW = i;
			startH = j;
			maxVal = input->matrix[idx];
			for(j1=0; j1 < poolSize; ++j1){
				for(i1=0; i1 < poolSize; ++i1 ){


					long x = seqW[i] + i1;	
					long y = seqH[j] + j1;	
					idx1 = x + y*input->w;
					val = input->matrix[idx1];
					
					//printf("i1,j1,idx,val(idx) = %lu, %lu, %lu, %f \n",x,y,idx1,val);
					if (val > maxVal)
						maxVal = val;

				}
			}
			//printf("Max value = %f \n\n",maxVal);

			output->matrix[idx] = maxVal;
				
		}
		printf("\n");
	}
	printf("\n");
}


int main(void){

	int poolSize = 2;
	long inputW = 10;
	long inputH = 10; // Make everything square to begin with
	float fmp = 0.6;
	long outputH = floor(inputH*fmp);
	long outputW = floor(inputW*fmp);
	float u = 0.5;
	
	struct Matrix *input = newMatrix(inputW,inputH);
	struct Matrix *output = newMatrix(outputW,outputH);
	matrixPrint(input);
	//matrixPrint(output);

	struct Sequence *sequenceH = newSequence(inputW, outputW, inputH, outputH, poolSize);
	sequencePrint(sequenceH);

	forwardInput(input,output,sequenceH);
	matrixPrint(output);


	return 0;
}
