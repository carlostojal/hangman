
//
// Carlos Tojal, 2020
// Hangman
//

#include <stdio.h>
#include "helpers.h"

int main() {

	char word[20];
	printf("** Hangman **\n\n");
	
	// get the word
	do {
		printf("Enter your word: ");
		scanf("%s", word);
		to_uppercase(word);
		printf("%s\n", word);
	} while(!check_word(word));

	return 0;
}
