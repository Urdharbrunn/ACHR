/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for duples of integers
**
** first created 	31/01/2019 (with older materials)
** version 0			
** last updated		31/01/2019
**
** function count -> 14
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdio.h>
#include <stdlib.h>
#include "duple.h"

duple *allocateDupleHeap (int n) { //debugged

	return (allocateDupleVector(n+1));
}

duple *allocateDupleVector (int n) { //debugged
	duple *X = NULL;

	if (n < 0)
		fprintf(stderr, "!E allocateHeapVector: requested negative memory allocation\n");
	else
		X = malloc(sizeof(duple)*n);
	if (!X)
		fprintf (stderr, "!E allocateHeapVector: memory allocation error\n");
	fflush(stderr);
	return(X);

}

void copyDupleVector (duple *H, duple *K, int n) { //debugged
	int i;

	if (!H || !K)
		fprintf(stderr, "!W copyDupleVector: duple does not exist\n");
	else {
		for (i=0; i<n; i++)
			K[i] = H[i];
	}
	return;
}

void deleteDupleVector (duple *H) { //debugged
	if (H)
		free(H);
	else
		fprintf(stderr, "!W deleteDupleVector: requested NULL pointer deallocation\n");
	return;
}

void dupleToVectors (duple *H, int *X, int *P, int n) { //debugged
	int i;
	if (!H)
		fprintf(stderr, "!W dupleToVectors: duple does not exist\n");
	else if (!X || !P)
		fprintf(stderr, "!W dupleToVectors: vectors are not allocated\n");
	else {
		for (i=0; i<n; i++) {
			X[i] = H[i].x;
			P[i] = H[i].p;
		}
	}
	return;
}

void exportDupleVector (FILE *out, duple *H, int n) { //debugged
	int i;

	if (!out)
		fprintf(out, "!W exportDupleVector: file not opened\n");
	else if (!H)
		fprintf(stderr, "!W exportDupleVector: vector does not exist\n");
	for (i=0; i<n; i++)
		fprintf(out, "%d\t", H[i].x);
	fprintf(out, "\n");
	for (i=0; i<n; i++)
		fprintf(out, "%d\t", H[i].p);
	fprintf(out, "\n");
	return;
}

duple extractDupleHeap (duple *H, duple *D) { //debugged
	int i = H[0].p - 1;
	duple m = H[1]; // stores root element
	H[1] = H[i]; // copy last element as root
	H[0].p --; // decreses size of heap
	i = 1;

	//descends the root to its right place
	while ( 2*i < H[0].p && ( H[i].p < H[2*i].p || H[i].p < H[2*i+1].p ) ) {
		if ( H[2*i].p > H[2*i+1].p ){
			swapDuple(&H[i], &H[2*i]);
			i = 2*i;
		}
		else {
			swapDuple(&H[i], &H[2*i+1]);
			i = 2*i+1;
		}
	}
	if (2*i == H[0].p && H[i].p < H[2*i].p)
		swapDuple(&H[i], &H[2*i]);
	return (m);
}

void importDupleVector (FILE *in, duple *H, int n) { //debugged
	int i;

	if (!in)
		fprintf(stderr, "!W importDupleVector: file not opened\n");
	else if (!H)
		fprintf(stderr, "!W importDupleVector: vector is not allocated\n");
	else {
		for (i=0; i<n; i++)
			fscanf(in, "%d %d", &H[i].x, &H[i].p);
	}
	return;
}

void insertDupleHeap (duple *H, duple *D, int x) { //debugged
	int i = H[0].p;
	H[i] = D[x];
	while (i>1 && H[i].p > H[i/2].p ) {
		swapDuple(&H[i], &H[i/2]);
		i = i/2;
	}
	H[0].p++; //increase first free position
	return;
}

void initializeDupleHeap (duple *H, duple *D, int n) { //debugged
	int i;
	H[0].p = 1; //first free position
	H[0].x = 0; //this has no use
	for (i=0; i<n; i++)
		insertDupleHeap(H, D, i);
	return;
}

void randDupleVector (duple *H, int n, int a, int b, int c, int d) { //debugged
	int i;
	for (i=0; i<n; i++) {
		H[i].x = (rand()%(b-a+1)) + a;
		H[i].p = (rand()%(d-c+1)) + c;
	}
	return;
}

void swapDuple (duple *a, duple *b) { //debugged
	if (a != b) {
		duple t;
		t = *a;
		*a = *b;
		*b = t;
	}
	return;
}

void updateDupleHeap (duple *H, int i) { //debugged

	if (!H)
		fprintf(stderr, "!W updateHeap: heap not allocated\n");
	else {
		// ascends the element
		while (i>1 && H[i].p > H[i/2].p ) {
			swapDuple(&H[i], &H[i/2]);
			i = i/2;
		}

		// descends the element
		while ( 2*i < H[0].p && ( H[i].p < H[2*i].p || H[i].p < H[2*i+1].p ) ) {
			if ( H[2*i].p > H[2*i+1].p ){
				swapDuple(&H[i], &H[2*i]);
				i = 2*i;
			}
			else {
				swapDuple(&H[i], &H[2*i+1]);
				i = 2*i+1;
			}
		}
		if (2*i == H[0].p && H[i].p < H[2*i].p)
			swapDuple(&H[i], &H[2*i]);
	}

	return;
}

void vectorsToDuple (duple *H, int *X, int *P, int n) { //debugged
	int i;

	for (i=0; i<n; i++) {
		H[i].x = X[i];
		H[i].p = P[i];
	}
	return;
}