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
** last updated		20/12/2018
**
** function count -> 31
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int **allocateMatrix (int n, int m) { //debugged
	int i = 0, **X = NULL;
	X = malloc(sizeof(int*)*n);
	if (!X)
		fprintf (stderr, "!E allocateMatrix: memory allocation error\n");
	else {
		X[0] = allocateVector(m);
		n = n-1;
		while (X[i] && i < n) {
			X[++i] = allocateVector(m);
			if (!X[i]) {
				fprintf(stderr, "!E allocateMatrix: memory allocation error\n");
				freeMatrix(X, n);
			}
		}
	}
	return (X);
}

int *allocateVector (int n) { //debugged
	int *X = malloc(sizeof(int)*n);
	if(!X)
		fprintf(stderr, "!E allocate Vector: memory allocation error\n");
	return(X);
}

void copyMatrix (int **A, int **B, int n, int m) { //debugged
	int i;
	for (i=0; i<n; i++)
		copyVector(A[i], B[i], m);
	return;
}

void copyVector (int *A, int *B, int n) { //debugged
	int i;
	for (i=0; i<n; i++)
		B[i]=A[i];
	return;
}

void deleteMatrix (int **X, int n) { //debugged
	int i;
	if (X) {
		for (i=0; i < n; i++)
			X[i] = freeVector(X[i]);
		free(X);
	} else
		fprintf(stderr, "!W freeMatrix: requested NULL pointer deallocation\n");
	return;
}

void deleteVector (int *X) { //debugged
	if (X)
		free(X);
	else
		fprintf(stderr, "!W freeVector: requested NULL pointer deallocation\n");
	return;
}

void exportMatrix (FILE *output, int **X, int n, int m) { //debugged
		int i;
		for (i=0; i<n; i++)
			exportVector(output, X[i], m);
		return;
}

void exportSubMatrix (FILE *output, int **X, int k, int h, int p, int q) { //debugged
	int i, n = k+p;
	for (i=k; i<n; i++)
		exportVector(stdout, &X[i][h], q);
	return;
}

void exportReverseVector(FILE *output, int *A, int n) { //debugged
	while (n)
		fprintf(output, "%d\t", A[--n]);
	fprintf(output, "\n");
	return;
}

void exportVector (FILE *output, int *A, int n) { //debugged
	int i;
	for (i=0; i<n; i++)
		fprintf (output, "%d\t", A[i]);
	fprintf (output, "\n");
	return;
}

void importMatrix ( FILE *input, int **X, int n, int m) { //debugged
	int i;
	for (i=0; i<n; i++)
		importVector(input, X[i], m);
	return;
}

void importVector (FILE *input, int *A, int n) { //debugged
	int i;
	for (i=0; i<n; i++)
		fscanf (input, "%d", &A[i]);
	return;
}

void initializeMatrix (int **X, int n, int m, int a) { //debugged
	int i;
	for (i=0; i < n; i++)
		initializeVector(X[i], m, a);
	return;
}

void initializeVector (int *X, int n, int a) { //debugged
	int i;
	for (i=0; i<n; i++)
		X[i] = a;
	return;
}

void linearMatrices (int **X, int **Y, int **Z, int n, int m, int a, int b) { //debugged
	int i;
	for (i=0; i<n; i++)
		linearVectors(X[i], Y[i], Z[i], m, a, b);
	return;
}

void linearVectors (int *V, int *W, int *Z, int n, int a, int b) { //debugged
	int i;
	for (i=0; i<n; i++)
		Z[i] = a*V[i] + b*W[i];
	return;
}

void matrixVector (int **X, int *B, int *P, int n, int m) { //debugged
	int i;
	for (i=0; i < n; i++)
		P[i] = vectorVector(X[i], B, m);
	return;
}

void matrixMatrix (int **X, int **Y, int **Z, int n, int m, int p) { //debugged
	int i, j, k, s;
	for (i=0; i < n; i++)
		for (j=0; j < p; j++) {
			s = 0;
			for (k=0; k < m; k++)
				s += X[i][k]*Y[k][j];
			Z[i][j] = s;
		}
	return;
}

int matrixMatrixPlus (int **X, int **Y, int **Z, int n, int m, int p) { //debugged
	int **W, i, j = 0;

	W = allocateMatrix(p, m);
	if (W) {
		transposeMatrix(Y, W, m, p);
		for (i=0; i < n; i++)
			for (j=0; j < p; j++)
				Z[i][j] = vectorVector(X[i], W[j], m);
	}
	return (j);
}

int maxVector (int *X, int n) { //debugged
	int i, max = 0;
	for (i=0; i<n; i++) {
		if (X[i] > X[max])
			max = i;
	}
	return(max);
}

int minVector (int *X, int n) { //debugged
	int i, min = 0;
	for (i=0; i<n; i++) {
		if (X[i] < X[min])
			min = i;
	}
	return(min);
}

void randMatrix (int **X, int n, int m, int a, int b) { //debugged
	int i;
	for (i=0; i<n; i++)
		randVector(X[i], m, a, b);
	return;
}

void randVector (int *A, int n, int a, int b) { //debugged
	int i;
	for (i=0; i<n; i++)
		A[i] = (rand()%(b-a+1)) + a;
	return;
}

void scalarMatrix (int **X, int **Y, int n, int m, int k) { //debugged
	int i;
	for (i=0; i < n; i++)
		scalarVector(X[i], Y[i], m, k);
	return;
}

void scalarVector (int *V, int *W, int n, int k) { //debugged
	int i;
	for (i=0; i < n; i++)
		W[i] = k*V[i];
	return;
}

void sumMatrices (int **X, int **Y, int **Z, int n, int m) { //debugged
	int i;
	for (i=0; i<n; i++)
		sumVectors(X[i], Y[i], Z[i], m);
	return;
}

void sumVectors (int *A, int *B, int *S, int n) { //debugged
	int i;
	for (i=0; i<n; i++)
		S[i] = A[i]+B[i];
	return;
}

void swapRows (int **X, int k, int h) { //debugged
	int *A;

	A = X[k];
	X[k] = X[h];
	X[h] = A;
	return;
}

void transposeMatrix (int **X, int **Y, int n, int m) { //debugged
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			Y[j][i] = X[i][j];
	return;
}

double vectorMean (int *V, int n) {
	int i, s = 0;
	for (i=0; i<n; i++)
		s += V[i];
	return((double) s/n);
}

int vectorVector (int *A, int *B, int n) { //debugged
	int s = 0, i;
	for (i=0; i < n; i++ )
		s += A[i]*B[i];
	return (s);
}