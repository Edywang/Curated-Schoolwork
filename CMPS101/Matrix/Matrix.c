/*
 * Matrix.c
 *
 *  Created on: Jul 8, 2019
 *      Author: Edwin Wang, ekwang
 *      CMPS101 PA2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Matrix.h"
#include "List.h"
#define MAX_ARRAY_SIZE 10000
#define FALSE 0
#define TRUE 1

// Reference types --------------------------------------------------------------

// ElementObj
typedef struct ElementObj {
	double val;
	int col;
} ElementObj;

// MatrixObj
typedef struct MatrixObj {
	int size;
	int nonzero;
	List rows[MAX_ARRAY_SIZE + 1];
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new Element.
Element newElement(double v, int c) {
	Element E = malloc(sizeof(ElementObj));
	assert(E != NULL);
	E->val = v;
	E->col = c;
	return E;
}

// Frees all heap memory associated with *pE, and sets
// *pE to NULL.
void freeElement(Element* pE) {
	if (pE != NULL && *pE != NULL) {
		free(*pE);
		*pE = NULL;
	}
}

// Creates and returns a new empty Matrix.
Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));
	assert(M != NULL);
	M->size = n;
	M->nonzero = 0;
	for (int i = 1; i <= n; i++)
		M->rows[i] = newList();
	return M;
}

// Frees all heap memory associated with *pM, and sets
// *pM to NULL.
void freeMatrix(Matrix* pM) {
	if (pM != NULL && *pM != NULL) {
		for (int i = 1; i <= (*pM)->size; i++) {
			/* moveFront((*pM)->rows[i]);
			 while (index((*pM)->rows[i]) != -1) {
			 freeElement(get((*pM)->rows[i]));
			 moveNext((*pM)->rows[i]);
			 } */
			freeList(&(((*pM)->rows[i])));
		}
		free(*pM);
		*pM = NULL;
	}
}

// Access functions

