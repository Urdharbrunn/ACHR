/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** header for graph related function
** graph are represented with adiacency lists
** requires list.h and vector.h
**
** first created  30/10/2018 (with older materials)
** version 0      30/10/2018
** last updated   08/01/2019
**
** function count -> 21
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

/*
 * special node to represent the component of a graph
 */
typedef struct xcomponent {
	int info;
	int size;
	node *vertex;
	struct xcomponent *next;
} component;

/*
 * graph structure
 * includes adiacency lists, adiacency matrix and list of components
 * graphs are supposed to be sparse, so adiacency matrix is not often used
 */
typedef struct xgraph {
	int n;
	node **V;
	int **A;
	component *C;
} graph;

/*
 * adds the edge u->v
 * return 1 in success, 0 otherwise
 * note: controls if u, v are in V, but don't if (u,v) already exists
 * note: does NOT add the edge v->u too
 */
int addEdge(graph *G, int u, int v);

/*
 * allocates memory for a component structure and returns pointer
 * info's value is set to k
 */
component *allocateComponent (int k);

/*
 * allocates memory for a graph structure and returns pointer
 */
graph *allocateGraph (void);

/*
 * runs the BFS and constructs the connected components
 * returns pointer to list of components or NULL if failed
 */
component *BFSComponents (graph *G);

/*
 * runs the BFS and constructs the father's vector
 * returns pointer to vector or NULL if failed
 */
int *BFSTree (graph *G,int s);

/*
 * frees memory deleting list
 * returns NULL if everything went ok
 */
void deleteComponentList (component *list);

/*
 * deletes edge u->v from graph
 * return 1 if succeeded, 0 if (u,v) does not exists
 * note: does NOT delete v->u too
 */
int deleteEdge (graph *G, int u, int v);

/*
 * frees memory deleting graph G
 */
void deleteGraph (graph *G);

/*
 * prints the components list in out stream
 */
void exportComponent (FILE *out, component *list);

/*
 * prints the graph in out stream
 * output is compatible with importGraphTerminator
 */
void exportGraphTerminator (FILE *out, graph *G);

/*
 * prints the graph in out stream
 * output is compatible with importGraph
 */
void exportGraph (FILE *out, graph *G);

/*
 * converts the adiacency list of G in the adiacency matrix M
 * note: M MUST be already initialized
 */
void graphToMatrix (graph *G);

/*
 * imports a graph from input in G, that must be already allocated.
 * returns 1 if successfull, 0 otherwise
 * note: input must be in the form
  	[# of vertices] [# of elements in list] [list] [#] [list] ...
 */
int importGraph (FILE *input, graph *G);

/*
 * imports a graph from input in G, that must be already allocated.
 * returns 1 if successfull, 0 otherwise
 * note: input must be in the form
  	[# of vertices]
  	[vertex]: [list] -1
  	[vertex]: [list] -1
  	...
 */
int importGraphTerminator (FILE *input, graph *G);

/*
 * allocates memory in G->V for n vertices
 * return 0 if error, 1 if ok
 */
int initializeGraph (graph *G, int n);

/*
 * opens files "name" in w mode
 * exports the graph in a format suitable for Wolfram Mathematica
 * return 1 if succeeded, 0 if failed
 */
int mathExportGraph (graph *G, char name[]);

/*
 * converts a square matrix into a graph
 * returns 0 on error, 1 otherwise
 * note: G MUST already be initialized
 */
int matrixToGraph (graph *G);

/*
 * generates a random graph using drand48
 * every edge exists with probability p
 * note: does NOT initializes seed
 * note: does NOT had loops
 * note: G MUST already be initialized
 */
int randomGraph48 (graph *G, double p);

/*
 * generates a random directed graph using drand48
 * every edge exists with probability p
 * note: does NOT initializes seed
 * note: does NOT had loops
 * note: G MUST already be initialized
 */
int randomDigraph48 (graph *G, double p);

/*
 * add a node in a LIFO stack
 * returns modified stack pointer or NULL if failed
 */
component *stackComponent (component *list, int x);

/*
 * transpose the graph G in GT
 * return 1 if succeeded, 0 otherwise
 * note: GT must already be initialized
 */
int transposeGraph (graph *G, graph *GT);
