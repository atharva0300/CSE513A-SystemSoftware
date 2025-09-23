/*
==============================
Name: 14.c
Author: Atharva Ratnadeep Pingale
Description: Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
Date: 23rd Sept 2025
==============================
*/


// simple_pipe.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2]; // pipefd[0] = read end, pipefd[1] = write end
    pid_t pid;
    char buffer[100];
    const char *msg = "Hello through the pipe!";

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(pipefd[1]); // Close unused write end

        // Read from pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child read: %s\n", buffer);

        close(pipefd[0]);
        exit(0);

    } else { // Parent process
        close(pipefd[0]); // Close unused read end

        // Write to pipe
        write(pipefd[1], msg, strlen(msg) + 1); // +1 for null terminator
        printf("Parent wrote: %s\n", msg);

        close(pipefd[1]);
        wait(NULL); // Wait for child
    }

    return 0;
}


/*
OUTPUT : 
======================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/14$ g++ 14.c -o 14
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/14$ ./14
Parent wrote: Hello through the pipe!
Child read: Hello through the pipe!

*/