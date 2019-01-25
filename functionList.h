/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** this file contains a list in alphabetical order grouped by library
** of function interfaces and type definitions for all the ACHR project
**
** at the current state this does include:
**
** algebra.h
** graph.h
** list.h
** sort.h
** vector.h
**
** first created	07/12/2018 (with older materials)
** version 0			07/12/2018
** last updated		25/01/2019
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

typedef struct xnode {
  int info;
  struct xnode *next;
} node;

typedef struct xcomponent {
	int info;
	int size;
	node *vertex;
	struct component *next;
} component;

typedef struct xqueue {
  node *first;
  node *last;
} queue;

typedef struct xgraph {
	int n;
	node **V;
	int **A;
	component *C;
} graph;

typedef struct xfactor {
	int base;
	int power;
	struct xfactor *next;
} factor;

typedef struct xsieve {
	int info;
	struct xsieve *next;
} sieve;

typedef struct xduple {
	int x;
	int p;
} duple;

//algebra.h
	//function count -> 17
	int baseToTen (int *A, int b, int n);
	int bezout (int a, int b, int *l, int *m);
	int divide (int a, int b);
	int esp (int a, int n);
	int eulerFunction (factor *p);
	void exportFactorization (FILE *out, factor *f);
	void exportSieve (FILE *out, sieve *s);
	factor *factorize (int n, sieve *S);
	int GCD (int a, int b);
	sieve *hasDivisors (int n, sieve *S);
	sieve *initializeSieve (int n);
	int isPrime (int n);
	int intLOG(int a, int b);
	int intSQRT (int a);
	int lcm (int a, int b);
	int lengthInBase (int x, int b);
	int tenToBase (int x, int b, int *A);

//algorithm.h
	//function count -> 0

//graph.h
	//function count -> 25
	int addEdge (graph *G, int u, int v);
	int addEdgeMatrix(graph *G, int u, int v);
	component *allocateComponent (int k);
	graph *allocateGraph (void);
	int BFS (graph *G, int s, int *D, int *P, int doComponent);
	int BFSComponents (graph *G);
	int *BFSDistance (graph *G, int s);
	int *BFSTree (graph *G, int s);
	void deleteComponentList (component *list);
	int deleteEdge (graph *G, int u, int v);
	void deleteGraph (graph *G);
	int deleteNode (graph *G, int u);
	void exportComponent (FILE *out, component *list);
	void exportGraph (FILE *out, graph *G);
	void exportGraphComplete (FILE *out, graph *G);
	void exportGraphTerminator (graph *G, FILE *out);
	void graphToMatrix (graph *G, int **A);
	int importGraph (FILE *input, graph *G);
	int importGraphTerminator (FILE *input, graph *G);
	int initializeGraph (graph *G, int n);
	int mathExportGraph (graph *G, char name[]);
	int matrixToGraph (int **A, graph *G);
	int randomGraph48 (graph *G, double p);
	int randomDigraph48 (graph *G, double p);
	int transposeGraph (graph *G, graph *GT);

//list.h
	//function count -> 21
	queue *allocateQueue (void);
	node* copyNode (node *p);
	node *copyList (node *list);
	node *deleteList (node *list);
	void deleteNodeNext (node *p);
	void exportList (FILE *out, node *list);
	void exportListTerminator (FILE *out, node *list);
	node *goToLast (node *list);
	node *importQueue (FILE *input, queue *Q, int n);
	node *importStack (FILE *input, int n);
	int insertNode (node *p, node *q);
	node *invertList (node *list);
	int listLength (node *list);
	int pop (queue *Q);
	int push (queue *Q, int x);
	node *randomList (int n, int a, int b);
	node *search (node *list, int k);
	node *searchDelete (node *list, int k);
	node *searchDeleteAll (node *list, int k);
	node *searchNext (node *list, int k);
	node *stack (node *list, int x);

//matrix.h
	//function count -> 15
	int **allocateMatrix (int n, int m);
	int copyMatrix (int **A, int **B, int n, int m);
	void deleteMatrix (int **X, int n);
	void exportMatrix (FILE *output, int **X, int n, int m);
	void exportSubMatrix (FILE *output, int **X, int k, int h, int p, int q);
	int importMatrix (FILE *input, int **X, int n, int m);
	int initializeMatrix (int **X, int n, int m, int a);
	int linearMatrices (int **X, int **Y, int **Z, int n, int m, int a, int b);
	void matrixMatrix (int **X, int **Y, int **Z, int n, int m, int p);
	void matrixVector (int **X, int *B, int *P, int n, int m);
	void randMatrix (int **X, int n, int m, int a, int b);
	void scalarMatrix (int **X, int **Y, int n, int m, int k);
	void sumMatrices (int **X, int **Y, int **Z, int n, int m);
	void swapRows (int **X, int k, int h);
	void transposeMatrix (int **X, int **Y, int n, int m);

//sort.h
	// function count -> 22
	void bubbleSort (int *X, int n);
	int extractHeap (int *H);
	duple extractHeapPriority (duple *H, duple *D);
	int heapSort (int *X, int n);
	void heapSortPriority (int *X, int *P, int n);
	void insertHeap (int *H, int x);
	void insertHeapPriority (duple *H, duple *D, int x);
	void insertionSort (int *X, int n);
	void insertionSortPriority(int *X, int *P, int n);
	int medianOfThree (int *X, int k, int n);
	int medianOfThreePriority (int *X, int *P, int k, int n);
	int merge (int *X, int p, int q, int r);
	int mergePriority (int *X, int *P, int p, int q, int r);
	int mergeSort (int *X, int p, int r);
	int mergeSortPriority (int *X, int *P, int p, int r);
	int pivoting (int *X, int k, int n);
	int pivotingPriority (int *X, int *P, int k, int n);
	void quickSort (int *X, int k, int n);
	void quickSortPriority (int *X, int *P, int k, int n);
	void selectionSort (int *X, int n);
	void swap (int *a, int *b);
	void swapDuple (duple *a, duple *b);

//vector.h
	// function count -> 15
	int *allocateVector (int n);
	int copyVector (int *A, int *B, int n);
	void deleteVector (int *X);
	void exportReverseVector(FILE *output, int *A, int n);
	void exportVector (FILE *output, int *A, int n);
	int importVector (FILE *input, int *A, int n);
	int initializeVector (int *X, int n, int a);
	int linearVectors (int *V, int *W, int *Z, int n, int a, int b);
	int maxVector (int *X, int n);
	int minVector (int *X, int n);
	void randVector (int *A, int n, int a, int b);
	void scalarVector (int *V, int *W, int n, int k);
	void sumVectors (int *A, int *B, int *S, int n);
	double vectorMean (int *V, int n);
	int vectorVector (int *A, int *B, int n);