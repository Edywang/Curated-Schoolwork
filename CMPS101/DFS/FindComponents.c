/*
 * FindComponents.c
 *
 *  Created on: Aug 12, 2019
 *      Author: Edwin Wang
 *      CMPS101 PA4
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "List.h"
#include "Graph.h"
#define INF -1
int total = 0;
int count = 1;

// Explicit declarations of imported stuff

typedef struct GraphObj* Graph;
Graph newGraph();
void addArc();
void printGraph();
void freeGraph();
void DFS();
int getDiscover();
int getFinish();
int index(List L);
Graph transpose();

void SCC(FILE* out, Graph G, List S, List components, int min, int max) {
	// Retrieve vertex to be considered and prepare for next recursion
	int i = get(S);
	moveNext(S);
	if (min < getDiscover(G, i) && max > getFinish(G, i)) {
		// If not done, keep recurring
		if (index(S) != -1)
			SCC(out, G, S, components, min, max);
		// If done, print total
		else
			fprintf(out, "\nG contains %d strongly connected component%s:\n",
					total, total == 1 ? "" : "s");
		prepend(components, i);
	} else {
		++total;
		min = getDiscover(G, i);
		max = getFinish(G, i);
		// If not done, keep recurring
		if (index(S) != -1)
			SCC(out, G, S, components, min, max);
		// If done, print total
		else
			fprintf(out, "\nG contains %d strongly connected component%s:\n",
					total, total == 1 ? "" : "s");
		prepend(components, i);
		// Print the component out and clear the list
		fprintf(out, "Component %d: ", count++);
		printList(out, components);
		fprintf(out, "\n");
		clear(components);
	}
}

int main(int argc, char *argv[]) {
	int buffer;      // buffer for fscanf
	int start;		 // buffer for start of edge
	int end;         // buffer for end of edge
	FILE* in;        // handle for input file
	FILE* out;       // handle for output file
	Graph G;

// check command line for correct number of arguments
	if (argc != 3) {
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

// open input file for reading
	if ((in = fopen(argv[1], "r")) == NULL) {
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

// open output file for writing
	if ((out = fopen(argv[2], "w")) == NULL) {
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

// Find number of vertices
	fscanf(in, "%d", &buffer);
// Create a graph with the correct number of vertices
	G = newGraph(buffer);

// Add all the arcs in (note arcs, not edges as this is a directed graph)
	fscanf(in, "%d %d", &start, &end);
	while (!(start == 0 && end == 0)) {
		addArc(G, start, end);
		fscanf(in, "%d %d", &start, &end);
	}
// Print the graph out after graph is complete
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");

	List S = newList();
	for (int i = 1; i <= buffer; i++)
		append(S, i);

// Algorithm outlined on page 617 of CLRS 3rd Edition
// Step 1: Call DFS(G) to compute finishing times for each vertex
	DFS(G, S);
// Step 2: Compute transpose of T
	Graph T = transpose(G);
// Step 3: Call DFS(T) but consider vertices in order of decreasing finish time
	DFS(T, S);
// Step 4: Now output the vertices of each tree as an SCC using result of step 3
	List components = newList();
	moveFront(S);
	SCC(out, G, S, components, 0, 0);

// finish
	freeGraph(&G);
	freeList(&S);
	fclose(in);
	fclose(out);
	exit(EXIT_SUCCESS);
}
