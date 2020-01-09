/*
 * Dictionary.c
 *
 *  Created on: Jun 3, 2019
 *      Author: Edwin Wang - ekwang
 *      Assignment: CS12B PA5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"
#define tableSize 101

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

// DictionaryObj
typedef struct DictionaryObj {
	Node lists[tableSize];
	int numItems;
} DictionaryObj;

// freeNode()
// destructor for the Node type
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
	int sizeInBits = 8 * sizeof(unsigned int);
	shift = shift & (sizeInBits - 1);
	if (shift == 0)
		return value;
	return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
	unsigned int result = 0xBAE86554;
	while (*input) {
		result ^= *input++;
		result = rotate_left(result, 5);
	}
	return result;
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key) {
	return pre_hash(key) % tableSize;
}

// public functions -----------------------------------------------------------

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void) {
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D!=NULL);
	for (int i = 0; i < tableSize; ++i)
		D->lists[i] = NULL;
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
	for (Node N = D->lists[hash(k)]; N != NULL; N = N->next) {
		if (!strcmp(k, N->key))
			return N->value;
	}
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
	++D->numItems;
	Node N = D->lists[hash(k)];
	D->lists[hash(k)] = newNode(k, v);
	D->lists[hash(k)]->next = N;
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
	Node N = D->lists[hash(k)];
	Node nNext = N->next;
	if (!strcmp(N->key, k)) { // Delete if target Node is head
		D->lists[hash(k)] = N->next;
		freeNode(&N);
	} else { // Delete if target Node isn't head
		for (; nNext->next != NULL; N = N->next) {
			nNext = N->next;
			if (!strcmp(nNext->key, k)) {
				N->next = nNext->next;
				freeNode(&nNext);
				break;
			}
		}
	}
	/* else if (!strcmp(D->tail->key, k)) { // Delete if target Node is tail
	 for (; N->next != D->tail; N = N->next)
	 ;
	 freeNode(&D->tail);
	 D->tail = N;
	 } else
	 for (; N->next != NULL; N = N->next) { // Delete if target in middle
	 if (!strcmp(N->next->key, k)) {
	 Node newNext = N->next->next;
	 freeNode(&N->next);
	 N->next = newNext;
	 break;
	 }
	 } */
}

// makeEmpty()
// resets S to the empty state
// pre: none
void makeEmpty(Dictionary D) {
	for (int i = 0; i < tableSize; ++i) {
		while (D->lists[i] != NULL) {
			Node N = D->lists[i];
			D->lists[i] = D->lists[i]->next;
			freeNode(&N);
		}
	}
	D->numItems = 0;
}

// printDictionary()
// prints a text representation of S to the file pointed to by out
// pre: none
void printDictionary(FILE* out, Dictionary D) {
	if (D == NULL) {
		fprintf(stderr,
				"Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < tableSize; ++i) {
		Node N = D->lists[i];
		while (N != NULL) {
			fprintf(out, "%s %s\n", N->key, N->value);
			N = N->next;
		}
	}
}
