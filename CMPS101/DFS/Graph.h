/*
 * Graph.h
 *
 *  Created on: Aug 12, 2019
 *      Author: Edwin Wang
 *      CMPS101 PA4
 */

#ifndef LIST_H_
#define LIST_H_
#define NIL 0
#define INF -1
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define UNDEF -1

/*** Exported Reference Type ***/

// List
typedef struct ListObj* List;

// Graph
typedef struct GraphObj* Graph;

/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);

/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/* Manipulation procedures */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif /* LIST_H_ */
