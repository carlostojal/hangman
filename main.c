
//
// Carlos Tojal, 2020
// Hangman
//

#include <stdio.h>
#include "helpers.h"

int main() {
	
	char chars[25];
	char word[20];
	char guess_word[20];
	char guessed_chars[27];
	int wrong_guesses = 0;
	int game_mode = -1;

	get_chars(chars); // fills char array with all chars

	game_mode = menu();

	if(game_mode != 0) {
	
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
			printf("Getting letter...\n");
			char guessed_char;
			do {
				guessed_char = get_random_char();
			} while(word_has_char(guessed_char, guess_word) || word_has_char(guessed_char, guessed_chars));
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
		} while(guess_word_len(guess_word, strlen(word)) != strlen(word));
		printf("\nI won! %d fails.\n", wrong_guesses);
		draw_game(guess_word, strlen(word));
	}

	return 0;
}
