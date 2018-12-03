/*
** source for vector related function
** vector starts from 0 index
** as a rule, in function names type is omitted if integer
** it should be allocateIntVector, allocateDoubleVector, etc
**
** first created	26/10/2018 (with older materials)
** version 0			29/10/2018
** last updated		26/11/2018
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

/*
 * allocates a matrix of integer with n rows and m column
 */
int **allocateMatrix (int n, int m);

/*
 * allocates a block of n int for a vector
 */
int *allocateVector (int n);

/*
 *  copies the int matrix A into B of dimension (n,m)
 */
void copyMatrix (int **A, int **B, int n, int m);

/*
 *  copies the int vector A into B of length n
 */
void copyVector (int *A, int *B, int n);

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
 * exports the int vector A of length n in output file
 * vector is printed on a single line, followed by newline
 * note: file must already be opened
 */
void exportVector (FILE *output, int *A, int n);

/*
 + deallocates the matrix X and its rows, if they has been allocated
 */
int **freeMatrix (int **X, int n);

/*
 * deallocates the vector X, if it has been allocated
 */
int *freeVector (int *X);

/*
 * imports from input file nm integer ordered in matrix X
 * note: file must already be opened and matrix initialized
 */
void importMatrix (FILE *input, int **X, int n, int m);

/*
 * imports from input file n integer in vector A
 * note: file must already be opened and vector initialized
 */
void importVector (FILE *input, int *A, int n);

/*
 * initializes the matrix X of n rows m column to 0
 */
void initializeMatrix (int **X, int n, int m);

/*
 * initializes the vector X of length n to 0
 */
void initializeVector (int *X, int n);

/*
 * calculate Z = aX + bY, matrices of dimensions (n,m)
 */
void linearMatrices (int **X, int **Y, int **Z, int n, int m, int a, int b);

/*
 * calculate Z = aV + bW, vectors of length n
 */
void linearVectors (int *V, int *W, int *Z, int n, int a, int b);

/*
 * multiplies Z = XY, where X has dimensions (n,m) and Y (m,p)
 */
void matrixMatrix (int **X, int **Y, int **Z, int n, int m, int p);

/*
 * multiplies Z = XY, where X has dimensions (n,m) and Y (m,p)
 * this is done by transposing Y and multipling on the rows, so requires RAM
 * returns 0 if failed to allocate transpose matrix, else Z's columns number
 */
int matrixMatrixPlus (int **X, int **Y, int **Z, int n, int m, int p);

/*
 * multiplies P = XB, where X is a matrices of dimensions (n,m) and B a vector of length m
 */
void matrixVector (int **X, int *B, int *P, int n, int m);

/*
 * return the index of maximum of vector X of length n
 */
int maxVector (int *X, int n);

/*
 * return the index of minimum of vector X of length n
 */
int minVector (int *X, int n);

/*
 * creates a random int matrix in X, dimensions (n,m), with numbers in [a,b]
 * note: srand must already be initialized
 */
void randMatrix (int **X, int n, int m, int a, int b);

/*
 * creates a random int vector in A, length n, with numbers in [a,b]
 * note: srand must already be initialized
 */
void randVector (int *A, int n, int a, int b);

/*
 * multiplies Y = kX, matrices of dimensions (n,m)
 */
void scalarMatrix (int **X, int **Y, int n, int m, int k);

/*
 * multiplies W = kV, vectors of length n
 */
void scalarVector (int *V, int *W, int n, int k);

/*
 * sums Z = X + Y, matrices with n rows and m column
 */
void sumMatrices (int **X, int **Y, int **Z, int n, int m);

/*
 * if flag = 1, sums C = A + B, vectors of length n
 */
void sumVectors (int *A, int *B, int *S, int n);

/*
 * swamps the rows k and h of the matrix X
 */
void swapRows (int **X, int k, int h);

/*
 * transposes matrix X of dimension (n,m) in Y
 * note: be sure Y has dimensions (m,n)
 */
void transposeMatrix (int **X, int **Y, int n, int m);

/*
 * returns the scalar product AB, vectors of length n
 */
int vectorVector (int *A, int *B, int n);
