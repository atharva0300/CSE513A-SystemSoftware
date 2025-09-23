/*
==============================
Name: 17.c.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to execute ls -l | wc.
                a. use dup      
                b. use dup2     
                c. use fcntl    [X]
Date: 23rd Sept 2025
==============================
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) { perror("pipe"); exit(1); }

    pid1 = fork();
    if (pid1 == 0) { // ls -l
        close(pipefd[0]); // close read end

        int newfd = fcntl(pipefd[1], F_DUPFD, STDOUT_FILENO);
        if (newfd != STDOUT_FILENO) {
            close(STDOUT_FILENO);
            dup(newfd); // redirect stdout to pipe
            close(newfd);
        }
        close(pipefd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) { // wc
        close(pipefd[1]); // close write end

        int newfd = fcntl(pipefd[0], F_DUPFD, STDIN_FILENO);
        if (newfd != STDIN_FILENO) {
            close(STDIN_FILENO);
            dup(newfd); // redirect stdin from pipe
            close(newfd);
        }
        close(pipefd[0]);

        execlp("wc", "wc", NULL);
        perror("execlp wc");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    printf("Parent regained control of terminal.\n");
    return 0;
}



/*
OUTPUT: 
==================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/17$ g++ 17.c.c -o 17.c
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/17$ ./17.c
      7      56     381
Parent regained control of terminal.


*/