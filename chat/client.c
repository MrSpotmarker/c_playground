//
// Created by joachim on 10/6/24.
//

#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "socketHelper.h"

int main() {
    int socketFd;
    struct sockaddr_in *address;

    // Get a socket descriptor
    socketFd = getSocketFd();
    if (socketFd == -1) {
        perror("Failed to get socket descriptor");
        return 1;
    }

    // Create IPv4 address
    address = createIPv4Address("127.0.0.1", 2000);
    if (address == NULL) {
        perror("Failed to create address");
        close(socketFd); // Close the socket on error
        return 1;
    }

    // Connect to the server
    int result = connect(socketFd, (struct sockaddr*) address, sizeof(*address));
    if (result == -1) {
        perror("Failed to connect");
        close(socketFd);
        return 1;
    }

    char *message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";

    // Send the message
    if (send(socketFd, message, strlen(message), 0) == -1) {
        perror("Failed to send message");
        close(socketFd);
        return 1;
    }

    // Receive response
    char buffer[4096]; // Larger buffer to handle potentially large responses
    int bytesReceived = recv(socketFd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived == -1) {
        perror("Failed to receive data");
        close(socketFd);
        return 1;
    }

    // Ensure null termination (in case the response isn't already)
    buffer[bytesReceived] = '\0';

    // Print the response
    printf("Response was:\n%s", buffer);

    // Close the socket
    close(socketFd);

    return 0;
}

