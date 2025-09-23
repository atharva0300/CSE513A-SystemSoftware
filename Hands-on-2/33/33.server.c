/*
==============================
Name: 33.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to communicate between two machines using socket.
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // listen on all interfaces
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Read data from client
    int valread = read(new_socket, buffer, BUFFER_SIZE-1);
    if (valread < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[valread] = '\0';
    printf("Received from client: %s\n", buffer);

    // Close socket
    close(new_socket);
    close(server_fd);

    return 0;
}



/*
OUTPUT: 
============================
TERMINAL 1 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/33$ g++ 33.server.c -o 33.server
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/33$ ./33.server
Server listening on port 8080...
Received from client: Hello from client!


atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/33$ g++ 33.client.c -o 33.client
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/33$ ./33.client
Message sent to server: Hello from client!



*/