// size()
// Return the size of square Matrix M.
int size(Matrix M) {
	if (M == NULL) {
		fprintf(stderr,
				"Matrix Error: calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
	if (M == NULL) {
		fprintf(stderr,
				"Matrix Error: calling NNZ() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->nonzero;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr,
				"Matrix Error: calling equals() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	// Initial condition checks
	if (A->size != B->size || A->nonzero != B->nonzero)
		return FALSE;
	// For each row
	for (int i = 1; i <= A->size; i++) {
		// If that row is different length, return false
		if (A->rows[i]->length != B->rows[i]->length)
			return FALSE;
		// Move cursors on both rows to the front
		moveFront(A->rows[i]);
		moveFront(B->rows[i]);
		// While cursor not off the end of the row
		while (index(A->rows[i]) != -1) {
			// If the elements are different, either column or row of each element in list
			if (((Element) get(A->rows[i]))->col
					!= ((Element) get(B->rows[i]))->col
					|| ((Element) get(A->rows[i]))->val
							!= ((Element) get(B->rows[i]))->val)
				return FALSE;
			// Increment cursor
			moveNext(A->rows[i]);
			moveNext(B->rows[i]);
		}
	}
	// If no differences found, they're the same
	return TRUE;
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M) {
	if (M == NULL) {
		fprintf(stderr,
				"Matrix Error: calling makeZero() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	// Free all elements
	for (int i = 1; i <= M->size; i++) {
		moveFront(M->rows[i]);
		while (index(M->rows[i]) != -1) {
			freeElement(get(M->rows[i]));
			moveNext(M->rows[i]);
		}
	}
	// Clear each row
	for (int i = 1; i <= M->size; i++) {
		moveFront(M->rows[i]);
		while (index(M->rows[i]) != -1) {
			freeElement(get(M->rows[i]));
			moveNext(M->rows[i]);
		}
		clear(M->rows[i]);
	}
	// Reset nonzero
	M->nonzero = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
	if (M == NULL) {
		fprintf(stderr,
				"Matrix Error: calling changeEntry() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (i < 1 || i > M->size || j < 1 || j > M->size) {
		fprintf(stderr,
				"Matrix Error: calling changeEntry() with invalid parameters\n");
		exit(EXIT_FAILURE);
	}
	moveFront(M->rows[i]);
	// Preliminary check
	if (index(M->rows[i]) != -1)
		// While the cursor is in the list and the column is greater than the current column
		while (index(M->rows[i]) != -1 && j > ((Element) get(M->rows[i]))->col) {
			moveNext(M->rows[i]);
		}
	else {
		if (x != 0) {
			append(M->rows[i], newElement(x, j));
			++M->nonzero;
		}
		return;
	}

	// If no spot found, insert at end
	if (index(M->rows[i]) == -1) {
		if (x != 0) {
			append(M->rows[i], newElement(x, j));
			++M->nonzero;
		}
	}
	// If exact spot found, modify or delete that spot
	else if (j == ((Element) get(M->rows[i]))->col) {
		// If value is 0, delete that entry
		if (x == 0) {
			freeElement(get(M->rows[i]));
			delete(M->rows[i]);
			--M->nonzero;
			// If value isn't 0, modify that entry
		} else
			((Element) get(M->rows[i]))->val = x;
		// If next element found, insert before
	} else if (x != 0 && index(M->rows[i]) != -1) {
		insertBefore(M->rows[i], newElement(x, j));
		++M->nonzero;
	}

}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
	if (A == NULL) {
		fprintf(stderr,
				"Matrix Error: calling copy() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(A->size);
// Copy conditions
	B->nonzero = A->nonzero;
// For each row in A
	for (int i = 1; i <= A->size; i++) {
		// Move cursor to front of the current row
		moveFront(A->rows[i]);
		// While that cursor isn't off the end of the row
		while (index(A->rows[i]) != -1) {
			// Append a new element to the current row of B using the current element in A
			append(B->rows[i],
					newElement(((Element) get(A->rows[i]))->val,
							((Element) get(A->rows[i]))->col));
			// Increment cursor
			moveNext(A->rows[i]);
		}
	}
	return B;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
	if (A == NULL) {
		fprintf(stderr,
				"Matrix Error: calling transpose() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(A->size);
// For each row in A
	for (int i = 1; i <= A->size; i++) {
		// Move cursor to front of the current row
		moveFront(A->rows[i]);
		// While that cursor isn't off the end of the row
		while (index(A->rows[i]) != -1) {
			// Append a new element to the correct row of B using the current column in A
			append(B->rows[((Element) get(A->rows[i]))->col],
					newElement(((Element) get(A->rows[i]))->val, i));
			// Increment cursor and NNZ
			++B->nonzero;
			moveNext(A->rows[i]);
		}
	}
	return B;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
	if (A == NULL) {
		fprintf(stderr,
				"Matrix Error: calling scalarMult() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = copy(A);
	if (x == 0) {
		makeZero(B);
	} else {
		for (int i = 1; i <= B->size; i++) {
			moveFront(B->rows[i]);
			while (index(B->rows[i]) != -1) {
				((Element) get(B->rows[i]))->val *= x;
				moveNext(B->rows[i]);
			}
		}
	}
	return B;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr,
				"Matrix Error: calling sum() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (A->size != B->size) {
		fprintf(stderr, "Matrix Error: calling sum() with invalid sizes\n");
		exit(EXIT_FAILURE);
	}
	int same = FALSE;
	if (A == B) {
		B = copy(A);
		same = TRUE;
	}
	Matrix C = newMatrix(A->size);
	// For each row in A and B
	for (int i = 1; i <= A->size; i++) {
		// Move cursor to front of the current row
		moveFront(A->rows[i]);
		moveFront(B->rows[i]);
		// While that cursor isn't off the end of the row
		while (index(A->rows[i]) != -1 && index(B->rows[i]) != -1) {
			// 3 cases
			// Case 1: A's current element before B's current element
			if (((Element) get(A->rows[i]))->col
					< ((Element) get(B->rows[i]))->col) {
				append(C->rows[i],
						newElement(((Element) get(A->rows[i]))->val,
								((Element) get(A->rows[i]))->col));
				moveNext(A->rows[i]);
				++C->nonzero;
			}
			// Case 2: B's current element before A's current element
			else if (((Element) get(A->rows[i]))->col
					> ((Element) get(B->rows[i]))->col) {
				append(C->rows[i],
						newElement(((Element) get(B->rows[i]))->val,
								((Element) get(B->rows[i]))->col));
				moveNext(B->rows[i]);
				++C->nonzero;
			}
			// Case 3: Columns match, then subtract
			else {
				if (((Element) get(A->rows[i]))->val
						+ ((Element) get(B->rows[i]))->val != 0) {
					append(C->rows[i],
							newElement(
									((Element) get(A->rows[i]))->val
											+ ((Element) get(B->rows[i]))->val,
									((Element) get(B->rows[i]))->col));
					++C->nonzero;
				}
				moveNext(A->rows[i]);
				moveNext(B->rows[i]);
			}

		}
		// Finish off the row with more elements (if one exists)
		if (index(A->rows[i]) != -1)
			while (index(A->rows[i]) != -1) {
				// Append new element with current element's value and column into C
				append(C->rows[i],
						newElement(((Element) get(A->rows[i]))->val,
								((Element) get(A->rows[i]))->col));
				moveNext(A->rows[i]);
				++C->nonzero;
			}
		else if (index(B->rows[i]) != -1)
			while (index(B->rows[i]) != -1) {
				// Append new element with current element's value and column into C
				append(C->rows[i],
						newElement(((Element) get(B->rows[i]))->val,
								((Element) get(B->rows[i]))->col));
				moveNext(B->rows[i]);
				++C->nonzero;
			}
	}
	if (same)
		freeMatrix(&B);
	return C;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr,
				"Matrix Error: calling diff() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (A->size != B->size) {
		fprintf(stderr, "Matrix Error: calling diff() with different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix C = newMatrix(A->size);
// For each row in A and B
	for (int i = 1; i <= A->size; i++) {
		// Move cursor to front of the current row
		moveFront(A->rows[i]);
		moveFront(B->rows[i]);
		// While that cursor isn't off the end of the row
		while (index(A->rows[i]) != -1 && index(B->rows[i]) != -1) {
			// 3 cases
			// Case 1: A's current element before B's current element
			if (((Element) get(A->rows[i]))->col
					< ((Element) get(B->rows[i]))->col) {
				append(C->rows[i],
						newElement(((Element) get(A->rows[i]))->val,
								((Element) get(A->rows[i]))->col));
				moveNext(A->rows[i]);
				++C->nonzero;
			}
			// Case 2: B's current element before A's current element
			else if (((Element) get(A->rows[i]))->col
					> ((Element) get(B->rows[i]))->col) {
				append(C->rows[i],
						newElement(-((Element) get(B->rows[i]))->val,
								((Element) get(B->rows[i]))->col));
				moveNext(B->rows[i]);
				++C->nonzero;
			}
			// Case 3: Columns match, then subtract
			else {
				if (((Element) get(A->rows[i]))->val
						- ((Element) get(B->rows[i]))->val != 0) {
					append(C->rows[i],
							newElement(
									((Element) get(A->rows[i]))->val
											- ((Element) get(B->rows[i]))->val,
									((Element) get(B->rows[i]))->col));
					++C->nonzero;
				}
				moveNext(A->rows[i]);
				moveNext(B->rows[i]);
			}

		}
		// Finish off the row with more elements (if one exists)
		if (index(A->rows[i]) != -1)
			while (index(A->rows[i]) != -1) {
				// Append new element with current element's value and column into C
				append(C->rows[i],
						newElement(((Element) get(A->rows[i]))->val,
								((Element) get(A->rows[i]))->col));
				moveNext(A->rows[i]);
				++C->nonzero;
			}
		else if (index(B->rows[i]) != -1)
			while (index(B->rows[i]) != -1) {
				// Append new element with current element's value and column into C
				append(C->rows[i],
						newElement(-((Element) get(B->rows[i]))->val,
								((Element) get(B->rows[i]))->col));
				moveNext(B->rows[i]);
				++C->nonzero;
			}
	}
	return C;
}

// private helper method vectorDot()
// Returns a the dot product of two matrix rows represented by lists P and Q
// Helper method for product()
double vectorDot(List P, List Q) {
	// Set up everything to start computing
	double dot = 0;
	moveFront(P);
	moveFront(Q);
	// Start computing
	while (index(P) != -1 && index(Q) != -1) {
		// If P's column before Q's column, nothing to be multiplied
		if (((Element) get(P))->col < ((Element) get(Q))->col)
			moveNext(P);
		// If Q's column before P's column, nothing to be multiplied
		else if (((Element) get(P))->col > ((Element) get(Q))->col)
			moveNext(Q);
		// If P and Q have the same column, then multiply the two and add to dot product
		else {
			dot += ((Element) get(P))->val * ((Element) get(Q))->val;
			moveNext(P);
			moveNext(Q);
		}
	}
	return dot;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr,
				"Matrix Error: calling product() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (A->size != B->size) {
		fprintf(stderr,
				"Matrix Error: calling product() with different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix trans = transpose(B);
	Matrix C = newMatrix(A->size);
	for (int i = 1; i <= A->size; i++) {
		for (int j = 1; j <= B->size; j++) {
			changeEntry(C, i, j, vectorDot(A->rows[i], trans->rows[j]));
		}
	}
	freeMatrix(&trans);
	return C;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
	if (M == NULL) {
		fprintf(stderr,
				"Matrix Error: calling printMatrix() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (M->nonzero == 0)
		return;
	// For each row in M
	for (int i = 1; i <= M->size; i++) {
		// Move cursor to front
		moveFront(M->rows[i]);
		if (length(M->rows[i]) != 0)
			fprintf(out, "%u: ", i);
		// While still elements to print, print and increment cursor
		while (index(M->rows[i]) != -1) {
			fprintf(out, "(%d, %.1f) ", ((Element) get(M->rows[i]))->col,
					((Element) get(M->rows[i]))->val);
			moveNext(M->rows[i]);
		}
		if (length(M->rows[i]) != 0)
			fprintf(out, "\n");
	}
}
