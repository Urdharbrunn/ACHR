/*
** this file is part of a git repository licensed under the
** 										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** header for graph related function
** graph are represented with adiacency lists
**
** first created  30/10/2018 (with older materials)
** version 0      30/10/2018
** last updated   03/12/2018
**
** write to dan(dot)salierno(at)stud(dot)uniroma3(dot)it for comments
** Daniele Salierno
*/

/*
 * struct for implementing lists (stacks and queues)
 */
typedef struct xnode {
  int info;
  struct xnode *next;
} node;

/*
 *  struct for implementing fifo queues lists
 */
typedef struct xqueue {
  node *first;
  node *last;
} queue;

typedef struct xgraph {
	int n;
	node **V;
} graph;

/*
 * adds the edge u->v
 * return 1 in success, 0 otherwise
 * note: controls if u, v are in V, but don't if (u,v) already exists
 * note: does NOT add the edge v->u too
 */
int addEdge(graph *G, int u, int v);

/*
 * allocates memory for a graph structure and returns pointer
 */
graph *allocateGraph (void);

/*
 * allocates memory for a queue structure and returns pointer
 */
queue *allocateQueue (void);

/*
 * allocates memory and copy info and next of p
 */
node* copyNode (node *p);

/*
 * returns the pointer to a list identical to list, ordering included
 * note: returns NULL if failed
 */
node *copyListRecursive (node *list);

/*
 * deletes edge u->v from graph
 * return 1 if succeeded, 0 if (u,v) does not exists
 * note: does NOT delete v->u too
 */
int deleteEdge(graph *G, int u, int v);

/*
 * deletes the list, freeing memory
 * returns list pointer, that should be NULL
 */
node *deleteList (node *list);

/*
 * deletes the node p->next, freeing memory
 */
void deleteNodeNext (node *p);

/*
 * prints the graph in out stream
 */
void exportGraph (graph *G, FILE *out);

/*
 * prints the graph in a way readable for importGraph
 */
void exportSelfCompatibleGraph (graph *G, FILE *out);

/*
 * prints the list in out stream
 */
void exportList (node *list, FILE *out);

/*
 * returns pointer to last element of list
 */
node *goToLast (node *list);

/*
 * converts the adiacency list of G in the adiacency matrix M
 * note: M MUST be already initialized
 */
void graphToMatrix (graph *G, int **M);

/*
 * imports a graph from input in G, that must be already allocated.
 * returns 1 if successfull, 0 otherwise
 * note: input must be in the form
  	[# of vertices] [# of elements in list] [list] [#] [list] ...
 */
int importGraph(graph *G, FILE *input);

/*
 * imports a list of n integers with FIFO structure
 * returns the pointer to the first element or NULL if failed
 * note: saves also in Q->last the pointer to last element
 * note: the correct call is Q->first = importQueue (Q, n, input)
 */
node *importQueue (queue *Q, int n, FILE *input);

/*
 * imports a list of n integers with LIFO structure
 * returns the pointer to the stack or NULL if failed
 */
node *importStack (int n, FILE *input);

/*
 * allocates memory in G->V for n vertices
 * return 0 if error, 1 if ok
 */
int initializeGraph (graph *G, int n);

/*
 * insert node q after p
 */
void insertNode (node *p, node *q);

/*
 * reverse the ordering of the list
 * returns the pointer to the new first element
 */
node *invertList (node *list);

/*
 * return di number of element in list
 */
int listLength (node *list);

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
int matrixToGraph (int **M, graph *G);

/*
 * return the info of the next (first) element of queue Q
 */
int pop(queue *Q);

/*
 * add a node in a FIFO queue
 * returns 1 in success, 0 in failing
 */
int push(queue *Q, int x);

/*
 * generates a random graph using drand48
 * every edge exists with probability p
 * note: does NOT initializes seed
 * note: does NOT had loops
 * note: G MUST already be initialized
 */
int randomGraph48(graph *G, double p);

/*
 * generates a random directed graph using drand48
 * every edge exists with probability p
 * note: does NOT initializes seed
 * note: does NOT had loops
 * note: G MUST already be initialized
 */
int randomDigraph48(graph *G, double p);

/*
 * generates a random list of n integer in (a,b) and returns pointer
 */
node *randomList (int n, int a, int b);

/*
 * verifies is k is in the list
 * return pointer to k in list, if present, or NULL
 */
node *search (node *list, int k);

/*
 * searches nodes with k info in list and deletes them
 * returns pointer to first element of the list
 */
node *searchDelete (node *list, int k);

/*
 * verifies if k is in the list
 * return pointer to node whose next is k or NULL
 * note: if the node whit k is the first, returns NULL as well
 */
node *searchNext (node *list, int k);

/*
 * add a node in a LIFO stack
 * returns modified stack pointer
 * note: if failes to allocate memory returns the same pointer and send error to stderr, nothing more
 */
node *stack(node *list, int x);

/*
 * transpose the graph G in GT
 * return 1 if succeeded, 0 otherwise
 * note: GT must already be initialized
 */
int transposeGraph(graph *G, graph *GT);
