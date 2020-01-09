/*
 * Lex.c
 *
 *  Created on: Jun 24, 2019
 *      Author: Edwin Wang
 *      CMPS101 PA1
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
		/* while (index(L) != -1 && strcmp(strings[i], strings[get(L)]) >= 0) {
		 moveNext(L);
		 }
		 if (index(L) > -1)
		 insertBefore(L, i);
		 else
		 append(L, i); */
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

// insertion sort to find lexicographic order and place into Integer List
// while List L is not the same length as the number of lines in FILE* in
	/*while (length(L) < n) {
	 // store first string in buffer unless first string is first in List
	 if (length(L) > 0 && front(L) == 0) {
	 longestL = 1;
	 stringBuffer = strings[1];
	 } else {
	 longestL = 0;
	 stringBuffer = strings[0];
	 }
	 // for each string in strings[], check if it should be placed in next
	 for (currentL = 1; currentL < n; currentL++) {
	 // if no items in List L, search for last element
	 if (length(L) == 0 && strcmp(stringBuffer, strings[currentL]) < 0) {
	 stringBuffer = strings[currentL];
	 longestL = currentL;
	 }
	 // if items in List L then check for last string that is before already added string(s)
	 else if (strcmp(stringBuffer, strings[currentL]) < 0
	 && strcmp(strings[currentL], strings[front(L)]) < 0) {
	 stringBuffer = strings[currentL];
	 longestL = currentL;
	 }
	 }
	 prepend(L, longestL);
	 }*/
	/*
	 // while List L not fully filled
	 while (length(L) <= n) {
	 // if strings in List to compare to, use first string in List L
	 if (length(L) > 0) {
	 stringBuffer = strings[front(L)];
	 longestL = front(L);
	 // otherwise, just use first string in char[][] strings
	 } else {
	 stringBuffer = strings[0];
	 longestL = 0;
	 }
	 // for each string in char[][] strings
	 for (int i = 0; i < n; i++) {
	 // If elements in L
	 if (length(L) > 0 && strcmp(stringBuffer, strings[i]) < 0
	 && strcmp(strings[i], strings[front(L)]) < 0) {
	 stringBuffer = strings[i];
	 longestL = i;
	 // else, I.E. no elements in List L
	 } else if (strcmp(stringBuffer, strings[i]) < 0) {
	 stringBuffer = strings[i];
	 longestL = i;
	 }
	 }
	 prepend(L, longestL);
	 }
	 */
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
