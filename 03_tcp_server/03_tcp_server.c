#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/netcommon.h"

#define PORT 8080
#define BUFFER_SIZE 1024

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int server_fd, new_socket;
    struct addrinfo hints, *address;
    char buffer[BUFFER_SIZE] = {0};

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, "8080", &hints, &address) != 0) {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    // Creating socket file descriptor
    server_fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
    if (!ISVALIDSOCKET(server_fd)) {
        fprintf(stderr, "socket failed: %d\n", GETSOCKETERRNO());
        exit(EXIT_FAILURE);
    }

    // Binding the socket to the network address and port
    if (bind(server_fd, address->ai_addr, address->ai_addrlen) < 0) {
        fprintf(stderr, "bind failed: %d\n", GETSOCKETERRNO());
        CLOSESOCKET(server_fd);
        exit(EXIT_FAILURE);
        }

        // Listening for incoming connections
        if (listen(server_fd, 3) < 0) {
        fprintf(stderr, "listen failed: %d\n", GETSOCKETERRNO());
        CLOSESOCKET(server_fd);
        exit(EXIT_FAILURE);
        }

        printf("Server listening on port %d\n", PORT);

        // Accepting incoming connection
        struct sockaddr_in client_address;
        socklen_t addrlen;
        new_socket = accept(server_fd, (struct sockaddr *)&client_address, &addrlen);
        if (!ISVALIDSOCKET(new_socket)) {
        fprintf(stderr, "accept failed: %d\n", GETSOCKETERRNO());
        CLOSESOCKET(server_fd);
        exit(EXIT_FAILURE);
        }

        // Reading message from client
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        printf("Received: %s\n", buffer);

        // Converting message to uppercase
        to_uppercase(buffer);

        // Sending uppercase message back to client
        send(new_socket, buffer, strlen(buffer), 0);
        printf("Uppercase message sent: %s\n", buffer);

        // Closing the socket
        CLOSESOCKET(new_socket);
        CLOSESOCKET(server_fd);

    return 0;
}