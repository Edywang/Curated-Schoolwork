//   DictionaryTest.c
//   Author: Edwin Wang
//   Author: ekwang
//   Assignment: 12L lab5
//   Created on: May 15th, 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
	Dictionary A = newDictionary();
	char* k;
	char* v;
	char* word1[] = { "one", "two", "three", "four", "five", "six", "seven" };
	char* word2[] = { "foo", "bar", "blah", "galumph", "happy", "sad", "blue" };
	int i;

	/*
	 insert(A, word1[0], word2[0]);
	 printDictionary(stdout, A);
	 k = word1[0];
	 v = lookup(A, k);
	 */

	for (i = 0; i < 7; i++) {
		// printf("Inserting (%s, %s)\n", word1[i], word2[i]);
		// printDictionary(stdout, A);
		insert(A, word1[i], word2[i]);
	}

	printDictionary(stdout, A);

	for (i = 0; i < 7; i++) {
		k = word1[i];
		v = lookup(A, k);
		printf("key=\"%s\" %s\"%s\"\n", k,
				(v == NULL ? "not found " : "value="), v);
	}

	// insert(A, "five", "glow"); // error: key collision

	delete(A, "one");
	printDictionary(stdout, A);
	delete(A, "three");
	printDictionary(stdout, A);
	delete(A, "seven");
	printDictionary(stdout, A);

	for (i = 0; i < 7; i++) {
		k = word1[i];
		v = lookup(A, k);
		printf("key=\"%s\" %s\"%s\"\n", k,
				(v == NULL ? "not found " : "value="), v);
	}

	// delete(A, "one");  // error: key not found

	printf("%s\n", (isEmpty(A) ? "true" : "false"));
	printf("%d\n", size(A));
	makeEmpty(A);
	printf("%s\n", (isEmpty(A) ? "true" : "false"));

	freeDictionary(&A);

	return (EXIT_SUCCESS);
}
