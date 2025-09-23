/*
==============================
Name: 15.c
Author: Atharva Ratnadeep Pingale
Description: Write a simple program to send some data from parent to the child process.
Date: 23rd Sept 2025
==============================
*/


// parent_to_child.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    const char *message = "Hello Child! This is parent.";
    char buffer[100];

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork child
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(pipefd[1]); // Close unused write end

        // Read from pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        close(pipefd[0]);
        exit(0);

    } else { // Parent process
        close(pipefd[0]); // Close unused read end

        // Write to pipe
        write(pipefd[1], message, strlen(message) + 1); // +1 for null terminator
        printf("Parent sent: %s\n", message);

        close(pipefd[1]);
        wait(NULL); // Wait for child
    }

    return 0;
}


/*
OUTPUT: 
================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/15$ g++ 15.c -o 15
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/15$ ./15
Parent sent: Hello Child! This is parent.
Child received: Hello Child! This is parent.

*/