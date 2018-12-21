/*
** this file is part of a git repository licensed under the
**										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for graph related function
** graph are represented with adiacency lists
**
** first created	30/10/2018 (with older materials)
** version 0			30/10/2018
** last updated		21/12/2018
**
** function count -> 20
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "vector.h"
#include "list.h"
#include "graph.h"

int addEdge(graph *G, int u, int v) { //debugged
	int flag = 1;

	if (u > G->n || v > G->n) {
		flag = 0;
		fprintf(stderr, "!W addEdge: requested edge out of bound\n");
	} else
		G->V[u] = stack(G->V[u], v);

	return(flag);
}

component *allocateComponent (int k) {
	component *C = NULL;
	C = malloc(sizeof(component));
	if (!C)
		fprintf(stderr, "!E allocateComponent: memory allocation error\n");
	else {
		C->size = 0;
		C->vertex = NULL;
		C->next = NULL;
		C->info = k;
	}
	return(C);
}

graph *allocateGraph (void) { //debugged
	graph *G = malloc(sizeof(graph));
	if (!G)
		fprintf(stderr, "!E allocateGraph: memory allocation error\n");
	else {
		G->C = NULL;
		G->V = NULL;
		G->n = 0;
	}
	return (G);
}

component *BFSComponents (graph *G) {
	int *colour = malloc(sizeof(int)*G->n), v, k = 0, flag = 1, r;
	node *u = NULL;
	queue Q;
	component *C = NULL;

	if (!colour)
		fprintf(stderr, "!E BFSComponent: vector allocation error\n");
	else {
		//initialization
		for (v=0; v < G->n; v++)
			colour[v] = 0;
		Q.first = NULL;
		Q.last = NULL;

		//cycle on components
		r = 0;
		while (r < G->n && flag) {
			if (!colour[r]) {
				flag = push(&Q, r);
				C = stackComponent(C, k++);

				//BFS
				printf("Starting BFS with root %d\n", r);
				while (Q.first && flag && C) {
					v = pop(&Q);
					u = G->V[v];
					while (u && flag) {
						if (!colour[u->info]) {
							colour[u->info] = 1;
							C->vertex = stack(C->vertex, u->info);
							if (!push(&Q, u->info) || !C->vertex)
								flag = 0;
							C->size++;
						}
						u = u->next;
					}
				}
			}
			r++;
		}
	}
	if (!flag)
		C = NULL;
	return (C);
}

int *BFSTree (graph *G, int s) {
	int *colour = NULL, *P = NULL, u;
	node *v = NULL;
	queue Q;

	//initialization
	colour = allocateVector(G->n);
	P = allocateVector(G->n);
	if (!colour || !P) {
		P = NULL;
	}

	Q.first = NULL;
	Q.last = NULL;

	if (!push(&Q, s))
		P = NULL;

	if (P) { //all went ok
		initializeVector(colour, G->n, 0);
		initializeVector(P, G->n, -1);
		colour[s] = 1;
		while (Q.first && P) {
			u = pop(&Q);
			v = G->V[u];
			while (v && P) {
				if (!colour[v->info]) {
					colour[v->info] = 1;
					P[v->info] = u;
					if (!push(&Q, v->info)) {
						deleteVector(P);
						P = NULL;
					}
					v = v->next;
				}
			}
		}

	}
	return (P);
}

void deleteComponentList (component *list) {
	component *c = list;
	while (c != NULL) {
		deleteList(c->vertex);
		c = c->next;
		free(list);
		list = c;
	}
	return;
}

int deleteEdge (graph *G, int u, int v) {
	node *p = G->V[u], *q;
	int flag = 0;

	q = p;
	p = p->next;
	while (p && !flag) {
		if (p->info == v) {
			q->next = p->next;
			free(p);
			flag = 1;
		} else {
			q = p;
			p = p->next;
		}
	}
	return (flag);
}

void deleteGraph (graph *G) {
	if (!G)
		fprintf(stderr, "!W freeGraph: reqeusted deletion of free memory!\n");
	else {
		int i;
		if (G->V) {
			for (i=0; i < G->n; i++) {
				if (G->V[i])
					deleteList(G->V[i]);
			}
			free(G->V);
		}
		if (G->A)
			deleteMatrix(G->A, G->n);
		if (G->C)
			deleteComponentList(G->C);
		free(G);
	}
	return;
}

void exportComponent (FILE *out, component *list) {
	while (list) {
		fprintf(out, "%d: ", list->info);
		exportList(list->vertex, out);
		list = list->next;
	}
	fprintf (out, "\n");
}

void exportGraph (FILE *out, graph *G) { //debugged
	int i;
	fprintf(out, "Numero di vertici del grafo: %d\n", G->n);
	for (i=0; i < G->n; i++) {
		fprintf(out, "%d -> ", i);
		exportList(G->V[i], out);
		fprintf(out, "\n");
	}
	fprintf(out, "\n");
	return;
}

void exportSelfCompatibleGraph (graph *G, FILE *out) { //debugged
	int i;
	fprintf(out, "%d\n", G->n);
	for (i=0; i < G->n; i++) {
		fprintf(out, "%d\t", listLength(G->V[i]));
		exportList(G->V[i], out);
	}
	return;
}

void graphToMatrix (graph *G) {
	node *p = NULL;
	int i;

	for (i=0; i < G->n; i++) {
		p = G->V[i];
		while (p) {
			G->A[i][p->info] = 1;
			p = p->next;
		}
	}
	return;
}

int importGraph (graph *G, FILE *input) { //debugged
	int i, m;
	fscanf(input, "%d", &G->n);
	G->V = malloc(G->n * sizeof(node*));
	if (!G->V) {
		fprintf(stderr, "!E importGraph: memory allocation error\n");
		m = 0;
	} else {
		for (i=0; i < G->n; i++) {
			fscanf(input, "%d", &m);
			G->V[i] = importStack(m, input);
		}
		m = 1;
	}
	return(m);
}

int initializeGraph (graph *G, int n) { //debugged
	int flag = 1, i;
	G->V = malloc(n*sizeof(node*));
	if (!G->V) {
		fprintf(stderr, "!E initializeGraph: memory allocation error\n");
		flag = 0;
	} else {
		G->n = n;
		for (i=0; i < n; i++)
			G->V[i] = NULL;
	}
	return(flag);
}

int mathExportGraph (graph *G, char name[]) {
	int i, flag;
	FILE *out = NULL;
	node *p = NULL;

	out = fopen(name, "w");
	if (!out) {
		fprintf(stderr, "!E mathExport: error opening file %s in write mode\n", name);
		flag = 0;
	}
	else {
		fprintf(out, "graph {\n");
		for (i=0; i < G->n; i++)
			fprintf(out, "%d\n", i);
		for (i=0; i < G->n; i++) {
			p = G->V[i];
			while (p) {
				if (p->info > i)
					fprintf(out, "%d -- %d;\n", i, p->info);
				p = p->next;
			}
		}
		fprintf(out, "}\n");
		fclose(out);
	}
	return(flag);
}

int matrixToGraph (graph *G) { //debugged
	int i, j, flag;

	for (i=0; i < G->n; i++) {
		for (j=0; j < G->n; j++) {
			if (G->A[i][j])
				flag = addEdge(G, i, j);
			if (!flag) {
				j = G->n;
				i = G->n;
				fprintf(stderr, "!E matrixToGraph: error adding edge\n");
			}
		}
	}
	return(flag);
}

int randomGraph48 (graph *G, double p) { //debugged
	int i, j, n = G->n;

	for (i=0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if (drand48() < p) {
				addEdge(G, i, j);
				addEdge(G, j, i);
			}
		}
	}
	return(n);
}

int randomDigraph48 (graph *G, double p) { //debugged
	int i, j, n = G->n;

	for (i=0; i < n; i++) {
		for (j=0; j < n; j++) {
			if (j != i && drand48() < p) {
				addEdge(G, i, j);
			}
		}
	}
	return(n);
}

component *stackComponent (component *list, int x) { //debugged
	component *q;
	q = malloc(sizeof(component));
	if (!q) {
		deleteComponentList(list);
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

int transposeGraph (graph *G, graph *GT) { //debugged
	int u, flag = 1;
	node *p, *q;

	for (u=0; u < G->n; u++) {
		p = G->V[u];
		while (p) {
			q = stack(GT->V[p->info], u);
			if (GT->V[p->info] == q) { //allocation failed
				p = NULL;
				u = G->n;
				flag = 0;
			} else {
				GT->V[p->info] = q;
				p = p->next;
			}
		}
	}
	return(flag);
}
