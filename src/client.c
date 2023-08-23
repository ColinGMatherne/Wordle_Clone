#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

char grid[][5] = {
    {"xxxxx"},
    {"xxxxx"},
    {"xxxxx"},
    {"xxxxx"},
    {"xxxxx"},
};

int main()
{
    char word[6];
    char guess[6];
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    // init socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9090);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	error("Could not connect to server", 1);

    if (recv(sock, &word, 6, 0) <= 0)
	error("Could not communicate with server", 2);

    // close connections
    close(sock);

    for (int i = 0; i < 5; i++) 
    {
    // get guess from user
    printf("Please enter word: ");
    scanf("%s", guess);

    // check users guess
    if (check_guess(guess, word, i))
    {
	printf("Congrats, %s was the right word\n", guess);
	exit(0);
    }

    prompt();
    }
    printf("Game Over, The word was %s\n", word);
    return 0;
}

void prompt()
{
    for (int i = 0; i < 5; i++) 
    {
	for (int j = 0; j < 5; j++)
	    printf("%c ", grid[i][j]);
	printf("\n");
    }
}

void error(char msg[], int code)
{
    perror(msg);
    exit(code);
}

int check_guess(char guess[], char word[], int round)
{
    // check if whole word is right
    if (strcmp(guess, word) == 0)
	return 1;

    // check each letter and change in grid
    for (int i = 0; i < 5; i++) 
    {
	if (guess[i] == word[i])
	    grid[round][i] = guess[i];
    }
    return 0;
}
