/*
==============================
Name: 34.server_pthread.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create a concurrent server.
                a. use fork         
                b. use pthread_create       [X]
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void* handle_client(void* arg) {
    int client_socket = *(int*)arg;
    free(arg);
    char buffer[BUFFER_SIZE];

    int valread = read(client_socket, buffer, BUFFER_SIZE-1);
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("Received: %s\n", buffer);
        send(client_socket, buffer, strlen(buffer), 0); // echo back
    }
    close(client_socket);
    return NULL;
}

int main() {
    int server_fd;
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

    printf("Concurrent server (pthread) listening on port %d...\n", PORT);

    while (1) {
        int *client_socket = (int*)malloc(sizeof(int));
        *client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (*client_socket < 0) {
            perror("accept");
            free(client_socket);
            continue;
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_socket);
        pthread_detach(tid); // automatically reclaim resources
    }

    close(server_fd);
    return 0;
}


/*
OUTPUT: 
========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/34$ g++ 34.server_pthread.c -o 34.server_pthread
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/34$ ./34.server_pthread
Concurrent server (pthread) listening on port 8080...
Received: Hello from client!


atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/33$ ./33.client
Message sent to server: Hello from client!

*/