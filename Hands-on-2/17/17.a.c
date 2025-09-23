/*
==============================
Name: 17.a.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to execute ls -l | wc.
                a. use dup      [X]
                b. use dup2
                c. use fcntl
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();
    if (pid1 < 0) { perror("fork"); exit(1); }

    if (pid1 == 0) { // First child: ls -l
        close(pipefd[0]); // Close read end

        // Save stdout and redirect to pipe
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    }

    pid2 = fork();
    if (pid2 < 0) { perror("fork"); exit(1); }

    if (pid2 == 0) { // Second child: wc
        close(pipefd[1]); // Close write end

        // Save stdin and redirect to pipe
        int saved_stdin = dup(STDIN_FILENO);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execlp("wc", "wc", NULL);
        perror("execlp wc");
        exit(1);
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for children
    wait(NULL);
    wait(NULL);

    printf("Parent regained control of terminal.\n");
    return 0;
}



/*
OUTPUT: 
=================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/17$ g++ 17.a.c -o 17.a
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/17$ ./17.a
      3      20     133
Parent regained control of terminal.

*/