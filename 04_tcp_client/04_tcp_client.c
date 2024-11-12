#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/netcommon.h"

#define PORT "8080"
#define BUFFER_SIZE 1024

const char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
#define WORD_COUNT (sizeof(words) / sizeof(words[0]))

int main() {
    int sock = 0;
    char buffer[BUFFER_SIZE] = {0};
    struct addrinfo hints, *res;

    // Set up hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Get address info
    if (getaddrinfo("127.0.0.1", PORT, &hints, &res) != 0) {
        perror("getaddrinfo error");
        return -1;
    }
    // Create socket
    if (!ISVALIDSOCKET(sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol))) {
        fprintf(stderr, "Socket creation error: %d\n", GETSOCKETERRNO());
        freeaddrinfo(res);
        return -1;
    }

    // Connect to the server
    if (connect(sock, res->ai_addr, res->ai_addrlen)) {
        fprintf(stderr, "Connection failed: %d\n", GETSOCKETERRNO());
        freeaddrinfo(res);
        CLOSESOCKET(sock);
        return -1;
    }

    freeaddrinfo(res);

    // Seed the random number generator
    srand(time(NULL));
    // Select a random word from the list
    const char *random_word = words[rand() % WORD_COUNT];

    // Send the random word to the server
    send(sock, random_word, strlen(random_word), 0);
    printf("Sent: %s\n", random_word);

    // Receive the server's response
    int valread = read(sock, buffer, BUFFER_SIZE);
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("Received: %s\n", buffer);
    } else {
        fprintf(stderr, "Read error: %d\n", GETSOCKETERRNO());
    }

    // Close the socket
    CLOSESOCKET(sock);

    return 0;
}
