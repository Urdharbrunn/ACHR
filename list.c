/*
** this file is part of a git repository licensed under the
**										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for stacks and queues related function
**
** first created	20/12/2018 (with older materials)
** version 0			20/12/2018
** last updated		18/01/2019

** function count -> 20
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"

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

node *copyList (node *list) {
	node *q = NULL, *first = NULL;
	q = malloc(sizeof(node));
	if (q && list) {
		q->info = list->info;
		list = list->next;
		first = q;
		while (list) {
			q->next = malloc(sizeof(node));
			q = q->next;
			if (!q) {
				deleteList(q);
				q = NULL;
			} else {
				q->info = list->info;
				list = list->next;
			}
		}
		if (q)
			q->next = NULL;
	}
	return(first);
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
	while (list) {
		t = list->next;
		free (list);
		list = t;
	}
	return (list);
}

void deleteNodeNext (node *p) { //debugged
	node *t = NULL;
	if (!p || !p->next)
		fprintf(stderr, "!W deleteNodeNext: requested deletion of NULL node\n");
	else {
		t = p->next->next;
		free(p->next);
		p->next=t;
	}
	return;
}

void exportList (FILE *out, node *list) { //debugged
	if (!out)
		fprintf(stderr, "!W exportList: output file not opened\n");
	else {
		while (list) {
			fprintf (out, "%d ", list->info);
			list = list->next;
		}
		fprintf (out, "\n");
	}
	return;
}

void exportListTerminator (FILE *out, node *list) { //debugged
	if (!out)
		fprintf(stderr, "!W exportList: output file not opened\n");
	else {
		while (list) {
			fprintf (out, "%d ", list->info);
			list = list->next;
		}
		fprintf (out, "-1\n");
	}
	return;
}

node *goToLast (node *list){ //debugged
	while (list && list->next)
		list = list->next;
	return(list);
}

node *importQueue (FILE *input, queue *Q, int n) { //debugged
	node *p = NULL;

	if (!input)
		fprintf(stderr, "!W importQueue: import file not opened\n");
	else if (!Q)
		fprintf(stderr, "!W importQueue: queue not allocated\n");
	else {
		p = malloc(sizeof(node));
		if (!p)
			fprintf(stderr, "!E importQueue: memory allocation error\n");
		else if (n) {
			fscanf (input, "%d", &p->info);
			p->next = importQueue(input, Q, n-1);
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
	}
	return (p);
}

node *importStack (FILE *input, int n) { //debugged
	node *s = NULL, *p = NULL;
	int i;

	if (!input)
		fprintf(stderr, "!W importQueue: import file not opened\n");
	else {
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
	}
	return (s);
}

int insertNode (node *p, node *q) { //debugged
	int flag = 0;
	if (!q)
		fprintf(stderr, "!W insertNode: requested insertion of NULL node\n");
	else if (!p)
		fprintf(stderr, "!W insertNode: requested insertion after NULL node\n");
	else {
		flag = 1;
		q->next = p->next;
		p->next = q;
	}
	return (flag);
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

int pop (queue *Q) { //debugged
	int x = 0;
	node *p;

	if (!Q)
		fprintf(stderr, "!W pop: queue not allocated\n");
	else if (!Q->first)
		fprintf(stderr, "!W pop: requested pop from empty queue\n");
	else {
		x = Q->first->info;
		if (Q->first->next == NULL) {
			free(Q->first);
			Q->first = NULL;
			Q->last = NULL;
		} else {
			p = Q->first;
			Q->first = Q->first->next;
			free(p);
		}
	}
	return(x);
}

int push(queue *Q, int x) { //debugged
	node *p;
	int flag = 0;

	if (!Q)
		fprintf(stderr, "!W push: queue not allocated\n");
	else {
		p = malloc(sizeof(node));
		if (!p)
			fprintf(stderr, "!E push: memory allocation error\n");
		else {
			flag = 1;
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
	if (list && list->info == k) {
		p = list;
		list = list->next;
		free(p);
	} else {
		p = searchNext(list, k);
		if (p)
			deleteNodeNext(p);
	}
	return(list);
}

node *searchDeleteAll (node *list, int k) { //debugged
	node *p = NULL;
	while (list && list->info == k) {
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
	if (p && p->info == k)
		flag = NULL;
	else if (p) {
		while (p->next && !flag) {
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