
//
// Carlos Tojal, 2020
// Hangman
//

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "helpers.h"

#define PORT 2911

int main() {
	
	char chars[25];
	char word[20];
	char guess_word[20];
	char guessed_chars[27];
	int wrong_guesses = 0;

	char username[20];
	char opponent[20];

	int game_mode, online_mode;

	// networking variables
	int server_fd, new_socket, valread;
	int sock;
	int opt = 1;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};

	game_mode = menu();

	if(game_mode != 0) {

		if(game_mode == 2) {
			online_mode = online_menu();
			if(online_mode == 0) {
				game_mode = 1;
			} else {
				// online mode
				printf("\nEnter your username: ");
				scanf("%s", username);
				// server mode
				if(online_mode == 1) {
					// Creating socket file descriptor 
					if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
					{ 
						perror("socket failed"); 
						exit(EXIT_FAILURE); 
					} 
					
					// Forcefully attaching socket to the port 8080 
					if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
																&opt, sizeof(opt))) 
					{ 
						perror("setsockopt"); 
						exit(EXIT_FAILURE); 
					} 
					address.sin_family = AF_INET; 
					address.sin_addr.s_addr = INADDR_ANY; 
					address.sin_port = htons( PORT ); 
					
					// Forcefully attaching socket to the port 8080 
					if (bind(server_fd, (struct sockaddr *)&address,  
												sizeof(address))<0) 
					{ 
						perror("bind failed"); 
						exit(EXIT_FAILURE); 
					} 
					if (listen(server_fd, 3) < 0) 
					{ 
						perror("listen"); 
						exit(EXIT_FAILURE); 
					} 
					printf("\nWaiting for player connection...\n");
					if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
									(socklen_t*)&addrlen))<0) 
					{ 
						perror("accept"); 
						exit(EXIT_FAILURE); 
					}
					// get opponent name and send player name
					valread = read(new_socket, buffer, 1024);
					strcpy(opponent, buffer);
					printf("%s joined.\n", opponent);
					send(new_socket, username, strlen(username), 0);
				} else {
					// client mode
					char ip_address[30];
					printf("\nHost IP address: ");
					scanf("%s", ip_address);
					if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
					{ 
						printf("\n Socket creation error \n"); 
						return -1; 
					} 
				
					address.sin_family = AF_INET; 
					address.sin_port = htons(PORT); 
					
					// Convert IPv4 and IPv6 addresses from text to binary form 
					if(inet_pton(AF_INET, ip_address, &address.sin_addr)<=0)  
					{ 
						printf("\nInvalid address/ Address not supported \n"); 
						return -1; 
					} 
				
					if (connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0) 
					{ 
						printf("\nConnection Failed \n"); 
						return -1; 
					} 
					send(sock , username , strlen(username) , 0 ); 
					valread = read(sock , buffer, 1024); 
					strcpy(opponent, buffer);
					printf("\nJoined %s's game.\n", opponent);
				}
			}
		}
		
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
