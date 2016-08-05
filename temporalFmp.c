#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long* generateIntervals(float u, long inputSize, long outputSize, int poolSize){
	float alpha;
	alpha = (float)(inputSize - poolSize)/(float)(outputSize- 1);
	long *sequence = (long*)malloc(sizeof(long)*outputSize+1);
	long i;
	sequence[0] = 0;
	sequence[outputSize+1] = inputSize;
	for(i=1;i<=outputSize;i++){
		sequence[i] = ceil(alpha*(i+u))-1;
		int incr = sequence[i] - sequence[i-1];
		printf("Sequence[%ld] = %ld (increment %d) \n",i,sequence[i],incr);

	}
	return sequence;
}

void forwardPass(long *output, long outputSize, long *input, long *sequence){
	long i, j;

	// For each pooling pair in sequence
	long p1, p2, v1, v2;
	for(i=0; i < outputSize; i++){
		p1 = sequence[i];
		p2 = sequence[i+1];
		v1 = input[p1];
		v2 = input[p2];
		output[i] = (v1 > v2) ? v1 : v2;
	}
	printf("\n ");
}

int main(void){
	int poolSize = 2;
	long inputSize = 10;
	long *input, *output;
	float fmp = 0.7;
	long outputSize = floor(inputSize*fmp);
	float u = 0.5;
	printf("inSize = %ld, ouSize = %ld, fraction = %f. \n",inputSize,outputSize,fmp);

	size_t inBytes = sizeof(long)*inputSize;
	size_t outBytes = sizeof(long)*outputSize;
	input = (long*)malloc(inBytes);
	output = (long*)malloc(outBytes);

	// Generate some random 1d input data
	printf("Input array \n");
	long i;
	for(i=0;i < inputSize; i++){
		input[i] = i;
		printf("%ld ",input[i]);
	}
	printf("\n\n");

	long *sequence = generateIntervals(u,inputSize,outputSize,poolSize);
	printf("Pooling sequence array \n");
	for(i=0;i < outputSize + 1; i++){
		printf("%ld ",sequence[i]);
	}
	printf("\n");

	forwardPass(output, outputSize, input, sequence);	
	printf("Result \n");
	for(i=0; i < outputSize; i++){
		printf("%ld ",output[i]);
	}
	printf("\n");
	
	return 0;
}



