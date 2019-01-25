/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for matrix related function
** vector starts from 0 index
** as a rule, in function names type is omitted if integer
** it should be allocateIntMatrix, allocateDoubleMatrix, etc
** depends on vector.h
**
** first created	25/01/2019 (with older materials)
** version 0			25/01/2019
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
#include "matrix.h"

int **allocateMatrix (int n, int m) { //debugged
	int i = 0, **X = NULL;
	if (n < 0 || m < 0)
		fprintf(stderr, "!E allocateMatrix: requested negative memory allocation\n");
	else X = malloc(sizeof(int*)*n);
	if (!X)
		fprintf (stderr, "!E allocateMatrix: memory allocation error\n");
	else {
		X[0] = allocateVector(m);
		n = n-1;
		while (X[i] && i < n) {
			X[++i] = allocateVector(m);
			if (!X[i]) {
				fprintf(stderr, "!E allocateMatrix: memory allocation error\n");
				deleteMatrix(X, n);
			}
		}
	}
	return (X);
}

int copyMatrix (int **A, int **B, int n, int m) { //debugged
	int i, flag = 0;
	if (!A || !B)
		fprintf(stderr, "!W copyMatrix: matrix not allocated\n");
	else {
		flag = 1;
		for (i=0; i<n; i++)
			copyVector(A[i], B[i], m);
	}
	return (flag);
}

void deleteMatrix (int **X, int n) { //debugged
	int i;
	if (X) {
		for (i=0; i < n; i++)
			deleteVector(X[i]);
		free(X);
	} else
		fprintf(stderr, "!W deleteMatrix: requested NULL pointer deallocation\n");
	return;
}

void exportMatrix (FILE *output, int **X, int n, int m) { //debugged
	int i;

	if (!output)
		fprintf(stderr, "!W exportMatrix: outuput file not opened\n");
	else if (!X)
		fprintf(stderr, "!W exportMatrix: matrix not allocated\n");
	else {
		for (i=0; i<n; i++)
			exportVector(output, X[i], m);
	}
	return;
}

void exportSubMatrix (FILE *output, int **X, int k, int h, int p, int q) { //debugged
	int i, n = k+p;

	if (!output)
		fprintf(stderr, "!W exportSubMatrix: outuput file not opened\n");
	else if (!X)
		fprintf(stderr, "!W exportSubMatrix: matrix not allocated\n");
	else {
		for (i=k; i<n; i++)
			exportVector(stdout, &X[i][h], q);
	}
	return;
}

int importMatrix (FILE *input, int **X, int n, int m) { //debugged
	int i = 0;

	if (!input)
		fprintf(stderr, "!W importMatrix: input file not opened\n");
	else if (!X)
		fprintf(stderr, "!W importMatrix: matrix not allocated\n");
	else {
		for (i=0; i<n; i++)
			importVector(input, X[i], m);
	}
	return (i);
}

int initializeMatrix (int **X, int n, int m, int a) { //debugged
	int i = 0, flag = 0;

	if (!X)
		fprintf(stderr, "!W initializeMatrix: matrix is not allocated\n");
	else {
		flag = 1;
		for (i=0; i < n; i++) {
			if (!initializeVector(X[i], m, a)) {
				i = n;
				flag = 0;
			}
		}
	}
	return(flag);
}

int linearMatrices (int **X, int **Y, int **Z, int n, int m, int a, int b) { //debugged
	int i, flag = 0;
	if (!X || !Y || !Z)
		fprintf(stderr, "!W linearMatrices: matrix not allocated\n");
	else {
		flag = 1;
		for (i=0; i<n; i++) {
			if (!linearVectors(X[i], Y[i], Z[i], m, a, b)) {
				i = n;
				flag = 0;
			}
		}
	}
	return (flag);
}

void matrixVector (int **X, int *B, int *P, int n, int m) { //debugged
	int i;
	if (!X || !B || !P)
		fprintf(stderr, "matrixVector: matrix or vector not allocated\n");
	else {
		for (i=0; i < n; i++)
			P[i] = vectorVector(X[i], B, m);
	}
	return;
}

void matrixMatrix (int **X, int **Y, int **Z, int n, int m, int p) { //debugged
	int i, j, k, s;

	if (!X || !Y || !Z)
		fprintf(stderr, "!W matrixMatrix: matrix not allocated\n");
	else {
		for (i=0; i < n; i++) {
			for (j=0; j < p; j++) {
				s = 0;
				for (k=0; k < m; k++)
					s += X[i][k]*Y[k][j];
				Z[i][j] = s;
			}
		}
	}
	return;
}

void randMatrix (int **X, int n, int m, int a, int b) { //debugged
	int i;
	
	if (!X)
		fprintf(stderr, "!W randMatrix: matrix not allocated\n");
	else {
		for (i=0; i<n; i++)
			randVector(X[i], m, a, b);
	}
	return;
}

void scalarMatrix (int **X, int **Y, int n, int m, int k) { //debugged
	int i;

	if (!X || !Y)
		fprintf(stderr, "!W scalarMatrix: matrix not allocated\n");
	else {
		for (i=0; i < n; i++)
			scalarVector(X[i], Y[i], m, k);
	}
	return;
}

void sumMatrices (int **X, int **Y, int **Z, int n, int m) { //debugged
	int i;

	if (!X || !Y || !Z)
		fprintf(stderr, "!W sumMatrices: matrix not allocated\n");
	else {
		for (i=0; i<n; i++)
			sumVectors(X[i], Y[i], Z[i], m);
	}
	return;
}

void swapRows (int **X, int k, int h) { //debugged
	int *A;

	if (!X)
		fprintf(stderr, "!W swapRows: matrix not allocated\n");
	else {
		A = X[k];
		X[k] = X[h];
		X[h] = A;
	}
	return;
}

void transposeMatrix (int **X, int **Y, int n, int m) { //debugged
	int i, j;

	if (!X || !Y)
		fprintf(stderr, "!W transposeMatrix: matrix not allocated\n");
	else {
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++)
				Y[j][i] = X[i][j];
		}
	}
	return;
}