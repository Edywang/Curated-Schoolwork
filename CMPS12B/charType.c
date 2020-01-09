/*
 * charType.c
 *
 *  Created on: May 2, 2019
 *      Author: Edwin Wang
 *  Assignment: CS12M lab4
 *		CruzID: ekwang
 * Description:
 // identifies alpha-numeric characters from each line of the input file
 // and places the alphabetical characters and count of each type in the output file.
 //
 // Recall the program FileIO.c from lab3 used fscanf to parse words in
 // a file and then process them.  However the function fscanf is not
 // appropriate when you want to read an entire line from a file as a
 // string.  In this program we use another IO function from stdio.h called
 // fgets() for this purpose.  Its prototype is:
 //
 //         char* fgets(char* s, int n, FILE* stream);
 //
 // fgets() reads up to n-1 characters from stream and places them in
 // the character array ponted to by s.  Characters are read until either
 // a newline or an EOF is read, or until the specified limit is reached.
 // After the characters have been read, a null character '\0' is placed
 // in the array immediately after the last character read.  A newline
 // character in stream will be retained and placed in s.  If successful,
 // fgets() returns the string s, and a NULL pointer is returned upon
 // failure.  See fgets in section 3c of the unix man pages for more.
 //
 //-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

// takes the input string s, and copies its characters into the appropriate output character arrays a (alphabetic),
// d (digits), p (punctuation), or w (whitespace). The output arrays will each be terminated by the null character
// '\0', making them into valid C strings.
void extract_chars(char* s, char* a, char* d, char* p, char* w) {
	int i = 0, numAlpha = 0, numDigit = 0, numPunct = 0, numWhite = 0;
	char *current = calloc(1, sizeof(char));
	assert(current != NULL);
	while (s[i] != '\0' && i < MAX_STRING_LENGTH) {
		if (isalpha((int) s[i]))
			a[numAlpha++] = s[i];
		if (isdigit((int) s[i]))
			d[numDigit++] = s[i];
		if (ispunct((int) s[i]))
			p[numPunct++] = s[i];
		if (isspace((int) s[i]))
			w[numWhite++] = s[i];
		++i;
	}
	free(current);
	a[numAlpha] = '\0';
	d[numDigit] = '\0';
	p[numPunct] = '\0';
	w[numWhite] = '\0';
}

// function main which takes command line arguments
int main(int argc, char* argv[]) {
	FILE* in;        // handle for input file
	FILE* out;       // handle for output file
	int lineNum = 1; // integer holding the current line number
	char* line;      // string holding input line
	char* alpha;     // string holding all alphabetical chars
	char* digit;     // string holding all digit chars
	char* punct;     // string holding all punctuation chars
	char* white;     // string holding all whitespace chars
	char* plural;    // string holding the correct plurality of "character"

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

	// allocate strings line, alpha, digit, punctuation, and white on the heap
	line = calloc(MAX_STRING_LENGTH + 1, sizeof(char));
	alpha = calloc(MAX_STRING_LENGTH + 1, sizeof(char));
	digit = calloc(MAX_STRING_LENGTH + 1, sizeof(char));
	punct = calloc(MAX_STRING_LENGTH + 1, sizeof(char));
	white = calloc(MAX_STRING_LENGTH + 1, sizeof(char));
	plural = "characters";
	assert(
			line != NULL && alpha != NULL && digit != NULL && punct != NULL && white != NULL && plural != NULL);

	// read each line in input file, extract alpha-numeric characters
	while (fgets(line, MAX_STRING_LENGTH, in) != NULL) {
		extract_chars(line, alpha, digit, punct, white);
		fprintf(out, "line %d contains:\n", lineNum);
		++lineNum;
		if (strlen(alpha) == 1)
			plural = "character";
		else
			plural = "characters";
		fprintf(out, "%u alphabetic %1s: %1s\n", strlen(alpha), plural,
				alpha);
		if (strlen(digit) == 1)
			plural = "character";
		else
			plural = "characters";
		fprintf(out, "%u numeric %1s: %1s\n", strlen(digit), plural, digit);
		if (strlen(punct) == 1)
			plural = "character";
		else
			plural = "characters";
		fprintf(out, "%u punctuation %1s: %1s\n", strlen(punct), plural,
				punct);
		if (strlen(white) == 1)
			plural = "character";
		else
			plural = "characters";
		fprintf(out, "%u whitespace %1s: %1s\n", strlen(white), plural, white);
	}

	// free heap memory
	free(line);
	free(alpha);
	free(digit);
	free(punct);
	free(white);

	// close input and output files
	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}

