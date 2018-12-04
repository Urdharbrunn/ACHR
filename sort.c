/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for sort algorithms on vectors
**
** first created 	03/12/2018 (with older materials)
** version 0			
** last updated		03/12/2018
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void bubbleSort (int *X, int n) { //debugged
	int flag, i;

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
	if (2*i == H[0] && H[i] < H[2*1])
		swap(&H[i], &H[2*i]);
	return (m);
}
	
int heapSort (int *X, int n) { //debugged
	int *H = malloc(sizeof(int)*n), i, flag = 0;
	if (!H)
		fprintf (stderr, "!E heapSort: memory allocation error\n");
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

void insertHeap (int *H, int x) { //debugged
	int i = H[0];
	H[i] = x;
	while ( i>1 && H[i] > H[i/2] ) {
		swap(&H[i], &H[i/2]);
		i = i/2;
	}
	H[0]++;
	return;
}

void insertionSort (int *X, int n) { //debugged
	int i, j, x;
	for (i=1; i<n; i++) {
		x = X[i];
		j = i-1;
		while (j>=0 && X[j] > x) {
			X[j+1] = X[j];
			j--;
		}
		X[j+1] = x;
	}
	return;
}

void insertionSortPriority(int *X, int *P, int n) { //debugged
	int i, j, p, x;
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
	while (n) {
		max = 0;
		for (i=0; i < n; i++) {
			if (X[i] > X[max])
				max = i;
		}
		swap(&X[n-1], &X[max]);
		n--;
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