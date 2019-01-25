/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for vector related function
** vector starts from 0 index
** as a rule, in function names type is omitted if integer
** it should be allocateIntVector, allocateDoubleVector, etc
**
** first created	26/10/2018 (with older materials)
** version 0			29/10/2018
** last updated		25/01/2019
**
** function count -> 15
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

/*
 * allocates a block of n int for a vector
 * returns pointer to vector, NULL if failed
 */
int *allocateVector (int n);

/*
 * copies the int vector A into B of length n
 * returns 0 if A or B are not allocated
 */
int copyVector (int *A, int *B, int n);

/*
 * deallocates the vector X, if it has been allocated
 */
void deleteVector (int *X);

/*
 * exports the int vector A of length n in output file
 * vector is printed on a single line, followed by newline
 * note: file must already be opened
 */
void exportVector (FILE *output, int *A, int n);

/*
 * exports the int vector A of length n in output file
 * A is printed from last element to first on a single line
 * note: file must already be opened
 */
void exportReverseVector(FILE *output, int *A, int n);

/*
 * imports from input file n integer in vector A
 * returns 0 if file is not opened or vector not allocated
 * note: file must already be opened and vector initialized
 */
int importVector (FILE *input, int *A, int n);

/*
 * initializes the vector X of length n to a
 */
int initializeVector (int *X, int n, int a);

/*
 * calculate Z = aV + bW, vectors of length n
 * returns 0 if vector is not allocated
 */
int linearVectors (int *V, int *W, int *Z, int n, int a, int b);

/*
 * return the index of maximum of vector X of length n
 */
int maxVector (int *X, int n);

/*
 * return the index of minimum of vector X of length n
 */
int minVector (int *X, int n);

/*
 * creates a random int vector in A, length n, with numbers in [a,b]
 * note: srand must already be initialized
 */
void randVector (int *A, int n, int a, int b);

/*
 * multiplies W = kV, vectors of length n
 */
void scalarVector (int *V, int *W, int n, int k);

/*
 * if flag = 1, sums C = A + B, vectors of length n
 */
void sumVectors (int *A, int *B, int *S, int n);

/*
 * returns the mean of a vector
 */
double vectorMean (int *V, int n);

/*
 * returns the scalar product AB, vectors of length n
 */
int vectorVector (int *A, int *B, int n);
