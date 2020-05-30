
#include <stdio.h>
#include "helpers.h"

int main() {

	char word[20];
	printf("** Hangman **\n\n");

	// get the word
	printf("Enter your word: ");
	scanf("%s", word);
	to_uppercase(word);
	printf("%s", word);

	return 0;
}
