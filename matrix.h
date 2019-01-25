/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** header for matrix related function
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

/*
 * allocates a matrix of integer with n rows and m column
 * returns pointer to matrix, NULL if failed
 */
int **allocateMatrix (int n, int m);

/*
 * copies the int matrix A into B of dimension (n,m)
 * returns 0 if A or B are not allocated
 */
int copyMatrix (int **A, int **B, int n, int m);

/*
 * deallocates the matrix X and its rows, if they has been allocated
 */
void deleteMatrix (int **X, int n);

/*
 * exports the int matrix X of dimension (n,m) in output file
 * matrix is printed calling exportVector on rows
 * note: file must already be opened
 */
void exportMatrix (FILE *output, int **X, int n, int m);

/*
 * export the int submatrix of X of dimension (p,q) starting from position (k,h) in output file
 * is printed calling exportVector on rows
 * note: file must be opened
 */
void exportSubMatrix (FILE *output, int **X, int k, int h, int p, int q);

/*
 * imports from input file nm integer ordered in matrix X
 * returns 0 if file is not opened or matrix not allocated
 * note: file must already be opened and matrix initialized
 */
int importMatrix (FILE *input, int **X, int n, int m);

/*
 * initializes the matrix X of n rows m column to a
 */
int initializeMatrix (int **X, int n, int m, int a);

/*
 * calculate Z = aX + bY, matrices of dimensions (n,m)
 * returns 0 if matrix is not allocated
 */
int linearMatrices (int **X, int **Y, int **Z, int n, int m, int a, int b);

/*
 * multiplies Z = XY, where X has dimensions (n,m) and Y (m,p)
 */
void matrixMatrix (int **X, int **Y, int **Z, int n, int m, int p);

/*
 * multiplies P = XB, where X is a matrices of dimensions (n,m) and B a vector of length m
 */
void matrixVector (int **X, int *B, int *P, int n, int m);

/*
 * creates a random int matrix in X, dimensions (n,m), with numbers in [a,b]
 * note: srand must already be initialized
 */
void randMatrix (int **X, int n, int m, int a, int b);

/*
 * multiplies Y = kX, matrices of dimensions (n,m)
 */
void scalarMatrix (int **X, int **Y, int n, int m, int k);

/*
 * sums Z = X + Y, matrices with n rows and m column
 */
void sumMatrices (int **X, int **Y, int **Z, int n, int m);

/*
 * swamps the rows k and h of the matrix X
 */
void swapRows (int **X, int k, int h);

/*
 * transposes matrix X of dimension (n,m) in Y
 * note: be sure Y has dimensions (m,n)
 */
void transposeMatrix (int **X, int **Y, int n, int m);