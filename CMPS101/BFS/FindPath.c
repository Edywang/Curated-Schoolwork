/*
 * FindPath.c
 *
 *  Created on: Aug 2, 2019
 *      Author: Edwin Wang
 *      CMPS101 PA3
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "List.h"
#include "Graph.h"
#define INF -1

// Explicit declarations of imported stuff

typedef struct GraphObj* Graph;
Graph newGraph();
void addEdge();
void printGraph();
void BFS();
void freeGraph();
int getDist();
List getPath();

int main(int argc, char *argv[]) {
	int buffer;      // buffer for fscanf
	int start;		 // buffer for start of edge
	int end;         // buffer for end of edge
	FILE* in;        // handle for input file
	FILE* out;       // handle for output file
	Graph G;
	List L = newList(); // List used for getPath()

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

	// Add all the edges in
	fscanf(in, "%d %d", &start, &end);
	while (!(start == 0 && end == 0)) {
		addEdge(G, start, end);
		fscanf(in, "%d %d", &start, &end);
	}
	// Print the graph out after graph is complete
	printGraph(out, G);
	fprintf(out, "\n");
	// Run BFS and find shortest path from between input vertices
	fscanf(in, "%d %d", &start, &end);
	while (!(start == 0 && end == 0)) {
		BFS(G, start);
		if (start == end) {
			fprintf(out, "The distance from %d to %d is 0\n", start, end);
			fprintf(out, "A shortest %d-%d path is: %d", start, end, start);
		} else {
			if (getDist(G, end) == INF) {
				fprintf(out, "The distance from %d to %d is infinity\n", start,
						end);
				fprintf(out, "No %d-%d path exists", start, end);
			} else {
				fprintf(out, "The distance from %d to %d is %d\n", start, end,
						getDist(G, end));
				clear(L);
				getPath(L, G, end);
				fprintf(out, "A shortest %d-%d path is: ", start, end);
				printList(out, L);
			}
		}

		fscanf(in, "%d %d", &start, &end);
		if (!(start == 0 && end == 0))
			fprintf(out, "\n\n");
	}

	// finish
	freeGraph(&G);
	freeList(&L);
	fclose(in);
	fclose(out);
	exit(EXIT_SUCCESS);
}
