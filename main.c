
//
// Carlos Tojal, 2020
// Hangman
//

#include <stdio.h>
#include "helpers.h"

int main() {

	char word[20];
	char guess_word[20];
	char guessed_chars[27];
	int wrong_guesses = 0;

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
		char guessed_char;
		do {
			guessed_char = get_random_char();
		} while(word_has_char(guessed_char, guess_word) || guessed_char == get_random_char() || word_has_char(guessed_char, guessed_chars));
		printf("Does your word have the letter '%c'?\n", guessed_char);
		char_concat(guessed_char, guessed_chars);
		if(word_has_char(guessed_char, word)) {
			put_char_in_word(guessed_char, guess_word, word);
			printf("Guessed letter '%c'.\n", guessed_char);
		} else {
			printf("Oops. I failed.\n");
			wrong_guesses++;
			printf("I have failed %d times.\n", wrong_guesses);
		}
		printf("Thinking of other letter...\n");
	} while(guess_word_len(guess_word, strlen(word)) != strlen(word));
	draw_game(guess_word, strlen(word));

	return 0;
}
