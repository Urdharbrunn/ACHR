/*
** this file is part of a git repository licensed under the
**										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for graph related function
** graph are represented with adiacency lists
** requires list.h and vector.h
**
** first created	30/10/2018 (with older materials)
** version 0			30/10/2018
** last updated		17/01/2019
**
** function count -> 25
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
	int flag = 0;
	if (!G)
		fprintf(stderr, "!W addEdge: graph is not allocated\n");
	else if (u > G->n || v > G->n)
		fprintf(stderr, "!W addEdge: requested edge out of bound\n");
	else {
		G->V[u] = stack(G->V[u], v);
		if (!G->V[u])
			fprintf(stderr, "!E addEdge: node creation failed\n");
		else
			flag = 1;
	}

	return(flag);
}

int addEdgeMatrix(graph *G, int u, int v) {
	int flag = 0;
	if (!G)
		fprintf(stderr, "!W addEdgeMatrix: graph is not allocated\n");
	else if (u > G->n || v > G->n)
		fprintf(stderr, "!W addEdgeMatrix: requested edge out of bound\n");
	else if (!G->A)
		fprintf(stderr, "!W addEdgeMatrix: matrix is not allocated");
	else {
		flag = 1;
		G->A[u][v] = 1;
	}
	return(flag);
}

component *allocateComponent (int k) { //debugged
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

int BFS (graph *G, int s, int *D, int *P, int doComponent) { //debugged
	int *colour = NULL, u, flag = 0;
	node *v = NULL;
	queue Q;

	if (!G)
		fprintf(stderr, "!W BFS: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W BFS: vertex vector is not allocated\n");
	else if (!D)
		fprintf(stderr, "!W BFS: distance vector is not allocated\n");
	else if (!P)
		fprintf(stderr, "!W BFS: tree vector is not allocated\n");
	else {
	
		//initialization
		colour = allocateVector(G->n);

		Q.first = NULL;
		Q.last = NULL;

		if (push(&Q, s) && colour) { //all went ok
			flag = 1;
			if (doComponent) {
				G->C = stackComponent(G->C, s);
				if (!G->C)
					flag = 0;
				else {
					G->C->vertex = stack(G->C->vertex, s);
					if (!G->C->vertex)
						flag = 0;
					else {
						G->C->size ++;
						G->nC ++;
					}
				}
			}

			initializeVector(colour, G->n, 0);
			initializeVector(P, G->n, -1);
			initializeVector(D, G->n, -1);
			colour[s] = 1;
			D[s] = 0;
			while (Q.first && flag) {
				u = pop(&Q);
				v = G->V[u];
				while (v && flag) {
					if (!colour[v->info]) {
						colour[v->info] = 1;
						if (doComponent) {
							G->C->vertex = stack(G->C->vertex, v->info);
							if (!G->C->vertex)
								flag = 0;
							else
								G->C->size ++;
						}
						D[v->info] = D[u] + 1;
						P[v->info] = u;
						if (!push(&Q, v->info))
							flag = 0;
					}
					v = v->next;
				}
			}

		}
	}
	return (flag);
}

int BFSComponents (graph *G) { //debugged
	int *colour = NULL, v, flag = 0, r;
	node *u = NULL;
	queue Q;
	component *H = NULL;

	if (!G)
		fprintf(stderr, "!W BFS: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W BFS: vertex vector is not allocated\n");
	else {
		flag = 1;

		if (G->C)
			deleteComponentList(G->C);
		G->C = NULL;
		G->nC = 0;
		colour = allocateVector(G->n);

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
				if (!colour[r] && !G->Deleted[u]) {
					flag = push(&Q, r);
					H = stackComponent(H, r);
					colour[r] = 1;
					if (!H) {
						flag = 0;
						fprintf(stderr, "!W BFSComponents: component allocation failed\n");
					} else {
						H->vertex = stack(H->vertex, r);
						if (!H->vertex) {
							flag = 0;
							fprintf(stderr, "!W BFSComponents: vertex allocation failed\n");
						}
						H->size++;
					}
					G->nC++;

					//BFS
					while (Q.first && flag && H) {
						v = pop(&Q);
						u = G->V[v];
						while (u && flag) {
							if (!colour[u->info]) {
								colour[u->info] = 1;
								H->vertex = stack(H->vertex, u->info);
								if (!push(&Q, u->info) || !H->vertex)
									flag = 0;
								H->size++;
							}
							u = u->next;
						}
					}
				}
				r++;
			}
		}
		if (!flag)
			H = NULL;
		G->C = H;
	}
	return (flag);
}

int *BFSDistance (graph *G, int s) { //debugged
	int *colour = NULL, *D = NULL, u;
	node *v = NULL;
	queue Q;

	if (!G)
		fprintf(stderr, "!W BFS: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W BFS: vertex vector is not allocated\n");
	else {

		//initialization
		colour = allocateVector(G->n);
		D = allocateVector(G->n);
		if (!colour || !D)
			D = NULL;

		Q.first = NULL;
		Q.last = NULL;

		if (!push(&Q, s)) {
			deleteVector(D);
			D = NULL;
		}

		if (D) { //all went ok
			initializeVector(colour, G->n, 0);
			initializeVector(D, G->n, -1);
			colour[s] = 1;
			D[s] = 0;
			while (Q.first && D) {
				u = pop(&Q);
				v = G->V[u];
				while (v && D) {
					if (!colour[v->info]) {
						colour[v->info] = 1;
						D[v->info] = D[u] + 1;
						if (!push(&Q, v->info)) {
							deleteVector(D);
							D = NULL;
						}
					}
					v = v->next;
				}
			}

		}
	}
	return (D);
}

int *BFSTree (graph *G, int s) { //debugged
	int *colour = NULL, *P = NULL, u;
	node *v = NULL;
	queue Q;

	if (!G)
		fprintf(stderr, "!W BFS: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W BFS: vertex vector is not allocated\n");
	else {

		//initialization
		colour = allocateVector(G->n);
		P = allocateVector(G->n);
		if (!colour || !P)
			P = NULL;

		Q.first = NULL;
		Q.last = NULL;

		if (!push(&Q, s)) {
			deleteVector(P);
			P = NULL;
		}

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
					}
					v = v->next;
				}
			}

		}
	}
	return (P);
}

void deleteComponentList (component *list) { //debugged
	component *c = list;
	while (c) {
		deleteList(c->vertex);
		c = c->next;
		free(list);
		list = c;
	}
	return;
}

int deleteEdge (graph *G, int u, int v) { //debugged
	node *p = NULL, *q;
	int flag = 0;

	if (!G)
		fprintf(stderr, "!W deleteEdge: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W deleteEdge: graph vertex vector is not allocated\n");
	else {
		q = G->V[u];
		p = q->next;
		if (q->info == v) {
			flag = 1;
			free(q);
			G->V[u] = p;
		}
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
	}
	return (flag);
}

void deleteGraph (graph *G) { 
	if (!G)
		fprintf(stderr, "!W freeGraph: requested deletion of free memory!\n");
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

int deleteNode (graph *G, int u) { //debugged
	int v, flag = 1;

	if (!G) {
		flag = 0;
		fprintf(stderr, "!W deleteNode: graph is not allocated\n");
	}
	else if (!G->Deleted) {
		fprintf(stderr, "!W deleteNode: allocating Deleted vector\n");
		G->Deleted = allocateVector(G->n);
		if (G->Deleted) {
			initializeVector(G->Deleted, G->n, 0);
			G->Deleted[u] = 1;
		} else
			fscanf(stderr, "!W deleteNode: vector allocation failed\n");
	} else
		G->Deleted[u] = 1;

	if (flag && !G->V) {
		flag = 0;
		fprintf(stderr, "!W deleteNode: vertex vector is not allocated\n");
	}
	else {
		//delete u from every adiacency list
		for (v = 0; v < G->n; v++)
			G->V[v] = searchDelete(G->V[v], u);

		//delete G_u list
		G->V[u] = deleteList(G->V[u]);

		//update connected component
		if (G->C)
			BFSComponents(G);

		//remove u from matrix
		if (G->A) {
			initializeVector(G->A[u], G->n, 0);
			for (v=0; v < G->n; v++)
				G->A[v][u] = 0;
		}
	}

	return;
}

void exportComponent (FILE *out, component *list) { //debugged
	if (!out) {
		fprintf(stderr, "!W exportComponent: output file is not opened\n");
		list = NULL;
	}
	while (list) {
		fprintf(out, "Component %d has %d vertex: ", list->info, list->size);
		exportList(list->vertex, out);
		list = list->next;
	}
	fprintf (out, "\n");
	return;
}

void exportGraph (FILE *out, graph *G) { //debugged
	int i;
	if (!out)
		fprintf(stderr, "!W exportGraph: output file is not opened\n");
	else if (!G)
		fprintf(stderr, "!W exportGraph: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W exportGraph: vertex vector is not allocated\n");
	else {
		fprintf(out, "%d\n", G->n);
		for (i=0; i < G->n; i++) {
			fprintf(out, "%d\t", listLength(G->V[i]));
			exportList(G->V[i], out);
		}
	}
	return;
}

void exportGraphComplete (FILE *out, graph *G) {
	int i;
	if (!out)
		fprintf(stderr, "!W exportGraphComplete: output file is not opened\n");
	else if (!G)
		fprintf(stderr, "!W exportGraphComplete: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W exportGraphComplete: vertex vector is not allocated\n");
	else {
		fprintf(out, "Number of vertices: %d\n", G->n);
		if (G->V) {
			fprintf(out, "\nAdiacency lists\n");
			for (i=0; i < G->n; i++) {
				fprintf(out, "%d -> ", i);
				exportList(G->V[i], out);
			}
		}
		if (G->A) {
			fprintf(out, "\nAdiacency matrix\n");
			exportMatrix(out, G->A, G->n, G->n);
		}
		if (G->C) {
			fprintf(out, "\nNumber of components: %d\n", G->nC);
			exportComponent(out, G->C);
		}
	}
	return;
}

void exportGraphTerminator (FILE *out, graph *G) { //debugged
	int i;
	if (!out)
		fprintf(stderr, "!W exportGraphTerminator: output file is not opened\n");
	else if (!G)
		fprintf(stderr, "!W exportGraphTerminator graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W exportGraphTerminator: vertex vector is not allocated\n");
	else {
		fprintf(out, "%d\n", G->n);
		for (i=0; i < G->n; i++) {
			fprintf(out, "%d: ", i);
			exportListTerminator(G->V[i], out);
		}
		fprintf(out, "\n");
	}
	return;
}

int graphToMatrix (graph *G, int **A) { //debugged
	node *p = NULL;
	int i, flag = 0;

	if (!G)
		fprintf(stderr, "!W graphToMatrix: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W graphToMatrix: vertex vector is not allocated\n");
	else if (!G->A)
		fprintf(stderr, "!W graphToMatrix: matrix is not allocated\n");
	else {
		flag = 1;
		for (i=0; i < G->n; i++) {
			p = G->V[i];
			while (p) {
				A[i][p->info] = 1;
				p = p->next;
			}
		}
	}
	return(flag);
}

int importGraph (FILE *input, graph *G) { //debugged
	int i = 0;
	if (!input)
		fprintf(stderr, "!W importGraph: input file is not opened\n");
	else if (!G)
		fprintf(stderr, "!W importGraph: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W importGraph: vertex vector is not allocated\n");
	else {
		fscanf(input, "%d", &G->n);
		G->V = malloc(G->n * sizeof(node*));
		if (!G->V)
			fprintf(stderr, "!E importGraph: memory allocation error\n");
		else {
			for (i=0; i < G->n; i++) {
				fscanf(input, "%d", &m);
				G->V[i] = importStack(m, input);
			}
			i = 1;
		}
	}
	return(i);
}

int importGraphTerminator (FILE *input, graph *G) { //debugged
	int i, v = 0, x;
	if (!input)
		fprintf(stderr, "!W importGraph: input file is not opened\n");
	else if (!G)
		fprintf(stderr, "!W importGraph: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W importGraph: vertex vector is not allocated\n");
	else {
		fscanf(input, "%d", &G->n);

		if (initializeGraph(G, G->n)) {
			for (i=0; i < G->n; i++) {
				fscanf(input, "%d:", &v);
				if (v != i)
					fprintf(stderr, "!W importGraphTerminator: vertices not in order\n");
				fscanf(input, "%d", &x);
				while (x != -1) {
					addEdge(G, v, x);
					fscanf(input, "%d", &x);
				}
			}
			v = 1;
		}
	}
	return(v);
}

int initializeGraph (graph *G, int n) { //debugged
	int flag = 1, i;
	if (!G) {
		fprintf(stderr, "!W initializeGraph: graph is not allocated\n");
		flag = 0;
	}
	else {
		G->V = malloc(n*sizeof(node*));
		if (!G->V) {
			fprintf(stderr, "!E initializeGraph: memory allocation error\n");
			flag = 0;
		} else {
			G->n = n;
			G->nC = 0;
			for (i=0; i < n; i++)
				G->V[i] = NULL;
			G->C = NULL;
			G->A = NULL;
		}
	}
	return(flag);
}

int mathExportGraph (graph *G, char name[]) { //debugged
	int i, flag = 0;
	FILE *out = NULL;
	node *p = NULL;

	out = fopen(name, "w");
	if (!out)
		fprintf(stderr, "!E mathExportGraph: error opening file %s in write mode\n", name);
	else if (!G)
		fprintf(stderr, "!W mathExportGraph: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W mathExportGraph: vertex vector is not allocated\n");
	else {
		flag = 1;
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

int matrixToGraph (int **A, graph *G) { //debugged
	int i, j, flag = 0;

	if (!G)
		fprintf(stderr, "!W matrixToGraph: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W matrixToGraph: vertex vector is not allocated\n");
	else if (!A)
		fprintf(stderr, "!W matrixToGraph: matrix is not allocated\n");
	else {
		flag = 1;
		for (i=0; i < G->n; i++) {
			for (j=0; j < G->n; j++) {
				if (A[i][j])
					flag = addEdge(G, i, j);
				if (!flag) {
					j = G->n;
					i = G->n;
					fprintf(stderr, "!E matrixToGraph: error adding edge\n");
				}
			}
		}
	}
	return(flag);
}

int randomGraph48 (graph *G, double p) { //debugged
	int i, j, n, flag = 0;

	if (!G)
		fprintf(stderr, "!W randomGraph48: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W randomGraph48: vertex vector is not allocated\n");
	else {
		n = G->n;
		flag = n;
		for (i=0; i < n; i++) {
			for (j = i+1; j < n; j++) {
				if (drand48() < p) {
					if (!addEdge(G, i, j) || !addEdge(G, j, i)) {
						flag = 0;
						i = n; 
						j = n;
					}
				}
			}
		}
	}
	return(flag);
}

int randomDigraph48 (graph *G, double p) { //debugged
	int i, j, n, flag = 0;

	if (!G)
		fprintf(stderr, "!W randomGraph48: graph is not allocated\n");
	else if (!G->V)
		fprintf(stderr, "!W randomGraph48: vertex vector is not allocated\n");
	else {
		n = G->n;
		flag = 1;
		for (i=0; i < n; i++) {
			for (j=0; j < n; j++) {
				if (j != i && drand48() < p) {
					if (!addEdge(G, i, j)) {
						i = n;
						j = n;
						flag = 0;
					}
				}
			}
		}
	}
	return(flag);
}

component *stackComponent (component *list, int x) { //debugged
	component *q = NULL;
	q = malloc(sizeof(component));
	if (!q) {
		deleteComponentList(list);
		list = NULL;
		fprintf(stderr, "!E stack: memory allocation error\n");
	}
	else {
		q->info = x;
		q->next = list;
		q->size = 0;
		q->vertex = NULL;
		list = q;
	}
	return(list);
}

int transposeGraph (graph *G, graph *GT) { //debugged
	int u, flag = 0;
	node *p, *q;

	if (!G)
		fprintf(stderr, "!W transposeGraph: graph is not allocated\n");
	else if (!GT)
		fprintf(stderr, "!W transposeGraph: transpost graph is not allocated\n");
	else if (!GT->V)
		fprintf(stderr, "!W transposeGraph: transpost graph's vertex vector is not allocated\n");
	else if (!G->V) 
		fprintf(stderr, "!W transposeGraph: vertex vector is not allocated\n");
	else {
		flag = 1;
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
	}
	return(flag);
}
