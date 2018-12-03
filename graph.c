/*
** this file is part of a git repository licensed under the
**                    GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** source for graph related function
** graph are represented with adiacency lists
**
** first created  30/10/2018 (with older materials)
** version 0      30/10/2018
** last updated   03/12/2018
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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

graph *allocateGraph (void) { //debugged
	graph *G = malloc(sizeof(graph));
	if (!G)
		fprintf(stderr, "!E allocateGraph: memory allocation error\n");
	return (G);
}

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

int deleteEdge(graph *G, int u, int v) {
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

void exportGraph (graph *G, FILE *out) { //debugged
  int i;
  fprintf(out, "Numero di vertici del grafo: %d\n", G->n);
  for (i=0; i < G->n; i++) {
    fprintf(out, "%d -> ", i);
    exportList(G->V[i], out);
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

void exportList (node *list, FILE *out) { //debugged
  while (list != NULL) {
    fprintf (out, "%d ", list->info);
    list = list->next;
  }
  fprintf (out, "\n");
  return;
}

void graphToMatrix (graph *G, int **M) {
  node *p = NULL;
  int i;

  for (i=0; i < G->n; i++) {
    p = G->V[i];
    while (p) {
      M[i][p->info] = 1;
      p = p->next;
    }
  }
  return;
}

node *goToLast (node *list){ //debugged
  while (list->next)
    list = list->next;
  return(list);
}

int importGraph(graph *G, FILE *input) { //debugged
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

int mathExportGraph (graph *G, char name[]) {
  int i, flag;
  FILE *out;
  node *p;

  scanf("%s", name);
  out = fopen(name, "w");
  if (!out) {
    fprintf(stderr, "!E mathExport: error opening file %s in write mode\n", name);
  	flag = 0;
  }
  else {
    fprintf(out, "{");
    for (i=0; i < G->n; i++) {
      p = G->V[i];
      fprintf(out, "{");
      while (p) {
        fprintf(out, "%d", p->info);
        p = p->next;
        if (p) 
          fprintf(out, ",");
      }
      fprintf(out, "}");
      if (i < G->n)
        fprintf(out, ", ");
    }
    fprintf(out, "}\n");
    fclose(out);
  }
  return(flag);
}

int matrixToGraph (int **M, graph *G) { //debugged
  int i, j, flag;

  for (i=0; i < G->n; i++) {
    for (j=0; j < G->n; j++) {
      if (M[i][j])
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

int randomGraph48(graph *G, double p) { //debugged
  int i, j, n = G->n;

  for (i=0; i < n; i++) {
    for (j=i; j < n; j++) {
      if (drand48() < p) {
        if (i!=j) {
        	addEdge(G, i, j);
        	addEdge(G, j, i);
        }
      }
    }
  }
  return(n);
}

int randomDigraph48(graph *G, double p) { //debugged
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

node *stack(node *list, int x) { //debugged
  node *q;
  q = malloc(sizeof(node));
  if (!q)
  	fprintf(stderr, "!E stack: memory allocation error\n");
  else {
	  q->info = x;
	  q->next = list;
	  list = q;
	}
  return(list);
}

int transposeGraph(graph *G, graph *GT) { //debugged
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
