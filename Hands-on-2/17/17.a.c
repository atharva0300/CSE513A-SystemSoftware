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

    // Fork first child: ls -l
    pid1 = fork();
    if (pid1 < 0) { perror("fork"); exit(1); }

    if (pid1 == 0) {
        close(pipefd[0]); // Close unused read end

        // Save current stdout
        int saved_stdout = dup(STDOUT_FILENO);

        // Redirect stdout to pipe write end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        // Restore stdout in case exec fails
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        exit(1);
    }

    // Fork second child: wc
    pid2 = fork();
    if (pid2 < 0) { perror("fork"); exit(1); }

    if (pid2 == 0) {
        close(pipefd[1]); // Close unused write end

        // Save current stdin
        int saved_stdin = dup(STDIN_FILENO);

        // Redirect stdin to pipe read end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execlp("wc", "wc", NULL);
        perror("execlp wc");
        // Restore stdin in case exec fails
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
        exit(1);
    }

    // Parent closes both ends of pipe
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
      7      56     381
Parent regained control of terminal.

*/