//
// Created by joachim on 10/6/24.
//

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include "./socketHelper.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>



#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
    int serverFD = socket(AF_INET, SOCK_STREAM, 0); 
    //struct sockaddr_in *srvAddress = createIPv4Address("127.0.0.1", 7585);
    struct sockaddr_in srvAddress;
    //memset(&srvAddress, '0', sizeof(srvAddress));

    srvAddress.sin_family = AF_INET;
    srvAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    srvAddress.sin_port = htons(7585);
 
    // printf("Port: %d\n", srvAddress->sin_port);

    if (bind(serverFD, (struct sockaddr*)&srvAddress, sizeof(srvAddress))) {
        handle_error("bind");
    }
    /* if (result == 0)
        printf("Socket was bound successfully\n");
    */

    int listenResult = listen(serverFD, 10);
    if (listenResult == 0)
        printf("Listening was bound successfully\n");

    struct sockaddr_in clientAddress;
    uint clientAddressSize = sizeof clientAddress;
    int clientSocketFD = accept(serverFD, (struct sockaddr *) &clientAddress, &clientAddressSize);

    // Receive response
    char buffer[4096]; // Larger buffer to handle potentially large responses
    long bytesReceived = recv(clientSocketFD, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived == -1) {
        perror("Failed to receive data");
        close(clientSocketFD);
        return 1;
    }

    return 0;
}