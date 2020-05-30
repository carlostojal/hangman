
//
// Carlos Tojal, 2020
// Hangman
//

#include <stdio.h>
#include "helpers.h"

int main() {

	char word[20];
	char guess_word[20];
	printf("** Hangman **\n\n");
	
	// get the word
	do {
		printf("Enter your word: ");
		scanf("%s", word);
		to_uppercase(word);
	} while(!check_word(word));

	// initialize empty guess word
	for(int i = 0; i < strlen(word); i++)
		guess_word[i] = ' ';
	
	do {
		// draw the game
		draw_game(guess_word, strlen(word));
	} while(guess_word_len(guess_word, strlen(word)) != strlen(word));

	return 0;
}
