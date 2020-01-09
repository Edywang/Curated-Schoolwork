/*
 * Graph.c
 *
 *  Created on: Aug 12, 2019
 *      Author: Edwin Wang
 *      CMPS101 PA4
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
	// Parents
	int* parents;
	// Colors
	int* color;
	// Adjacency List Representation of Graph
	List* adj;
	// Time at which vertex was finished in DFS
	int* finish;
	// Time at which vertex was found in DFS
	int* found;
	// Universal constant used for DFS
	int time;
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
	G->parents = calloc(n + 1, sizeof(int));
	G->color = calloc(n + 1, sizeof(int));
	G->finish = calloc(n + 1, sizeof(int));
	G->found = calloc(n + 1, sizeof(int));
	G->adj = calloc(n + 1, sizeof(List));
	for (int i = 1; i <= n; i++) {
		G->adj[i] = newList();
		G->found[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	return (G);
}

// Frees all heap memory associated with *pG, and sets
// *pG to NULL.
void freeGraph(Graph* pG) {
	if (pG != NULL && *pG != NULL) {
		for (int i = 1; i <= (*pG)->size; i++) {
			freeList(&((*pG)->adj[i]));
		}
		free((*pG)->adj);
		free((*pG)->parents);
		free((*pG)->color);
		free((*pG)->finish);
		free((*pG)->found);
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

int getParent(Graph G, int u) {
	if (u < 1 || u > G->size) {
		fprintf(stderr,
				"Graph Error: calling getParent() with invalid sized argument\n");
		exit(EXIT_FAILURE);
	}
	return G->parents[u];
}

int getDiscover(Graph G, int u) {
	if (u < 1 || u > G->size) {
		fprintf(stderr,
				"Graph Error: calling getParent() with invalid sized argument\n");
		exit(EXIT_FAILURE);
	}
	return G->found[u];
}

int getFinish(Graph G, int u) {
	if (u < 1 || u > G->size) {
		fprintf(stderr,
				"Graph Error: calling getParent() with invalid sized argument\n");
		exit(EXIT_FAILURE);
	}
	return G->finish[u];
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

// DFSVisit()
// Helper function for the DFS() function
// Also defined in 22.3 of Intro to Algorithms CLRS 3rd Ed.
// Note imported values: WHITE = 0, GRAY = 1, BLACK = 2, INF = -1, NIL = 0
void DFSVisit(Graph G, int u, List S) {
	G->found[u] = ++(G->time);
	G->color[u] = GRAY;
	for (moveFront(G->adj[u]); index(G->adj[u]) != -1; moveNext(G->adj[u])) {
		if (G->color[get(G->adj[u])] == WHITE) {
			G->parents[get(G->adj[u])] = u;
			DFSVisit(G, get(G->adj[u]), S);
		}
	}
	G->color[u] = BLACK;
	G->finish[u] = ++(G->time);
	prepend(S, u);
}

// DFS()
// Performs a Depth First Search from source vertex S on Graph G
// Algorithm implemented from 22.3 of Intro to Algorithms CLRS 3rd Ed.
// Note imported values: WHITE = 0, GRAY = 1, BLACK = 2, INF = -1, NIL = 0
// Argument S defines order in which vertices are processed then stores vertices in order of dec. finish times
void DFS(Graph G, List S) {
	// Reset all lists
	for (int i = 1; i <= G->size; i++) {
		G->color[i] = WHITE;
		G->parents[i] = NIL;
	}
	// Set time to 0
	G->time = 0;
	moveFront(S);
	List queue = newList();
	// Main loop of DFS
	for (moveFront(S); index(S) != -1; moveNext(S)) {
		if (G->color[get(S)] == WHITE)
			DFSVisit(G, get(S), queue);
	}

	// Update S to match queue and free queue
	clear(S);
	for (moveFront(queue); index(queue) != -1; moveNext(queue)) {
		append(S, get(queue));
	}
	freeList(&queue);
}

/*** Other operations ***/

Graph transpose(Graph G) {
	Graph transpose = newGraph(G->size);
	for (int i = 1; i <= G->size; i++) {
		for (moveFront(G->adj[i]); index(G->adj[i]) != -1;
				moveNext(G->adj[i])) {
			addArc(transpose, get(G->adj[i]), i);
		}
	}
	return transpose;
}

Graph copyGraph(Graph G) {
	Graph copy = newGraph(G->size);
	for (int i = 1; i <= G->size; i++) {
		for (moveFront(G->adj[i]); index(G->adj[i]) != -1;
				moveNext(G->adj[i])) {
			addArc(copy, i, get(G->adj[i]));
		}
	}
	return copy;
}

void printGraph(FILE* out, Graph G) {
	for (int i = 1; i <= G->size; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}
