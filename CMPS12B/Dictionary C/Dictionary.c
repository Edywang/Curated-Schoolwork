//-----------------------------------------------------------------------------
//   Dictionary.c
//   Implementation file for IntegerStack ADT
//   Author: Edwin Wang
//   Author: ekwang
//   Assignment: 12L lab5
//   Created on: May 15th, 2019
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

// private types --------------------------------------------------------------

// NodeObj
typedef struct NodeObj {
	char* key;
	char* value;
	struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor of the Node type
Node newNode(char* x, char* y) {
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->key = x;
	N->value = y;
	N->next = NULL;
	return (N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// DictionaryObj
typedef struct DictionaryObj {
	Node head;
	Node tail;
	int numItems;
} DictionaryObj;

// public functions -----------------------------------------------------------

// newStack()
// constructor for the Stack type
Dictionary newDictionary(void) {
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D!=NULL);
	D->head = NULL;
	D->tail = NULL;
	D->numItems = 0;
	return D;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD) {
	if (pD != NULL && *pD != NULL) {
		if (!isEmpty(*pD))
			makeEmpty(*pD);
		free(*pD);
		*pD = NULL;
	}
}

// isEmpty()
// returns 1 (true) if D is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D) {
	if (D == NULL) {
		fprintf(stderr,
				"Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	return (D->numItems == 0);
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D) {
	return (D->numItems);
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* k) {
	for (Node N = D->head; N != NULL; N = N->next)
		if (!strcmp(k, N->key))
			return N->value;
	return NULL;
}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v) {
	if (lookup(D, k) != NULL) {
		fprintf(stderr,
				"Dictionary Error: insert() called with existing key\n");
		exit(EXIT_FAILURE);
	}
	if (D->numItems == 0) { // No items in Dictionary
		D->tail = newNode(k, v);
		D->head = D->tail;
	} else { // Items already in Dictionary
		D->tail->next = newNode(k, v);
		D->tail = D->tail->next;
	}
	++D->numItems;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k) {
	if (lookup(D, k) == NULL) {
		fprintf(stderr,
				"Dictionary Error: calling delete() on non-existing pair\n");
		exit(EXIT_FAILURE);
	}
	--D->numItems;
	Node N = D->head;
	Node currentNode = D->head;
	if (D->numItems == 0) { // Delete if target is only Node in Dictionary
		D->head = NULL;
		D->tail = NULL;
	} else if (!strcmp(D->head->key, k)) { // Delete if target Node is head
		D->head = N->next;
	} else if (!strcmp(D->tail->key, k)) { // Delete if target Node is tail
		for (; strcmp(currentNode->next->key, k);
				currentNode = currentNode->next)
			;
		N = currentNode->next;
		currentNode->next = NULL;
		D->tail = currentNode;
	} else { // Delete if target in middle
		for (; strcmp(currentNode->next->key, k);
				currentNode = currentNode->next)
			;
		N = currentNode->next;
		currentNode->next = currentNode->next->next;
	}
	freeNode(&N);
}

// pop()
// deletes item at top of D
// pre: !isEmpty(S)
void pop(Dictionary D) {
	Node N;
	if (D == NULL) {
		fprintf(stderr,
				"Dictionary Error: calling pop() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if (D->numItems == 0) {
		fprintf(stderr,
				"Dictionary Error: calling pop() on empty Dictionary\n");
		exit(EXIT_FAILURE);
	}
	N = D->head;
	D->head = D->head->next;
	--D->numItems;
	freeNode(&N);
}

// makeEmpty()
// resets S to the empty state
// pre: none
void makeEmpty(Dictionary D) {
	while (D->numItems > 0)
		pop(D);
	D->tail = NULL;
	D->head = NULL;
}

// printDictionary()
// prints a text representation of S to the file pointed to by out
// pre: none
void printDictionary(FILE* out, Dictionary D) {
	Node N = D->head;
	if (D == NULL) {
		fprintf(stderr,
				"Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < D->numItems; ++i) {
		fprintf(out, "%s %s\n", N->key, N->value);
		N = N->next;
	}
}
