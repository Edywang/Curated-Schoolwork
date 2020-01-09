/*
 * List.h
 *
 *  Created on: Jul 8, 2019
 *      Author: Edwin Wang
 *      CMPS101 PA2
 */

#ifndef LIST_H_
#define LIST_H_

// Exported reference types ---------------------------------------------------

// NodeObj
typedef struct NodeObj NodeObj;

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

// List
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new empty List.
List newList();

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL);

// newNode()
// constructor of the Node type
Node newNode(void* newData);

// freeNode()
// destructor for the Node type
void freeNode(Node* pN);

// Access functions -----------------------------------------------------------
int isEmpty(List L); // Returns true if number of elements in L is 0, false otherwise.
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
void* front(List L); // Returns front element of L. Pre: length()>0
void* back(List L); // Returns back element of L. Pre: length()>0
void* get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0
// Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets L to its original empty state.
void moveFront(List L); // If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveBack(List L); // If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void movePrev(List L); // If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L); // If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void prepend(List L, void* data); // Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void append(List L, void* data); // Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void insertBefore(List L, void* data); // Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void* data); // Insert new element before cursor.
// Pre: length()>0, index()>=0
void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete(List L); // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0

#endif /* LIST_H_ */
