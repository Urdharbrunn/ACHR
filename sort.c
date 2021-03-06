/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for sort algorithms on vectors
** requires duple.h
**
** first created 	03/12/2018 (with older materials)
** version 0			03/12/2018
** last updated		31/01/2019
**
** function count -> 19
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "duple.h"

void bubbleSort (int *X, int n) { //debugged
	int flag, i;

	if (!X)
		fprintf(stderr, "!W bubbleSort: array not allocated\n");
	else {
		do {
			flag = 0;
			for (i=0; i < n; i++) {
				if (X[i] > X[i+1]) {
					swap(&X[i], &X[i+1]);
					flag = 1;
				}
			}
			n--;
		} while (flag);
	}
	return;
}

int extractHeap (int *H) { //debugged
	int i = H[0]-1, m = H[1];
	H[1] = H[i];
	H[0]--;
	i = 1;
	while ( 2*i < H[0] && ( H[i] < H[2*i] || H[i] < H[2*i+1] ) ) {
		if ( H[2*i] > H[2*i+1] ){
			swap(&H[i], &H[2*i]);
			i = 2*i;
		}
		else {
			swap(&H[i], &H[2*i+1]);
			i = 2*i+1;
		}
	}
	if (2*i == H[0] && H[i] < H[2*i])
		swap(&H[i], &H[2*i]);
	return (m);
}

int heapSort (int *X, int n) { //debugged
	int *H = NULL, i, flag = 0;
	H = malloc(sizeof(int)*n);
	if (!H)
		fprintf (stderr, "!E heapSort: memory allocation error\n");
	else if (!X)
		fprintf(stderr, "!W bubbleSort: array not allocated\n");
	else {
		flag = 1;
		H[0] = 1;
		for (i=0; i<n; i++)
			insertHeap(H,X[i]);
		for (i=n-1; i>=0; i--)
			X[i] = extractHeap(H);
		free(H);
	}
	return (flag);
}

int heapSortPriority (int *X, int *P, int n) { //debugged
	int i = 0;
	duple *D = NULL, *H = NULL, flag;
	D = malloc(sizeof(duple)*n), H = allocateDupleHeap(n);
	if (!H || !D)
		fprintf (stderr, "!E heapSortPriority: memory allocation error\n");
	else if (!X || !P)
		fprintf(stderr, "!W heapSortPriority: array not allocated\n");
	else {

		//initializes the duples with elements to sort and priorities
		//mergeVectors(D, X, P);
		for (i=0; i<n; i++) {
			D[i].x = X[i];
			D[i].p = P[i];
		}

		initializeDupleHeap(H, D, n);

		for (i=n-1; i>=0; i--) {
			flag = extractDupleHeap(H, D);
			X[i] = flag.x;
			P[i] = flag.p;
		}
		free(H);
		free(D);
		i = 1;
	}
	return (i);
}

void insertHeap (int *H, int x) { //debugged
	int i = H[0];
	H[i] = x;
	while (i>1 && H[i] > H[i/2] ) {
		swap(&H[i], &H[i/2]);
		i = i/2;
	}
	H[0]++;
	return;
}

void insertionSort (int *X, int n) { //debugged
	int i, j, x;
	if (!X)
		fprintf(stderr, "!W insertionSort: array not allocated\n");
	else {
		for (i=1; i<n; i++) {
			x = X[i];
			j = i-1;
			while (j>=0 && X[j] > x) {
				X[j+1] = X[j];
				j--;
			}
			X[j+1] = x;
		}
	}
	return;
}

void insertionSortPriority(int *X, int *P, int n) { //debugged
	int i, j, p, x;
	if (!X || !P)
		fprintf(stderr, "!W bubbleSort: array not allocated\n");
	else {
		for (i=1; i<n; i++) {
			p = P[i];
			x = X[i];
			j = i-1;
			while (j>=0 && P[j] > p) {
				P[j+1] = P[j];
				X[j+1] = X[j];
				j--;
			}
			P[j+1] = p;
			X[j+1] = x;
		}
	}
	return;
}

int medianOfThree (int *X, int k, int n) { //debugged
	int m = (k+n) / 2;
	if (X[m] < X[k])
		swap(&X[k], &X[m]);
	if (X[n] < X[k])
		swap(&X[n], &X[k]);
	if (X[m] < X[n])
		swap(&X[m], &X[n]);
	return (X[n]);
}

