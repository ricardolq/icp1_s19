#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "../include/netcommon.h"

#define PORT 8080
#define BUFFER_SIZE 1024

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

SOCKET server_fd;
// Signal handler for SIGINT - control + c
void handle_sigint(int sig) {
   CLOSESOCKET(server_fd);
   exit(0);
}

void *handle_client(void *arg) {
    SOCKET new_socket = *(SOCKET *)arg;
    free(arg);

    char buffer[BUFFER_SIZE] = {0};

    // Reading message from client
    int valread = read(new_socket, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    // Converting message to uppercase
    to_uppercase(buffer);

    // Sending uppercase message back to client
    send(new_socket, buffer, strlen(buffer), 0);
    printf("Uppercase message sent: %s\n", buffer);
    CLOSESOCKET(new_socket);
    return NULL;
}

int main() {
    signal(SIGINT, handle_sigint);
    INIT_SOCKETS();
    SOCKET new_socket;
    struct addrinfo hints, *address;

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
    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&client_address, &addrlen);
        if (!ISVALIDSOCKET(new_socket)) {
            fprintf(stderr, "accept failed: %d\n", GETSOCKETERRNO());
            CLOSESOCKET(server_fd);
            exit(EXIT_FAILURE);
        }

        SOCKET *client_socket = malloc(sizeof(SOCKET));
        *client_socket = new_socket;

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, client_socket) != 0) {
            fprintf(stderr, "pthread_create failed\n");
            CLOSESOCKET(new_socket);
            free(client_socket);
            continue;
        }

        pthread_detach(thread_id);
    }
    return 0;
}