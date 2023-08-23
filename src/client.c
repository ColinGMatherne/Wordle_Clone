#include "client.h"
#include <stdio.h>
#include <sys/socket.h>

int main()
{

    char word[6];
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

    printf("%s", word);
}

void error(char msg[], int code)
{
    perror(msg);
    exit(code);
}
