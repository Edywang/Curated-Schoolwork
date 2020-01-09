//-----------------------------------------------------------------------------
//
// GraphTest.c
// 
// Edwin Wang, ekwang
// CS101 PA3
//
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
/*
 int main(int argc, char* argv[]){
 int i, s, max, min, d, n=35;
 List  C = newList(); // central vertices
 List  P = newList(); // peripheral vertices
 List  E = newList(); // eccentricities

 List L = newList();
 Graph G = NULL;

 // Build graph G
 G = newGraph(n);
 for(i=1; i<n; i++){
 if( i%7!=0 ) addEdge(G, i, i+1);
 if( i<=28  ) addEdge(G, i, i+7);
 }
 addEdge(G, 9, 31);
 addEdge(G, 17, 13);
 addEdge(G, 14, 33);

 // Print adjacency list representation of G
 printGraph(stdout, G);

 // Calculate the eccentricity of each vertex
 for(s=1; s<=n; s++){
 BFS(G, s);
 max = getDist(G, 1);
 for(i=2; i<=n; i++){
 d = getDist(G, i);
 max = ( max<d ? d : max );
 }
 // append(E, max);
 }

 // Determine the Radius and Diameter of G, as well as the Central and
 // Peripheral vertices.
 append(C, 1);
 append(P, 1);
 min = max = front(E);
 moveFront(E);
 moveNext(E);
 for(i=2; i<=n; i++){
 d = get(E);
 if( d==min ){
 append(C, i);
 }else if( d<min ){
 min = d;
 clear(C);
 append(C, i);
 }
 if( d==max ){
 append(P, i);
 }else if( d>max ){
 max = d;
 clear(P);
 append(P, i);
 }
 moveNext(E);
 }

 // Print results
 printf("\n");
 printf("Radius = %d\n", min);
 printf("Central vert%s: ", length(C)==1?"ex":"ices");
 printList(stdout, C);
 printf("\n");
 printf("Diameter = %d\n", max);
 printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
 printList(stdout, P);
 printf("\n");

 // Free objects
 freeList(&C);
 freeList(&P);
 freeList(&E);

 getPath(L, G, max);
 printList(stdout, L);
 makeNull(G);
 printGraph(stdout, G);
 freeGraph(&G);

 return(0);
 }
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>

#include "Graph.h"
#include "List.h"

#define FIRST_TEST DG_getSize
#define MAXSCORE 40

static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
static uint8_t disable_exit_handler;
jmp_buf test_crash;

enum Test_e {
	DG_getSize = 0, // directed graph tests
	DG_getSource,
	DG_getParent,
	DG_getDist,
	DG_getPath,

	UG_getSize, // undirected graph tests
	UG_getSource,
	UG_getParent,
	UG_getDist,
	UG_getPath,

	NUM_TESTS,
};

char *testName(int test) {

	if (test == DG_getSize)
		return "DG_getSize";
	if (test == DG_getSource)
		return "DG_getSource";
	if (test == DG_getParent)
		return "DG_getParent";
	if (test == DG_getDist)
		return "DG_getDist";
	if (test == DG_getPath)
		return "DG_getPath";

	if (test == UG_getSize)
		return "UG_getSize";
	if (test == UG_getSource)
		return "UG_getSource";
	if (test == UG_getParent)
		return "UG_getParent";
	if (test == UG_getDist)
		return "UG_getDist";
	if (test == UG_getPath)
		return "UG_getPath";

	return "";
}

// return 0 if pass otherwise the number of the test that was failed
uint8_t runTest(Graph *pA, List *pL, List *pC, int test) {
	Graph A = *pA;
	List L = *pL;
	List C = *pC;
	switch (test) {

	case DG_getSize: {
		if (getSize(A) != 0)
			return 1;
		addArc(A, 54, 1);
		addArc(A, 54, 2);
		addArc(A, 54, 3);
		addArc(A, 1, 54);
		addArc(A, 1, 55);
		if (getSize(A) != 5)
			return 2;
		BFS(A, 67);
		if (getSize(A) != 5)
			return 3;
		addArc(A, 55, 1);
		if (getSize(A) != 6)
			return 4;
		return 0;
	}
	case DG_getSource: {
		if (getSource(A) != NIL)
			return 1;
		BFS(A, 42);
		if (getSource(A) != 42)
			return 2;
		BFS(A, 88);
		if (getSource(A) != 88)
			return 3;
		return 0;
	}
	case DG_getParent: {
		for (uint8_t i = 1; i <= 100; i++)
			if (getParent(A, i) != NIL)
				return 1;
		addArc(A, 64, 4);
		addArc(A, 64, 3);
		addArc(A, 42, 2);
		addArc(A, 2, 64);
		addArc(A, 4, 2);
		addArc(A, 3, 42);
		BFS(A, 42);
		if (getParent(A, 42) != NIL)
			return 2;
		if (getParent(A, 2) != 42)
			return 3;
		if (getParent(A, 8) != NIL)
			return 4;
		return 0;
	}
	case DG_getDist: {
		for (uint8_t i = 1; i <= 100; i++)
			if (getDist(A, i) != INF)
				return 1;
		addArc(A, 64, 4);
		addArc(A, 64, 3);
		addArc(A, 42, 2);
		addArc(A, 2, 64);
		addArc(A, 4, 2);
		addArc(A, 3, 42);
		BFS(A, 64);
		if (getDist(A, 64) != 0)
			return 2;
		if (getDist(A, 2) != 2)
			return 3;
		BFS(A, 4);
		if (getDist(A, 42) != 4)
			return 4;
		if (getDist(A, 43) != INF)
			return 5;
		BFS(A, 99);
		if (getDist(A, 64) != INF)
			return 6;
		return 0;
	}
	case DG_getPath: {
		addArc(A, 64, 4);
		addArc(A, 64, 3);
		addArc(A, 42, 2);
		addArc(A, 2, 64);
		addArc(A, 4, 2);
		addArc(A, 3, 42);
		BFS(A, 3);
		getPath(L, A, 64);
		append(C, 3);
		append(C, 42);
		append(C, 2);
		append(C, 64);
		if (!equals(L, C))
			return 1;
		moveFront(L);
		BFS(A, 2);
		getPath(L, A, 2);
		append(C, 2);
		if (!equals(L, C))
			return 2;
		getPath(L, A, 99);
		if (equals(L, C))
			return 3;
		clear(L);
		clear(C);
		append(C, NIL);
		BFS(A, 99);
		getPath(L, A, 2);
		if (!equals(C, L))
			return 4;
		return 0;
	}
	case UG_getSize: {
		if (getSize(A) != 0)
			return 1;
		addEdge(A, 54, 1);
		addEdge(A, 54, 2);
		addEdge(A, 54, 3);
		addEdge(A, 1, 55);
		if (getSize(A) != 4)
			return 2;
		BFS(A, 67);
		if (getSize(A) != 4)
			return 3;
		addEdge(A, 55, 2);
		if (getSize(A) != 5)
			return 4;
		return 0;
	}
	case UG_getSource: {
		if (getSource(A) != NIL)
			return 1;
		BFS(A, 42);
		if (getSource(A) != 42)
			return 2;
		BFS(A, 88);
		if (getSource(A) != 88)
			return 3;
		return 0;
	}
	case UG_getParent: {
		for (uint8_t i = 1; i <= 100; i++)
			if (getParent(A, i) != NIL)
				return 1;
		addEdge(A, 64, 4);
		addEdge(A, 64, 3);
		addEdge(A, 42, 2);
		addEdge(A, 2, 64);
		addEdge(A, 4, 2);
		addEdge(A, 3, 42);
		BFS(A, 42);
		if (getParent(A, 42) != NIL)
			return 2;
		if (getParent(A, 64) != 2)
			return 3;
		if (getParent(A, 3) != 42)
			return 4;
		if (getParent(A, 8) != NIL)
			return 5;
		return 0;
	}
	case UG_getDist: {
		for (uint8_t i = 1; i <= 100; i++)
			if (getDist(A, i) != INF)
				return 1;
		addEdge(A, 64, 4);
		addEdge(A, 64, 3);
		addEdge(A, 42, 2);
		addEdge(A, 2, 64);
		addEdge(A, 4, 2);
		addEdge(A, 3, 42);
		BFS(A, 64);
		if (getDist(A, 64) != 0)
			return 2;
		if (getDist(A, 2) != 1)
			return 3;
		BFS(A, 4);
		if (getDist(A, 42) != 2)
			return 4;
		if (getDist(A, 43) != INF)
			return 5;
		BFS(A, 99);
		if (getDist(A, 64) != INF)
			return 6;
		return 0;
	}
	case UG_getPath: {
		addEdge(A, 64, 4);
		addEdge(A, 64, 3);
		addEdge(A, 42, 2);
		addEdge(A, 2, 64);
		addEdge(A, 4, 2);
		addEdge(A, 3, 42);
		BFS(A, 3);
		getPath(L, A, 64);
		append(C, 3);
		append(C, 64);
		if (!equals(L, C))
			return 1;
		moveFront(L);
		BFS(A, 2);
		getPath(L, A, 2);
		append(C, 2);
		if (!equals(L, C))
			return 2;
		getPath(L, A, 99);
		if (equals(L, C))
			return 3;
		clear(L);
		clear(C);
		append(C, NIL);
		BFS(A, 99);
		getPath(L, A, 2);
		if (!equals(C, L))
			return 4;
		return 0;
	}
	}
	return 254;
}

void segfault_handler(int signal) { // everyone knows what this is
	testStatus = 255;
	longjmp(test_crash, 1);
}

void exit_attempt_handler(void) { // only I decide when you are done
	if (disable_exit_handler)
		return; // allow this to be disabled
	testStatus = 255;
	longjmp(test_crash, 2);
}

void abrupt_termination_handler(int signal) { // program killed externally
	testStatus = 255;
	longjmp(test_crash, 3);
}

int main(int argc, char **argv) {
	if (argc > 2 || (argc == 2 && strcmp(argv[1], "-v") != 0)) {
		printf("Usage: %s [-v]", (argc > 0 ? argv[0] : "./GraphTest"));
		exit(1);
	}

	printf("\n"); // more spacing
	if (argc == 2)
		printf("\n"); // consistency in verbose mode

	testsPassed = 0;
	disable_exit_handler = 0;
	atexit(exit_attempt_handler);
	signal(SIGSEGV, segfault_handler);

	for (uint8_t i = FIRST_TEST; i < NUM_TESTS; i++) {
		Graph A = newGraph(100);
		List L = newList();
		List C = newList();
		testStatus = runTest(&A, &L, &C, i);
		freeGraph(&A);
		freeList(&L);
		freeList(&C);
		uint8_t fail_type = setjmp(test_crash);
		if (argc == 2) { // it's verbose mode
			printf("Test %s %s", testName(i),
					testStatus == 0 ? "PASSED" : "FAILED");
			if (testStatus == 255) {
				printf(": due to a %s\n",
						fail_type == 1 ? "segfault" :
						fail_type == 2 ?
								"program exit" : "program interruption");
				printf("\nWARNING: Program will now stop running tests\n\n");
				break;
			} else if (testStatus == 254) {
				printf(": undefined test\n");
			} else if (testStatus != 0) {
				printf(": test %d\n", testStatus);
			} else {
				printf("\n");
			}
		}
		if (testStatus == 0) {
			testsPassed++;
		}
	}

	disable_exit_handler = 1;

	uint8_t totalScore = (MAXSCORE - NUM_TESTS * 4) + testsPassed * 4;

	if (argc == 2 && testStatus != 255)
		printf("\nYou passed %d out of %d tests\n", testsPassed, NUM_TESTS);
	else if (testStatus == 255) {
		totalScore = 10; // charity points
		if (argc == 2)
			printf("Receiving charity points because your program crashes\n");
	}
	printf(
			"\nYou will receive %d out of %d possible points on the GraphTests\n\n",
			totalScore, MAXSCORE);
	exit(0);
	return 0;
}
