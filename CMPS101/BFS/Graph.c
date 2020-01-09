/*
 * Graph.c
 *
 *  Created on: Aug 2, 2019
 *      Author: Edwin Wang
 *      CMPS101 PA3
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"
#define MAX_ARRAY_SIZE 10000

// Reference types -----------------------------------------------------------

// GraphObj
typedef struct GraphObj {
	// Number of vertices
	int size;
	// Number of edges
	int edges;
	// Last used vertex as source
	int source;
	// Parents
	int* parents;
	// Colors
	int* color;
	// Distance
	int* dist;
	// Adjacency List Representation of Graph
	List* adj;
} GraphObj;

// Explicit declarations of imported functions

List newList(void);
void clear(List L);
void moveNext(List L);
void insertBefore(List L, int data);
void prepend(List L, int data);
void append(List L, int data);
int index(List L);
int get(List L);
int length(List L);
int back(List L);
void deleteBack(List L);
void moveFront(List L);
void freeList(List* pL);
void printList(FILE* out, List L);

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new empty Graph.
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	assert(G != NULL);
	G->size = n;
	G->edges = 0;
	G->source = NIL;
	G->parents = calloc(n + 1, sizeof(int));
	G->color = calloc(n + 1, sizeof(int));
	G->dist = calloc(n + 1, sizeof(int));
	G->adj = calloc(n + 1, sizeof(List));
	for (int i = 1; i <= n; i++) {
		G->adj[i] = newList();
		G->dist[i] = INF;
	}
	return (G);
}

// Frees all heap memory associated with *pG, and sets
// *pG to NULL.
void freeGraph(Graph* pG) {
	if (pG != NULL && *pG != NULL) {
		for (int i = 1; i <= (*pG)->size; i++)
			freeList(&((*pG)->adj[i]));
		free(*pG);
		*pG = NULL;
	}
}

/*** Access functions ***/

int getOrder(Graph G) {
	return G->size;
}

int getSize(Graph G) {
	return G->edges;
}

int getSource(Graph G) {
	return G->source;
}

int getParent(Graph G, int u) {
	if (u < 1 || u > G->size) {
		fprintf(stderr,
				"Graph Error: calling getParent() with invalid sized argument\n");
		exit(EXIT_FAILURE);
	}
	return G->parents[u];
}

int getDist(Graph G, int u) {
	if (u < 1 || u > G->size) {
		fprintf(stderr,
				"Graph Error: calling getParent() with invalid sized argument\n");
		exit(EXIT_FAILURE);
	}
	return G->dist[u];
}

// getPath()
// Takes in List L and inserts the shortest path in G from source to vertex u, or NIL otherwise
void getPath(List L, Graph G, int u) {
	if (G->source == NIL) {
		fprintf(stderr,
				"Graph Error: calling getPath() on graph with no source\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > G->size) {
		fprintf(stderr,
				"Graph Error: calling getParent() with invalid sized argument\n");
		exit(EXIT_FAILURE);
	}
	/*
	 if (G->source == u) {
	 prepend(L, u);
	 return;
	 } else if (G->parents[u] == NIL) {
	 prepend(L, NIL);
	 return;
	 }
	 int i = u;
	 while (i != NIL) {
	 prepend(L, i);
	 if (i == G->source)
	 break;
	 i = G->parents[i];
	 }
	 */
	if (u == G->source)
		append(L, u);
	else if (G->parents[u] == NIL)
		append(L, NIL);
	else {
		getPath(L, G, G->parents[u]);
		append(L, u);
	}
}

/*** Manipulation procedures ***/

// makeNull()
// Resets graph G to null graph
void makeNull(Graph G) {
	for (int i = 1; i <= G->size; i++)
		clear(G->adj[i]);
	G->edges = 0;
}

// addEdge()
// Adds undirected edge between vertices u and v
// I.E. adds u to adjacency list of v and vice versa
void addEdge(Graph G, int u, int v) {
	if (u < 1 || u > G->size || v < 1 || v > G->size) {
		fprintf(stderr,
				"Graph Error: calling addEdge() with invalid sized argument(s)\n");
		exit(EXIT_FAILURE);
	}
// Find the correct position to insert or find that no such position exists
	moveFront(G->adj[u]);
	while (index(G->adj[u]) != -1 && get(G->adj[u]) < v)
		moveNext(G->adj[u]);
	moveFront(G->adj[v]);
	while (index(G->adj[v]) != -1 && get(G->adj[v]) < u)
		moveNext(G->adj[v]);
// If no position exists, append it
	if (index(G->adj[u]) == -1)
		append(G->adj[u], v);
// If a position exists, insert it before the cursor
	else
		insertBefore(G->adj[u], v);
// If no position exists, append it
	if (index(G->adj[v]) == -1)
		append(G->adj[v], u);
// If a position exists, insert it before the cursor
	else
		insertBefore(G->adj[v], u);
// Increment number of edges in graph G
	++G->edges;
}

// addArc()
// Adds directed edge from vertex u to vertex v
// I.E. adds v to adjacency list of u
void addArc(Graph G, int u, int v) {
	if (u < 1 || u > G->size || v < 1 || v > G->size) {
		fprintf(stderr,
				"Graph Error: calling addArc() with invalid sized argument(s)\n");
		exit(EXIT_FAILURE);
	}
// Find the correct position to insert or find that no such position exists
	moveFront(G->adj[u]);
	while (index(G->adj[u]) != -1 && get(G->adj[u]) < v)
		moveNext(G->adj[u]);
// If no position exists, append it
	if (index(G->adj[u]) == -1)
		append(G->adj[u], v);
// If a position exists, insert it before the cursor
	else
		insertBefore(G->adj[u], v);
// Increment number of edges in graph G
	++G->edges;
}

// BFS()
// Performs a Breadth First Search from source vertex S on Graph G
// Algorithm implemented from 22.2 of Intro to Algorithms CLRS 3rd Ed.
// Note imported values: WHITE = 0, GRAY = 1, BLACK = 2, INF = -1, NIL = 0
void BFS(Graph G, int s) {
// Reset all lists
	for (int i = 1; i <= G->size; i++) {
		G->color[i] = WHITE;
		G->dist[i] = INF;
		G->parents[i] = NIL;
	}
// Determine original source
	G->source = s;
	G->color[s] = GRAY;
	G->dist[s] = 0;
	G->parents[s] = NIL;
	List Q = newList();
// Effectively enqueue
	prepend(Q, s);
	while (length(Q) != 0) {
		// Effectively dequeue
		s = back(Q);
		deleteBack(Q);
		// For each vertex adjacent to vertex s
		moveFront(G->adj[s]);
		while (index(G->adj[s]) != -1) {
			// If it's white, process it, finish processing the previous vertex
			if (G->color[get(G->adj[s])] == WHITE) {
				G->color[get(G->adj[s])] = GRAY;
				G->dist[get(G->adj[s])] = G->dist[s] + 1;
				G->parents[get(G->adj[s])] = s;
				prepend(Q, get(G->adj[s]));
			}
			moveNext(G->adj[s]);
		}
		G->color[s] = BLACK;
	}
	freeList(&Q);
}

/*** Other operations ***/

void printGraph(FILE* out, Graph G) {
	for (int i = 1; i <= G->size; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}
