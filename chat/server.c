//
// Created by joachim on 10/6/24.
//

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include "./socketHelper.h"

int main() {
    int serverFD = getSocketFd();
    struct sockaddr_in *srvAddress = createIPv4Address("127.0.0.1", 7585);
 
    // printf("Port: %d\n", srvAddress->sin_port);

    int result = bind(serverFD, (const struct sockaddr *) &srvAddress, sizeof(srvAddress));
    if (result == 0)
        printf("Socket was bound successfully\n");

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