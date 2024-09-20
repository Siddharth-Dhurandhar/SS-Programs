/*
============================================================================
Name : 34a.c
Author : Siddharth Dhurandhar
Description : Write a program to create a concurrent server.
 a. use fork
 b. use pthread_create
Date: 20th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUF_SIZE] = {0};
    int bytes_read;

    // Read message from client
    bytes_read = read(client_socket, buffer, BUF_SIZE);
    printf("Client says: %s\n", buffer);

    // Send response to client
    const char *response = "Hello from server";
    write(client_socket, response, strlen(response));

    // Close the connection
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addr_len = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept new connection
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len)) < 0) {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Create child process to handle the client
        if (fork() == 0) {
            // In child process
            close(server_fd);  // Close the listening socket in child process
            handle_client(client_socket);
            exit(0);  // Exit child process after handling the client
        } else {
            // In parent process
            close(client_socket);  // Close the client socket in parent
        }
    }

    return 0;
}

