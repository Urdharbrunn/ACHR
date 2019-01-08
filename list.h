/*
** this file is part of a git repository licensed under the
**										GNU GPL LICENSE
** whose integral text is part of the repository itself
**
** header for stacks and queues related function
**
** first created	20/12/2018 (with older materials)
** version 0			20/12/2018
** last updated		08/01/2019
**
** function count -> 20
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
 * struct for implementing fifo queues lists
 */
typedef struct xqueue {
  node *first;
  node *last;
} queue;

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
 * deletes the list, freeing memory
 * returns list pointer, that should be NULL
 */
node *deleteList (node *list);

/*
 * deletes the node p->next, freeing memory
 */
void deleteNodeNext (node *p);

/*
 * prints the list in out stream
 */
void exportList (node *list, FILE *out);

/*
 * prints the list in out stream and terminates it with -1
 */
void exportListTerminator (node *list, FILE *out);

/*
 * returns pointer to last element of list
 */
node *goToLast (node *list);

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
 * return the info of the next (first) element of queue Q
 */
int pop (queue *Q);

/*
 * add a node in a FIFO queue
 * returns 1 in success, 0 in failing
 */
int push (queue *Q, int x);

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