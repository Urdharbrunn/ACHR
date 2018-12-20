/*
** this file is part of a git repository licensed under the
**										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for stacks and queues related function
**
** first created	20/12/2018 (with older materials)
** version 0			20/12/2018
** last updated		20/12/2018

** function count -> 19
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

queue *allocateQueue (void) { //debugged
	queue *Q = malloc(sizeof(queue));
	if (!Q)
		fprintf(stderr, "!E allocateQueue: memory allocation error\n");
	else {
		Q->first = NULL;
		Q->last = NULL;
	}
	return (Q);
}

node *copyListRecursive (node *p) { //debugged
	node *q = NULL;
	if (p) {
		q = malloc(sizeof(node));
		if (q) {
			q->info = p->info;
			q->next = copyListRecursive(p->next);
			if (!q->next && p->next) {
				free(q);
				q = NULL;
			}
		} else
				fprintf(stderr, "!E copyListRecursive: memory allocation error\n");
	}
	return (q);
}

node* copyNode (node *p){ //debugged
	node *q = malloc(sizeof(node));
	if (!q)
		fprintf(stderr, "!E stack: memory allocation error\n");
	else {
		q->info = p->info;
		q->next = p->next;
	}
	return(q);
}

node *deleteList (node *list) { //debugged
	node *t;
	while (list != NULL) {
		t = list->next;
		free (list);
		list = t;
	}
	return (list);
}

void deleteNodeNext (node *p) { //debugged
	node *t = NULL;
	if(!p->next)
		fprintf(stderr, "!W deleteNodeNext: requested deletion of NULL node\n");
	else {
		t = p->next->next;
		free(p->next);
		p->next=t;
	}
	return;
}

void exportList (node *list, FILE *out) { //debugged
	while (list) {
		fprintf (out, "%d ", list->info);
		list = list->next;
	}
	fprintf (out, "\n");
	return;
}

node *goToLast (node *list){ //debugged
	while (list->next)
		list = list->next;
	return(list);
}

node *importQueue (queue *Q, int n, FILE *input) { //debugged
	node *p = NULL;
	p = malloc(sizeof(node));
	if (!p)
		fprintf(stderr, "!E importQueue: memory allocation error\n");
	else if (n) {
		fscanf (input, "%d", &p->info);
		p->next = importQueue(Q, n-1, input);
		if (!p->next && n > 1) {
			fprintf(stderr, "!E importQueue: memory allocation error\n");
			free(p);
			p = NULL;
		}
	}
	if (!n)
		p = NULL;

	if (n == 1)
		Q->last = p;
	return (p);
}

node *importStack (int n, FILE *input) { //debugged
	node *s = NULL, *p;
	int i;
	for (i=0; i < n; i++) {
		p = malloc(sizeof(node));
		if (!p) {
			fprintf(stderr, "!E importStack: memory allocation error\n");
			free(s);
			s = NULL;
		} else {
			fscanf (input, "%d", &p->info);
			p->next = s;
			s = p;
		}
	}
	return (s);
}

void insertNode (node *p, node *q) { //debugged
	q->next = p->next;
	p->next = q;
	return;
}

node *invertList (node *list) { //debugged
	node *t, *p = NULL;
	while (list != NULL) {
		t = list->next;
		list->next = p;
		p = list;
		list = t;
	}
	return (p);
}

int listLength (node *list) { //debugged
	node *p = list;
	int length = 0;

	while (p != NULL) {
		length++;
		p = p->next;
	}
	return (length);
}

int pop(queue *Q) { //debugged
	int x = Q->first->info;
	node *p;
	
	if (Q->first->next == NULL) {
		free(Q->first);
		Q->first = NULL;
		Q->last = NULL;
	} else {
		p = Q->first;
		Q->first = Q->first->next;
		free(p);
	}
	return(x);
}

int push(queue *Q, int x) { //debugged
	node *p;
	int flag = 1;
	p = malloc(sizeof(node));
	if (!p) {
		fprintf(stderr, "!E push: memory allocation error\n");
		flag = 0;
	} else {
		p->info = x;
		p->next = NULL;
		if (Q->last == NULL){
			Q->last = p;
			Q->first = p;
		} else {
			Q->last->next = p;
			Q->last = p;
		}
	}
	return(flag);
}

node *randomList (int n, int a, int b) { //debugged
	node *list = NULL, *p;
	int i;

	for (i=0; i < n; i++){
		p = malloc(sizeof(node));
		if (!p) {
			fprintf(stderr, "!E randomList: memory allocation error\n");
			deleteList(list);
			list = NULL;
		} else {
			p->info = (rand()%(b-a+1))+a;
			p->next = list;
			list = p;
		}
	}
	return(list);
}

node *search (node *list, int k) { //debugged
	node *p = list, *flag = NULL;

	while (p && !flag) {
		if (p->info == k)
			flag = p;
		else
			p = p->next;
	}
	return (flag);
}

node *searchDelete (node *list, int k) { //debugged
	node *p = NULL;
	while (list->info == k) {
		p = list;
		list = list->next;
		free(p);
	}
	p = searchNext(list, k);
	while (p) {
		deleteNodeNext(p);
		p = searchNext(list, k);
	}
	return(list);
}

node *searchNext (node *list, int k) { //debugged
	node *p = list, *q = p, *flag = NULL;
	int kIsFirst = 0;
	if (p && p->info == k)
		kIsFirst = 1;
	else if (p)
		p = p->next;
	if (!kIsFirst) {
		while (p && !flag) {
			if (p->info == k)
				flag = q;
			else {
				p = p->next;
				q = q->next;
			}
		}
	}
	return (flag);
}

node *stack (node *list, int x) { //debugged
	node *q;
	q = malloc(sizeof(node));
	if (!q) {
		deleteList(list);
		list = NULL;
		fprintf(stderr, "!E stack: memory allocation error\n");
	}
	else {
		q->info = x;
		q->next = list;
		list = q;
	}
	return(list);
}