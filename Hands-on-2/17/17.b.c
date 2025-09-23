/*
==============================
Name: 17.b.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to execute ls -l | wc.
                a. use dup      
                b. use dup2     [X]
                c. use fcntl
Date: 23rd Sept 2025
==============================
*/


// ls_wc_dup2.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) { perror("pipe"); exit(1); }

    pid1 = fork();
    if (pid1 == 0) { // ls -l
        dup2(pipefd[1], STDOUT_FILENO); // stdout -> pipe write
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) { // wc
        dup2(pipefd[0], STDIN_FILENO); // stdin -> pipe read
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        exit(1);
    }

    // Parent
    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}

/*
OUTPUT: 
=================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/17$ g++ 17.b.c -o 17.b
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/17$ ./17.b
      6      47     320

*/