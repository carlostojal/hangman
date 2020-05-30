
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
	return 1;
}

// convert word to uppercase
void to_uppercase(char* s) {
	int i;
	for(i = 0; s[i] != '\0'; i++) {
		if(s[i] >= 97)
			s[i] -= 32;
	}
}

char get_random_char() {
	char c;
	time_t t;
	srand((unsigned) time(&t));
	do {
		c = rand() % 91; // get random character from ASCII code 0 to 90
	} while(c < 65); // repeat while the character is not in A-Z
}

void draw_game(char* word, int word_size) {
	int i;
	for(i = 0; i < word_size; i++) {
		if(word[i] == (int) ' ')
			printf("_ ");
		else
			printf("%c ", word[i]);
	}
	printf("\n");
}

int guess_word_len(char* word, int word_size) {
	int len = 0;
	for(int i = 0; i < word_size; i++) {
		if(word[i] != ' ')
			len++;
	}
	return len;
}
