/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** header for sort algorithms on vectors
**
** first created 	03/12/2018 (with older materials)
** version 0			03/12/2018
** last updated		11/01/2019
**
** function count -> 16
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

/*
 * applies bubble sort
 * slightly optimized decreasing n at each iteration
 */
void bubbleSort (int *X, int n);

/*
 * extracts the first element of the heap
 * updates the heap
 * returns the extracted value
 */
int extractHeap (int *H);

/*
 * applies heap sort
 * returns 0 if failed to allocate the heap
 */
int heapSort (int *X, int n);

/*
 *inserts an element in the heap
 */
void insertHeap (int *H, int x);

/*
 * applies insertion sort
 * slightly optimized by adding a variable used to make less swaps
 */
void insertionSort (int *X, int n);

/*
 * applies insertion sort to X, ordering elements according to P
 * X_i < X_j iff P_i < P_j
 */
void insertionSortPriority(int *X, int *P, int n);

/*
 * selects the pivot for quick sort by preordering the 3 element 
 * X[k] < X[m] < X[n], where m is the mean
 */
int medianOfThree (int *X, int k, int n);

/*
 * selects the pivot for quick sort by preordering the 3 element 
 * X[k] < X[m] < X[n], where m is the mean (k+n)/2
 * this is for the priority version, so works on P and X simoultaneously
 */
int medianOfThreePriority (int *X, int *P, int k, int n);

/*
 * does the merge part of merge sort
 * returns 0 on allocation error, 1 otherwise
 */
int merge (int *X, int p, int q, int r);

/*
 * applies merge sort
 * first call si mergeSort(X, 0, length(X))
 * depends on merge function
 * returns 0 if merge failed to allocate memory
 */
int mergeSort (int *X, int p, int r);

/*
 * applies the pivoting to subvector k->n-1 of X using Lomuto's scheme
 * this degrades quickSort to O(n^2)
 * pivot is selected as last element X[n-1]
 */
int pivoting (int *X, int k, int n);

/*
 * applies the pivoting to subvector k->n-1 of P using Lomuto's scheme
 * this degrades quickSort to O(n^2)
 * pivot is selected as last element P[n-1]
 * this is for the priority version, so works on P and X simoultaneously
 */
int pivotingPriority (int *X, int *P, int k, int n);

/*
 * applies quick sort
 * first call is quickSort(X, 0, length(X))
 * this calls pivoting(X, k, n)
 * slightly optimized with lomuto with median of three pivoting
 */
void quickSort (int *X, int k, int n);

/*
 * applies quick sort
 * first call is quickSortPriority(X, 0, length(X))
 * this calls pivotingPriority(X, k, n)
 * slightly optimized with lomuto with median of three pivoting
 */
void quickSortPriority (int *X, int *P, int k, int n);

/*
 * applies selection sort
 */
void selectionSort (int *X, int n);

/*
 * swaps elements in a and b if they are different
 */
void swap (int *a, int *b);