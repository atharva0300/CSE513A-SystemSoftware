/*
==============================
Name: 18.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to find out total number of directories on the pwd.
            execute ls -l | grep ^d | wc ? Use only dup2.
Date: 23rd Sept 2025
==============================
*/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid1, pid2, pid3;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    // First child: ls -l
    pid1 = fork();
    if (pid1 == 0) {
        dup2(pipe1[1], STDOUT_FILENO); // stdout -> pipe1 write
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    }

    // Second child: grep ^d
    pid2 = fork();
    if (pid2 == 0) {
        dup2(pipe1[0], STDIN_FILENO);  // stdin <- pipe1 read
        dup2(pipe2[1], STDOUT_FILENO); // stdout -> pipe2 write
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        execlp("grep", "grep", "^d", NULL);
        perror("execlp grep");
        exit(1);
    }

    // Third child: wc
    pid3 = fork();
    if (pid3 == 0) {
        dup2(pipe2[0], STDIN_FILENO); // stdin <- pipe2 read
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        exit(1);
    }

    // Parent closes all pipe fds
    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);

    // Wait for children
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Parent regained control of terminal.\n");
    return 0;
}


/*
OUTPUT: 
=====================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/18$ g++ 18.c -o 18
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/18$ ./18
      1       9      64
Parent regained control of terminal.
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/18$ mkdir testdir2
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/18$ ./18
      2      18     129
Parent regained control of terminal.

*/