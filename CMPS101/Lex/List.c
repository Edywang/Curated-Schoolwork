/*
 * List.c
 *
 *  Created on: Jun 24, 2019
 *      Author: Edwin Wang
 *      CMPS101 PA1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"

// private types --------------------------------------------------------------

// NodeObj
typedef struct NodeObj {
	int data;
	struct NodeObj* next;
	struct NodeObj* previous;
} NodeObj;

// Node
typedef NodeObj* Node;

// ListObj
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int index;
	int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// constructor of the Node type
Node newNode(int number) {
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->data = number;
	N->next = NULL;
	N->previous = NULL;
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

// Creates and returns a new empty List.
List newList(void) {
	List L = malloc(sizeof(ListObj));
	assert(L != NULL);
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return (L);
}

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {
		if (!isEmpty(*pL))
			clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

int isEmpty(List L) {
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling isEmpty() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->length == 0);
}

int length(List L) { // Returns the number of elements in L.
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return L->length;
}

int index(List L) { // Returns index of cursor element if defined, -1 otherwise.
	if (L == NULL) {
		fprintf(stderr, "List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return L->index;
}

int front(List L) { // Returns front element of L. Pre: length()>0
	if (L == NULL) {
		fprintf(stderr, "List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0)
		fprintf(stderr,
				"List Error: calling front() on empty List reference\n");
	return L->front->data;
}

int back(List L) { // Returns back element of L. Pre: length()>0
	if (L == NULL) {
		fprintf(stderr, "List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0)
		fprintf(stderr, "List Error: calling back() on empty List reference\n");
	return L->back->data;
}

int get(List L) { // Returns cursor element of L. Pre: length()>0, index()>=0
	if (L == NULL) {
		fprintf(stderr, "List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0)
		fprintf(stderr, "List Error: calling get() on empty List reference\n");
	if (L->cursor == NULL)
		fprintf(stderr, "List Error: calling get() on NULL Cursor reference\n");
	return L->cursor->data;
}

int equals(List A, List B) { // Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
	int eq = 0;
	Node N = NULL;
	Node M = NULL;
	if (A == NULL || B == NULL) {
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
	}
	eq = (A->length == B->length);
	N = A->front;
	M = B->front;
	while (eq && N != NULL) {
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

// Manipulation procedures ----------------------------------------------------

void clear(List L) { // Resets L to its original empty state.
	if (L == NULL) {
		fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N;
	while (L->length > 0) {
		N = L->front;
		if (L->length > 1) {
			L->front = L->front->next;
		} else {
			L->front = L->back = NULL;
		}
		--L->length;
		L->index = -1;
		L->cursor = NULL;
		freeNode(&N);
	}
}

void moveFront(List L) { // If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->front != NULL) {
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L) { // If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length > 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

void movePrev(List L) { // If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L != NULL) {
		if (L->cursor == L->front) {
			L->cursor = NULL;
			L->index = -1;
		} else {
			L->cursor = L->cursor->previous;
			L->index--;
		}
	}
}

void moveNext(List L) { // If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor != NULL) {
		if (L->cursor == L->back) {
			L->cursor = NULL;
			L->index = -1;
		} else {
			L->cursor = L->cursor->next;
			L->index++;
		}
	}
}
void prepend(List L, int data) { // Insert new element into L. If L is non-empty,
// insertion takes place before front element.
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = L->front;
	L->front = newNode(data);
	if (L->length == 0)
		L->back = L->front;
	else
		N->previous = L->front;
	L->front->next = N;
	++L->length;
	if (L->cursor != NULL)
		++L->index;
}

void append(List L, int data) { // Insert new element into L. If L is non-empty,
// insertion takes place after back element.
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		L->front = L->back = newNode(data);
	} else {
		L->back->next = newNode(data);
		L->back->next->previous = L->back;
		L->back = L->back->next;
	}
	++L->length;
}

void insertBefore(List L, int data) { // Insert new element before cursor.
// Pre: length()>0, index()>=0
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr,
				"List Error: calling insertBefore() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == NULL || L->index < 0) {
		fprintf(stderr,
				"List Error: calling insertBefore() on NULL Cursor reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = L->cursor->previous;
	L->cursor->previous = newNode(data);
	L->cursor->previous->next = L->cursor;
	L->cursor->previous->previous = N;
	if (N != NULL)
		N->next = L->cursor->previous;
	else
		L->front = L->cursor->previous;
	++L->length;
	++L->index;
}

void insertAfter(List L, int data) { // Insert new element before cursor.
// Pre: length()>0, index()>=0
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr,
				"List Error: calling insertAfter() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == NULL) {
		fprintf(stderr,
				"List Error: calling insertAfter() on NULL Cursor reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = L->cursor->next;
	L->cursor->next = newNode(data);
	L->cursor->next->previous = L->cursor;
	L->cursor->next->next = N;
	if (N != NULL)
		N->previous = L->cursor->next;
	else
		L->back = L->cursor->next;
	++L->length;
}

void deleteFront(List L) { // Delete the front element. Pre: length()>0
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr,
				"List Error: calling deleteFront() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 1)
		clear(L);
	else {
		Node N = L->front;
		L->front = L->front->next;
		L->front->previous = NULL;
		freeNode(&N);
		--L->length;
		if (L->cursor != NULL)
			--L->index;
		else
			L->index = -1;
	}
}

void deleteBack(List L) { // Delete the back element. Pre: length()>0
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr,
				"List Error: calling deleteBack() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 1)
		clear(L);
	else {
		if (L->cursor == L->back)
			L->index = -1;
		Node N = L->back;
		L->back = L->back->previous;
		L->back->next = NULL;
		freeNode(&N);
		--L->length;
	}
}

void delete(List L) { // Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == NULL) {
		fprintf(stderr,
				"List Error: calling delete() on NULL Cursor reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr,
				"List Error: calling delete() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == 0) {
		deleteFront(L);
	} else if (L->index == L->length - 1) {
		deleteBack(L);
	} else {
		L->cursor->previous->next = L->cursor->next;
		--L->length;
		freeNode(&L->cursor);
		L->index = -1;
	}
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L) { // Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = L->front;
	while (N != NULL) {
		printf("%d ", N->data);
		N = N->next;
	}
}
List copyList(List L) { // Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
	if (L == NULL) {
		fprintf(stderr,
				"List Error: calling copyList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	List newL = newList();
	Node N = L->front;
	while (N != NULL) {
		append(newL, N->data);
		N = N->next;
	}
	return newL;
}