int medianOfThreePriority (int *X, int *P, int k, int n) { //debugged
	int m = (k+n) / 2;
	if (P[m] < P[k]) {
		swap(&P[k], &P[m]);
		swap(&X[k], &X[m]);
	}
	if (P[n] < P[k]) {
		swap(&P[n], &P[k]);
		swap(&X[n], &X[k]);
	}
	if (P[m] < P[n]) {
		swap(&P[m], &P[n]);
		swap(&X[m], &X[n]);
	}
	return (P[n]);
}

int merge (int *X, int p, int q, int r) { //debugged
	int i = p, j = q + 1, k = 0, *C = NULL, flag = 0;
	C = malloc(sizeof(int)*(r-p));
	if (!C)
		fprintf (stderr, "!E merge: memory allocation error\n");
	else {
		flag = 1;
		while (i <= q && j < r) {
			if (X[i] < X[j]) {
				C[k] = X[i];
				i++;
			} else {
					C[k] = X[j];
					j++;
				}
			k++;
		}
		while (i <= q) {
			C[k] = X[i];
			k++;
			i++;
		}
		while (j < r) {
			C[k] = X[j];
			k++;
			j++;
		}
		for (k=p; k < r; k++)
			X[k] = C[k-p];
	}
	free(C);
	return(flag);
}

int mergePriority (int *X, int *P, int p, int q, int r) {
	int i = p, j = q + 1, k = 0, *C = NULL, flag = 0, *B = NULL;
	C = malloc(sizeof(int)*(r-p));
	B = malloc(sizeof(int)*(r-p));
	if (!C || ! B)
		fprintf (stderr, "!E mergePriority: memory allocation error\n");
	else {
		flag = 1;
		while (i <= q && j < r) {
			if (P[i] < P[j]) {
				C[k] = X[i];
				B[k] = P[i];
				i++;
			} else {
				C[k] = X[j];
				B[k] = P[j];
				j++;
			}
			k++;
		}
		while (i <= q) {
			C[k] = X[i];
			B[k] = P[i];
			k++;
			i++;
		}
		while (j < r) {
			C[k] = X[j];
			B[k] = P[j];
			k++;
			j++;
		}
		for (k=p; k < r; k++) {
			X[k] = C[k-p];
			P[k] = B[k-p];
		}
	}
	return(flag);
}

int mergeSort (int *X, int p, int r) { //debugged
	int q, flag = 1;
	if (p < r) {
		q = (p + r) / 2;
		flag = mergeSort(X, p, q);
		if (flag)
			flag = mergeSort(X, q + 1, r);
		if (flag)
			flag = merge(X, p, q, r+1);
	}
	return (flag);
}

int mergeSortPriority (int *X, int *P, int p, int r) { //debugged
	int q, flag = 1;
	if (p < r) {
		q = (p + r) / 2;
		flag = mergeSortPriority(X, P, p, q);
		if (flag)
			flag = mergeSortPriority(X, P, q + 1, r);
		if (flag)
			flag = mergePriority(X, P, p, q, r+1);
	}
	return (flag);
}

int pivoting (int *X, int k, int n) { //debugged
	int p, j;
	p = medianOfThree(X, k, n); //selects pivot
	for (j=k; j < n; j++) {
		if (X[j] < p) {
			swap(&X[k], &X[j]);
			k++;
		}
	}
	swap(&X[k], &X[n]);
	return(k);
}

int pivotingPriority (int *X, int *P, int k, int n) { //debugged
	int p, j;
	p = medianOfThreePriority(X, P, k, n); //selects pivot
	for (j=k; j < n; j++) {
		if (P[j] < p) {
			swap(&X[k], &X[j]);
			swap(&P[k], &P[j]);
			k++;
		}
	}
	swap(&X[k], &X[n]);
	swap(&P[k], &P[n]);
	return(k);
}

void quickSort (int *X, int k, int n) { //debugged
	if (k < n) {
		int p = pivoting(X, k, n-1);
		quickSort(X, k, p);
		quickSort(X, p+1, n);
	}
	return;
}

void quickSortPriority (int *X, int *P, int k, int n) { //debugged
	if (k < n) {
		int p = pivotingPriority(X, P, k, n-1);
		quickSortPriority(X, P, k, p);
		quickSortPriority(X, P, p+1, n);
	}
	return;
}

void selectionSort (int *X, int n) { //debugged
	int i, max;
	if (!X)
		fprintf(stderr, "!W bubbleSort: array not allocated\n");
	else {
		while (n) {
			max = 0;
			for (i=0; i < n; i++) {
				if (X[i] > X[max])
					max = i;
			}
			swap(&X[n-1], &X[max]);
			n--;
		}
	}
	return;
}

void swap (int *a, int *b) { //debugged
	if (a != b) {
		int t;
		t = *a;
		*a = *b;
		*b = t;
	}
	return;
}