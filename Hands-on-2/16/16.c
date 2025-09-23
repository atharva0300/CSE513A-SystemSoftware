/*
==============================
Name: 16.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to send and receive data from parent to child vice versa. Use two way
communication.
Date: 23rd Sept 2025
==============================
*/


// parent_child_twoway.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; // Parent -> Child
    int pipe2[2]; // Child -> Parent
    pid_t pid;
    char buffer[100];

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2

        // Read from parent
        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        // Send reply to parent
        const char *msg = "Hello Parent! This is child.";
        write(pipe2[1], msg, strlen(msg) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);

    } else { // Parent process
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        // Send message to child
        const char *msg = "Hello Child! This is parent.";
        write(pipe1[1], msg, strlen(msg) + 1);
        printf("Parent sent: %s\n", msg);

        // Read reply from child
        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }

    return 0;
}


/*
OUTPUT : 
=====================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/16$ g++ 16.c -o 16
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/16$ ./16
Parent sent: Hello Child! This is parent.
Child received: Hello Child! This is parent.
Parent received: Hello Parent! This is child.

*/