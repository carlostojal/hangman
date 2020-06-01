
#include <stdlib.h>
#include <time.h>
#include <string.h>

//
// Carlos Tojal, 2020
// Hangman
//

// find special characters in the word
int check_word(char *s) {
	int i;
	for(i = 0; s[i] != '\0'; i++) {
		if(s[i] < 65 || (s[i] > 90 && s[i] < 97) || s[i] > 122)
			return 0;
	}
	if(i > 20)
		return 0;
	return 1;
}

void get_chars(char* chars) {
}

// convert word to uppercase
void to_uppercase(char* s) {
	for(int i = 0; s[i] != '\0'; i++) {
		if(s[i] >= 97)
			s[i] -= 32;
	}
}

// add char to end of string
void char_concat(char c, char* s) {
	int i;
	for(i = 0; i < strlen(s); i++) {}
	s[i] = c;
}

// get random char to use to guess word
char get_random_char() {
	char chars[25];
	time_t t;
	srand((unsigned) time(&t));
	for(int i = 65; i <= 90; i++) // fill array with all chars
		chars[i - 65] = i;
	return chars[rand() % 26]; // return random char from array
}

// draws the game
void draw_game(char* word, int word_size) {
	printf("\n");
	for(int i = 0; i < word_size; i++) {
		if(word[i] == (int) ' ')
			printf("_ ");
		else
			printf("%c ", word[i]);
	}
	printf("\n");
}

// gets the number of characters already guessed
int guess_word_len(char* word, int word_size) {
	int len = 0;
	for(int i = 0; i < word_size; i++) {
		if(word[i] != ' ')
			len++;
	}
	return len;
}

// check if the word has a char
int word_has_char(char c, char* word) {
	for(int i = 0; i < strlen(word); i++) {
		if(word[i] == c)
			return 1;
	}
	return 0;
}

// puts the guessed char in the guess word
void put_char_in_word(char c, char* guess_word, char* original_word) {
	for(int i = 0; i < strlen(original_word); i++) {
		if(original_word[i] == c)
			guess_word[i] = c;
	}
}
