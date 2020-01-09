/*
 * ListTest.c originally Lex.c
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
#include "List.h"

int main(int argc, char *argv[]) {
	FILE* in;        // handle for input file
	FILE* out;       // handle for output file
	int n = 0;       // value for number of lines in input file
	char buffer; // buffer for characters to check for '\0' characters then to hold the longest char
	int longestL = 0; // value for the longest length line in input file then the index of it for the sort
	int currentL = 0; // value for length of current line in input file, then the index of it for the sort
	int j = 0; // value for the current number of characters in char*

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

	// count the number of lines n in the input file
	buffer = getc(in);
	while (buffer != EOF) {
		if (buffer == '\n') {
			++n;
			if (currentL > longestL)
				longestL = currentL;
			currentL = 0;
		} else
			++currentL;
		buffer = getc(in);
	}
	// for the last line that ends in EOF
	++n;

	// reset FILE* in to start of file
	rewind(in);

	// declare string array as 2d char array with appropriate length
	char strings[n][longestL + 1];

	// store strings in string array, working properly
	for (int i = 0; i < n; i++) {
		buffer = getc(in);
		// while still characters left in line, add the char to the string
		while (buffer != '\n' && buffer != EOF) {
			strings[i][j++] = buffer;
			buffer = getc(in);
		}
		// null terminate the string and reset string index counter
		strings[i][j] = '\0';
		j = 0;
	}

	List L = newList();
	for (int i = 0; i < n; i++) {
		moveFront(L);
		// Find appropriate spot to insert string
		while (index(L) != -1 && strcmp(strings[get(L)], strings[i]) <= 0) {
			moveNext(L);
		}
		// If spot found, insert there
		if (index(L) != -1)
			insertBefore(L, i);
		// If no spot found, insert at end
		else
			append(L, i);
	}
	// print the lines into the output file according to the indices stored in List L
	moveFront(L);
	while (index(L) > -1) {
		fprintf(out, "%s\n", strings[get(L)]);
		moveNext(L);
	}
	// finish
	fclose(in);
	fclose(out);
	freeList(&L);
	exit(EXIT_SUCCESS);
}
