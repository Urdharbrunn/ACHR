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
** last updated		08/01/2019
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
//function count -> 24
int addEdge (graph *G, int u, int v);
component *allocateComponent (int k);
graph *allocateGraph (void);
int BFS (graph *G, int s, int *D, int *P, int doComponent);
int BFSComponents (graph *G);
int *BFSDistance (graph *G, int s);
int *BFSTree (graph *G, int s);
void deleteComponentList (component *list);
int deleteEdge (graph *G, int u, int v);
void deleteGraph (graph *G);
void deleteNode (graph *G, int u);
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
node *copyListRecursive (node *list);
node *deleteList (node *list);
void deleteNodeNext (node *p);
void exportList (node *list, FILE *out);
void exportListTerminator (node *list, FILE *out);
node *goToLast (node *list);
node *importQueue (queue *Q, int n, FILE *input);
node *importStack (int n, FILE *input);
void insertNode (node *p, node *q);
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

//sort.h
// function count -> 15
void bubbleSort (int *X, int n);
int extractHeap (int *H);
int extractHeapSorting (int *H, int *P);
int heapSort (int *X, int n);
void insertHeap (int *H, int x);
void insertionSort (int *X, int n);
void insertionSortPriority(int *X, int *P, int n);
int medianOfThree (int *X, int k, int n);
int medianOfThreePriority (int *X, int *P, int k, int n);
int pivoting (int *X, int k, int n);
int pivotingPriority (int *X, int *P, int k, int n);
void quickSort (int *X, int k, int n);
void quickSortPriority (int *X, int *P, int k, int n);
void selectionSort (int *X, int n);
void swap (int *a, int *b);

//vector.h
// function count -> 31
int **allocateMatrix (int n, int m);
int *allocateVector (int n);
void copyMatrix (int **A, int **B, int n, int m);
void copyVector (int *A, int *B, int n);
void deleteMatrix (int **X, int n);
void deleteVector (int *X);
void exportMatrix (FILE *output, int **X, int n, int m);
void exportReverseVector(FILE *output, int *A, int n);
void exportSubMatrix (FILE *output, int **X, int k, int h, int p, int q);
void exportVector (FILE *output, int *A, int n);
void importMatrix (FILE *input, int **X, int n, int m);
void importVector (FILE *input, int *A, int n);
void initializeMatrix (int **X, int n, int m, int a);
void initializeVector (int *X, int n, int a);
void linearMatrices (int **X, int **Y, int **Z, int n, int m, int a, int b);
void linearVectors (int *V, int *W, int *Z, int n, int a, int b);
void matrixMatrix (int **X, int **Y, int **Z, int n, int m, int p);
void matrixVector (int **X, int *B, int *P, int n, int m);
int maxVector (int *X, int n);
int minVector (int *X, int n);
void randMatrix (int **X, int n, int m, int a, int b);
void randVector (int *A, int n, int a, int b);
void scalarMatrix (int **X, int **Y, int n, int m, int k);
void scalarVector (int *V, int *W, int n, int k);
void sumMatrices (int **X, int **Y, int **Z, int n, int m);
void sumVectors (int *A, int *B, int *S, int n);
void swapRows (int **X, int k, int h);
void transposeMatrix (int **X, int **Y, int n, int m);
double vectorMean (int *V, int n);
int vectorVector (int *A, int *B, int n);