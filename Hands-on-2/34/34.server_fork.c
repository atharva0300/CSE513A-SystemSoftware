/*
==============================
Name: 34.server_fork.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create a concurrent server.
                a. use fork         [X]
                b. use pthread_create
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int valread = read(client_socket, buffer, BUFFER_SIZE-1);
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("Received: %s\n", buffer);
        send(client_socket, buffer, strlen(buffer), 0); // echo back
    }
    close(client_socket);
    exit(0); // child process exits
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Concurrent server (fork) listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Child process handles client
            close(server_fd); // child does not need listening socket
            handle_client(client_socket);
        } else if (pid > 0) {
            // Parent process closes client socket and continues
            close(client_socket);
            waitpid(-1, NULL, WNOHANG); // reap zombie children
        } else {
            perror("fork");
            close(client_socket);
        }
    }

    close(server_fd);
    return 0;
}



/*
OUTPUT: 
===============================
TERMINAL 1 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/34$ g++ 34.server_fork.c -o 34.server_fork
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/34$ ./34.server_fork
Concurrent server (fork) listening on port 8080...
Received: Hello from client!


TERMINAL 2 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/33$ ./33.client
Message sent to server: Hello from client!


*/