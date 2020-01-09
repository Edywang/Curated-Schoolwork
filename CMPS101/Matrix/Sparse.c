/*
 * Sparse.c
 *
 *  Created on: Jul 8, 2019
 *      Author: Edwin Wang
 *      CMPS101 PA2
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "Matrix.h"

int main(int argc, char *argv[]) {
	FILE* in;        // handle for input file
	FILE* out;       // handle for output file
	int size;		 // size of square matrices A and B
	int nonZeroA;    // number of nonzero entries in A
	int nonZeroB;    // number of nonzero entries in B
	int row;         // buffer used to store row number
	int col;         // buffer used to store column number
	double val;      // buffer used to store value

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

	// read first line of integers
	fscanf(in, "%d", &size);
	fscanf(in, "%d", &nonZeroA);
	fscanf(in, "%d", &nonZeroB);

	// initialize matrices
	Matrix A = newMatrix(size);
	Matrix B = newMatrix(size);

	// fill matrices
	for (int i = 0; i < nonZeroA; i++) {
		fscanf(in, "%d", &row);
		fscanf(in, "%d", &col);
		fscanf(in, "%lf", &val);
		changeEntry(A, row, col, val);
	}
	for (int i = 0; i < nonZeroB; i++) {
		fscanf(in, "%d", &row);
		fscanf(in, "%d", &col);
		fscanf(in, "%lf", &val);
		changeEntry(B, row, col, val);
	}

	// done with input
	fclose(in);

	// print output to output file
	fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out, A);
	fprintf(out, "\n");

	fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
	printMatrix(out, B);
	fprintf(out, "\n");

	fprintf(out, "(1.5)*A =\n");
	Matrix scalar = scalarMult(1.5, A);
	printMatrix(out, scalar);
	freeMatrix(&scalar);
	fprintf(out, "\n");

	fprintf(out, "A+B =\n");
	Matrix bothAdd = sum(A, B);
	printMatrix(out, bothAdd);
	freeMatrix(&bothAdd);
	fprintf(out, "\n");

	fprintf(out, "A+A =\n");
	Matrix selfAdd = sum(A, A);
	printMatrix(out, selfAdd);
	freeMatrix(&selfAdd);
	fprintf(out, "\n");

	fprintf(out, "B-A =\n");
	Matrix bothSub = diff(B, A);
	printMatrix(out, bothSub);
	freeMatrix(&bothSub);
	fprintf(out, "\n");

	fprintf(out, "A-A =\n");
	Matrix selfSub = diff(A, A);
	printMatrix(out, selfSub);
	freeMatrix(&selfSub);
	fprintf(out, "\n");

	fprintf(out, "Transpose(A) =\n");
	Matrix trans = transpose(A);
	printMatrix(out, trans);
	freeMatrix(&trans);
	fprintf(out, "\n");

	fprintf(out, "A*B =\n");
	Matrix mult = product(A, B);
	printMatrix(out, mult);
	freeMatrix(&mult);
	fprintf(out, "\n");

	fprintf(out, "B*B =\n");
	Matrix selfMult = product(B, B);
	printMatrix(out, selfMult);
	freeMatrix(&selfMult);
	fprintf(out, "\n");

	// finish
	freeMatrix(&A);
	freeMatrix(&B);
	fclose(out);
	exit(EXIT_SUCCESS);
}
