#include "server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

int main()
{
    char word[][6] = {"apple", "track"};
    int num = rand_num(sizeof(word)/sizeof(word[0]));

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    struct sockaddr client_addr;

    // init socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9090);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // bind to port
    int addr_len = sizeof(server_addr);
    if (bind(sock, (struct sockaddr *)&server_addr, addr_len) == -1)
	error("Could not bind to port", 1);

    // listen on port
    if (listen(sock, 5) == -1)
	error("Failed to listen on port", 2);
    // accept connections
    addr_len = sizeof(client_addr);

    int client_sock = accept(sock, (struct sockaddr *)&client_addr, (unsigned int * restrict)&addr_len);
    if (client_sock == -1)
	error("Could not accept client connections", 3);

    // send data to client
    if (send(client_sock, word[num], 6, 0) == -1)
	error("Could not send data to client", 4);

    // close connections
    close(sock);
}

void error(char msg[], int code)
{
    perror(msg);
    exit(code);
}

int rand_num(int max)
{
    srand(time(0));
    return rand() % max;
}
