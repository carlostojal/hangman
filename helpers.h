
void to_uppercase(char* s) {
	int i;
	for(i = 0; s[i] != '\0'; i++) {
		if(s[i] >= 97)
			s[i] -= 32;
	}
}
