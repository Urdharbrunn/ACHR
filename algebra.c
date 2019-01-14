/*
** this file is part of a git repository licensed under the
**										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for basic algebra related function
**
** first created	30/10/2018 (with older materials)
** version 0			30/10/2018
** last updated		10/12/2018
**
** function count -> 17
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdlib.h>
#include <stdio.h>
#include "algebra.h"

int baseToTen (int *A, int b, int n) { //debugged
	int t = 0, i, e = 1;
	for (i=0; i < n; i++) {
		t += A[i]*e;
		e *= b;
	}
	return (t);
}

int bezout (int a, int b, int *l, int *m) { //debugged
  int s = 0, old_s = 1, t = 1, old_t = 0, r = b, old_r = a, q, tmp;

  while (r) {
    q = old_r / r;
    
    tmp = r;
    r = old_r - q*r;
    old_r = tmp;

    tmp = s;
    s = old_s - q*s;
    old_s = tmp;

    tmp = t;
    t = old_t - q*t;
    old_t = tmp;
  }

  *l = old_s;
  *m = old_t;

  return (old_r);
}

int divide (int a, int b) { //debugged
	int flag = 1;
	if (!a)
		fprintf(stderr, "!W divide: requested 0 division\n");
	else
		flag = !(b%a);
  return (flag);
}

int esp (int a, int n) { //debugged
	int p = 1;
	while (n) {
		if (n%2)
			p *= a;
		a *= a;
		n /= 2;
	}
	return(p);
}

int eulerFunction (factor *p) { //debugged
	int f = 1, t;
	while (p) {
		if (p->power != 1) {
			t = esp(p->base, p->power-1);
			f *= t * p->base - t;
		} else
			f *= p->base;
		p = p->next;
	}
	return(f);
}

void exportFactorization (FILE *out, factor *f) { //debugged
	if (!f)
		fprintf(stderr, "!W exportFactorization: empty factorization\n");
	else if (f->power != 1) {
		fprintf(out, "%d^%d", f->base, f->power);
		f = f->next;
	}
	else {
		fprintf(out, "%d", f->base);
		f = f->next;
	}
	while (f) {
		if (f->power != 1)
			fprintf (out, " * %d^%d", f->base, f->power);
		else
			fprintf(out, " * %d", f->base);
		f = f->next;
	}
	fprintf (out, "\n");
	return;
}

void exportSieve (FILE *out, sieve *s) { //debugged
	while (s) {
		fprintf (out, "%d ", s->info);
		s = s->next;
	}
	fprintf (out, "\n");
	return;
}

factor *factorize (int n, sieve *S) { //debugged
	factor *f = NULL;
	S = hasDivisors (n, S);
	if (S && divide(S->info, n)) {
		f = malloc(sizeof(factor));
		if (!f)
			fprintf(stderr, "!E factorize: memory allocation error\n");
		else {
			f->base = S->info;
			f->power = 1;
			n /= f->base;
			while (divide(f->base, n)) {
				f->power++;
				n /= f->base;
			}
			if (n == 1)
				f->next = NULL;
			else
				f->next = factorize(n,S);
		}
	} else {
		f = malloc(sizeof(factor));
		if (!f)
			fprintf(stderr, "!E factorize: memroy allocation error\n");
		else {
			f->base = n;
			f->power = 1;
			f->next = NULL;
		}
	}
	return (f);
}

int GCD (int a, int b) { //debugged
	if (!b)
		fprintf(stderr, "!W GCD: requested MCD for 0\n");
	else {
		int r = a%b;
		while (r) {
			a = b;
			b = r;
			r = a%b;
		}
	}
	return (b);
}

sieve *hasDivisors (int n, sieve *S) { //debugged
	int flag = 1, m = intSQRT(n);
	sieve *p = S;
	while (p && flag && p->info < m) {
		if (divide(p->info, n))
			flag = 0;
		else
			p = p->next;
	}
	return(p);
}

sieve *initializeSieve (int n) { //debugged
	int *S = NULL, k, i;
	sieve *s = NULL, *p;
	S = malloc(sizeof(int)*(n+1));
	if (!S)
		fprintf(stderr, "!E initializeSieve: array memory allocation failed\n");
	else {
		S[0] = 0;
		S[1] = 0;
		for (i=2; i <= n; i++) //initialization
			S[i] = 1;
		//we allocate a temporary phantom first element
		p = malloc(sizeof(sieve));
		if (!p) {
			fprintf(stderr, "!E initializeSieve: sieve memory allocation failed\n");
			n = 2; //we need to not enter into for structure
		}
		s = p;
		for (i=2; i <= n; i++) {
			if (S[i]) {
				p->next = malloc(sizeof(sieve));
				p = p->next;
				if (p)
					p->info = i;
				else {
					fprintf(stderr, "!E initializeSieve: sieve memory allocation failed\n");
					i = n + 1;
				}
				if (i <= n/2)
					k = 2*i;
				else
					k = n+1;
				while (k <= n && k > 0) { //second condition controls overflow
					S[k] = 0;
					k += i;
				}
			}
		}
		free (S);
		if (s) { //eliminate the temporary first element
			p = s;
			s = s->next;
			free(p);
		}
	}
	return (s);
}

int intLOG(int a, int b) { //debugged
	
	return (lengthInBase(a, 10)-1);
}

int intSQRT (int a) { //debugged
	int x = esp(10, intLOG(a,10)/2+1)/2, x_old = a; //initial position
	if (a <= 100) {
		x = 10;
	}
	while (x_old - x > 1) {
		x_old = x;
		x = (x+a/x) / 2;
	}

	return (x);
}

int isPrime (int n) { //debugged
	int m = intSQRT(n), flag = 1;
	sieve *S = initializeSieve(m), *p = S;
	while (p && flag) {
		if (divide(p->info, n))
			flag = 0;
		else {
			free (S);
			p = p->next;
			S = p;
		}
	}
	return(flag);
}

int lcm (int a, int b) { //debugged
	int flag = 0;
	if (!a || !b)
		fprintf(stderr, "!W lcm: requested lcm for 0\n");
	else
		flag = a*b / GCD(a,b);
	return (flag);
}

int lengthInBase (int x, int b) { //debugged
	int i = 0, e = 1;

	while (x > 0) {
		i++;
		x -= (b-1)*e;
		e *= b;
	}
	return(i);
}

int tenToBase (int x, int b, int *A) { //debugged
	int i = 0;
	if(!b)
		fprintf(stderr, "!W tenToBase: requested x written in base 0!\n");
	else {
		while (x) {
			A[i] = x%b;
			i++;
			x /= b;
		}
	}
	return (i);
}
