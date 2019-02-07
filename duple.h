/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** header for duples of integers
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

/*
 * structure for duples of integers
 */
typedef struct xduple {
	int x;
	int p;
} duple;

/*
 * allocates a duple's heap for n elements
 * returns pointer to first element or NULL
 */
duple *allocateDupleHeap (int n);

/*
 * allocates a vector of n duples
 * returns pointer to first element or NULL
 */
duple *allocateDupleVector (int n);

/*
 * copies vector H in K
 * K has to be already allocated
 */
void copyDupleVector (duple *H, duple *K, int n);

/*
 * frees memory of H
 */
void deleteDupleVector (duple *H);

/*
 * converts duple H in vectors X and P
 * vectors must be allocated
 */
void dupleToVectors (duple *H, int *X, int *P, int n);

/*
 * exports the duple H on file out
 * note: file must be already opened
 */
void exportDupleVector (FILE *out, duple *H, int n);

/*
 * extracts the first element of the heap
 * updates the heap
 * returns the extracted value D
 */
duple extractDupleHeap (duple *H, duple *D);

/*
 * imports a duple vector of n elements from in file
 * format presents in turn each element
 */
void importDupleVector (FILE *in, duple *H, int n);

/*
 * creates in H an heap with elements of D
 * uses D.p as priority
 */
void initializeDupleHeap (duple *H, duple *D, int n);

/*
 * inserts the element D[x] in the heap H
 */
void insertDupleHeap (duple *H, duple *D, int x);

/*
 * generates a random duple vector with element in (a,b) for x and (c,d) for p
 */
void randDupleVector (duple *H, int n, int a, int b, int c, int d);

/*
 * swaps duple in a and b if they are different
 */
void swapDuple (duple *a, duple *b);

/*
 * updates the heap H adjusting the position of i-th element
 */
void updateDupleHeap (duple *H, int i);

/*
 * create a duple with vector X e P of length n
 */
void vectorsToDuple (duple *H, int *X, int *P, int n);