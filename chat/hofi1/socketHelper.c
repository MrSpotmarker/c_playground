#include "socketHelper.h"

#include <string.h>
#include <arpa/inet.h>
#include <malloc.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct sockaddr_in* createIPv4Address (char *ip, int port) {
    printf("Passed port: %d\n", port);
    struct sockaddr_in *address = malloc(sizeof (struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    if (strlen(ip) == 0)
        address->sin_addr.s_addr = INADDR_ANY;
    else
        address->sin_addr.s_addr = htonl(INADDR_ANY);
        //inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    printf("Final port: %d\n", address->sin_port);
    return address;
}

int getSocketFd() { return socket(AF_INET, SOCK_STREAM, 0); }