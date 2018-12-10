/*
** this file is part of a git repository licensed under the
**										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** header for basic algebra related function
**
** first created	30/10/2018 (with older materials)
** version 0			30/10/2018
** last updated		10/12/2018
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

typedef struct xfactor {
	int base;
	int power;
	struct xfactor *next;
} factor;

typedef struct xsieve {
	int info;
	struct xsieve *next;
} sieve;

/*
 * converts the integer in A of n digits from base b to 10 and returns it;
 * note: A is in the form so that x = sum a_i * b^i for i = 0 to n
 */
int baseToTen (int *A, int b, int n);

/*
 * calculates bezout's identity using the extended euclidian algorithm
 * returns the gcd(a,b) and stores in l, m coefficients so that
 * al + bm = gcd(a,b)
 */
int bezout (int a, int b, int *l, int *m);

/*
 * returns 0 if a does not divide b, otherwise a positive value
 * note: you have to ensure a is not 0
 */
int divide (int a, int b);

/*
 * returns the value a^n
 * runs in O(log_2 n)
 * uses the notation in base 2
 * note: beware of overflow
 */
int esp (int a, int n);

/*
 * prints the factorization in out stream
 */
void exportFactorization (FILE *out, factor *f);

/*
 * prints the list in out stream
 */
void exportSieve (FILE *out, sieve *s);

/*
 * finds all factors of n in S
 * if S is long enough, completely factorizes n
 * returns pointer to factorization or NULL if failed
 * note: S has to be already initialized to intSQRT(n)
 */
factor *factorize (int n, sieve *S);

/*
 * calculates the gcd using the euclid's algorithm
 * returns the gcd between a and b or 0 if a or b was 0
 */
int GCD (int a, int b);

/*
 * returns NULL if n has not divisors in S, pointer to a divisor otherwise
 * note: if sieve is initialized with intSQRT(n) says if n is prime
 * note: sieve has to be initialized elsewhere
 */
sieve *hasDivisors (int n, sieve *S);

/*
 * initializes a sieve we bigger element n
 * returns pointer to first element (2) or NULL if failed
 */
sieve *initializeSieve (int n);

/*
 * returns 1 if n is prime, 0 o/w
 * uses the Eratostene's sieve
 * note: consider using hasDivisors(n, S) if you need more than one answer
 */
int isPrime (int n);

/*
 * returns log_b(a) = lengthInBase(a,b)-1
 * note: overflows at 1000000000
 */
int intLOG(int a, int b);

/*
 * calculates the integer approximation of sqrt(a)
 * uses Newton's integer algorithm
 * return the floor (sqrt(a))
 * note: does not overflow
 */
int intSQRT (int a);

/*
 * calculates the lcm using the formula ab/gcd(a,b)
 * returns the lcm or 0 if a or b is 0
 */
int lcm (int a, int b);

/*
 * returns the length of x written in base b
 * that is log_b x +1
 * note: overflows at 1000000000
 */
int lengthInBase (int x, int b);

/*
 * writes x in base b in array A
 * return 0 if x or b are 0, 1 otherwise
 * note: A has to be already allocated (see also lengthInBase function)
 * note: this uses the remainders euclidian algorithm
 * note: when you print A, you have to print it reversed
 */
int tenToBase (int x, int b, int *A);
