
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
