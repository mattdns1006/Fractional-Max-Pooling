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
		//printf("Sequence[%ld] = %ld (increment %d) \n",i,sequence[i],incr);
	}
	return sequence;
}

void forwardPass(float *output, long outputSize, float *gradInput, float *input, long *sequence){
	long i, j;

	// For each pooling pair in sequence
	long p1, p2;
       	float v1, v2;
	for(i=0; i < outputSize; i++){
		p1 = sequence[i];
		p2 = sequence[i+1];
		v1 = input[p1];
		v2 = input[p2];
		output[i] = (v1 > v2) ? v1 : v2;
		if(v1>v2){
			gradInput[p2] = 1;

		}else{
			gradInput[p1] = 1;
		}

	}
	printf("\n ");
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

	// Generate some random 1d input data and fill gradients with 0
	printf("\n\n");
	printf("Input array \n");
	int i;
	for(i=0;i < inputSize; i++){
		input[i] = cos(i);
		gradInput[i] = 0;
		printf("%f ",input[i]);
	}
	printf("\n\n");

	long *sequence = generateIntervals(u,inputSize,outputSize,poolSize);
	printf("Pooling sequence array \n");
	for(i=0;i < outputSize + 1; i++){
		printf("%ld ",sequence[i]);
	}
	printf("\n\n");

	forwardPass(output, outputSize, gradInput, input, sequence);	
	printf("Result \n");
	for(i=0; i < outputSize; i++){
		printf("%f ",output[i]);
	}
	printf("\n\n");

	printf("gradInput \n");
	for(i=0; i < inputSize; i++){
		printf("%f ",gradInput[i]);
	}
	printf("\n\n");

	/*
	FILE *gnuplot = popen("gnuplot -persistent","w");
	fprintf(gnuplot,"plot '-'\n");
	for(i = 0; i < 10; i++)
		fprintf(gnuplot, "%g %g\n", gradInput[i] , gradInput[i]);
	fprintf(gnuplot, "e\n");
	fflush(gnuplot);
	*/
	
	free(input);
	free(output);
	free(gradInput);

	return 0;
}



