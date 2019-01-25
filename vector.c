/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for vector related function
** vector starts from 0 index
** as a rule, in function names type is omitted if integer
** it should be allocateIntVector, allocateDoubleVector, etc
**
** first created	26/10/2018 (with older materials)
** version 0			29/10/2018
** last updated		25/01/2019
**
** function count -> 15
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int *allocateVector (int n) { //debugged
	int *X = NULL;
	if (n < 0)
		fprintf(stderr, "!E allocateVector: requested negative memory allocation\n");
	else
		X = malloc(sizeof(int)*n);
	if(!X)
		fprintf(stderr, "!E allocateVector: memory allocation error\n");
	fflush(stderr);
	return(X);
}

int copyVector (int *A, int *B, int n) { //debugged
	int i, flag = 0;
	if (!A || !B)
		fprintf(stderr, "!W copyMatrix: matrix not allocated\n");
	else {
		flag = 1;
		for (i=0; i<n; i++)
			B[i]=A[i];
	}
	return (flag);
}

void deleteVector (int *X) { //debugged
	if (X)
		free(X);
	else
		fprintf(stderr, "!W deleteVector: requested NULL pointer deallocation\n");
	return;
}

void exportReverseVector(FILE *output, int *X, int n) { //debugged
	if (!output)
		fprintf(stderr, "!W exportReverseVector: outuput file not opened\n");
	else if (!X)
		fprintf(stderr, "!W exportReverseVector: vector not allocated\n");
	else {
		while (n)
			fprintf(output, "%d\t", X[--n]);
		fprintf(output, "\n");
	}
	return;
}

void exportVector (FILE *output, int *X, int n) { //debugged
	int i;

	if (!output)
		fprintf(stderr, "!W exportVector: outuput file not opened\n");
	else if (!X)
		fprintf(stderr, "!W exportVector: matrix not allocated\n");
	else {
		for (i=0; i<n; i++)
			fprintf (output, "%d\t", X[i]);
		fprintf (output, "\n");
	}
	return;
}

int importVector (FILE *input, int *A, int n) { //debugged
	int i = 0;

	if (!input)
		fprintf(stderr, "!W importVector: input file not opened\n");
	else if (!A)
		fprintf(stderr, "!W importVector: vector not allocated\n");
	else {
		for (i=0; i<n; i++)
			fscanf (input, "%d", &A[i]);
	}
	return (i);
}

int initializeVector (int *X, int n, int a) { //debugged
	int i = 0;
	if (!X)
		fprintf(stderr, "!W initializeVectori: vector is not allocated\n");
	else {
		for (i=0; i<n; i++)
			X[i] = a;
	}
	return (i);
}

int linearVectors (int *V, int *W, int *Z, int n, int a, int b) { //debugged
	int i = 0;

	if (!V || !W || !Z)
		fprintf(stderr, "!W linearVectors: vector not allocated\n");
	else {
		for (i=0; i<n; i++)
			Z[i] = a*V[i] + b*W[i];
	}
	return (i);
}

int maxVector (int *X, int n) { //debugged
	int i, max = 0;

	if (!X)
		fprintf(stderr, "!W linearVectors: vector not allocated\n");
	else {
		for (i=0; i<n; i++) {
			if (X[i] > X[max])
				max = i;
		}
	}

	return(max);
}

int minVector (int *X, int n) { //debugged
	int i, min = 0;

	if (!X)
		fprintf(stderr, "!W linearVectors: vector not allocated\n");
	else {
		for (i=0; i<n; i++) {
			if (X[i] < X[min])
				min = i;
		}
	}

	return(min);
}

void randVector (int *A, int n, int a, int b) { //debugged
	int i;

	if (!A)
		fprintf(stderr, "!W randVector: vector not allocated\n");
	else {
		for (i=0; i<n; i++)
			A[i] = (rand()%(b-a+1)) + a;
	}
	return;
}

void scalarVector (int *V, int *W, int n, int k) { //debugged
	int i;
	if (!V || !W)
		fprintf(stderr, "!W scalarVector: vector not allocated\n");
	else {
		for (i=0; i < n; i++)
			W[i] = k*V[i];
	}
	return;
}

void sumVectors (int *A, int *B, int *S, int n) { //debugged
	int i;

	if (!A || !B || !S)
		fprintf(stderr, "!W sumVectors: vector not allocated\n");
	else {
		for (i=0; i<n; i++)
			S[i] = A[i]+B[i];
	}
	return;
}

double vectorMean (int *V, int n) {
	int i, s = 0;
	if (!V)
		fprintf(stderr, "!W vectorMean: vector not allocated\n");
	else if (!n) {
		fprintf(stderr, "!W vectorMean: requested mean for vector of 0 element\n");
		n = 1;
	}
	else {
		for (i=0; i<n; i++)
			s += V[i];
	}
	return((double) s/n);
}

int vectorVector (int *A, int *B, int n) { //debugged
	int s = 0, i;

	if (!A || !B)
		fprintf(stderr, "!W vectorVector: vector not allocated\n");
	else {
		for (i=0; i < n; i++ )
			s += A[i]*B[i];
	}
	
	return (s);
}