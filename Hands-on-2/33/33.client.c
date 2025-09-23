/*
==============================
Name: 33.client.c
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
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *message = "Hello from client!";
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Enter server IP address (change if different machine)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    send(sock, message, strlen(message), 0);
    printf("Message sent to server: %s\n", message);

    close(sock);
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