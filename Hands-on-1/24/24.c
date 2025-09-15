/*
==============================
Name: 24.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create an orphan process.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) {
        // Child process
        printf("Child process started. PID: %d\n", getpid());
        printf("Parent PID before sleep: %d\n", getppid());

        sleep(30);  // Wait for parent to exit

        // After parent exits, PPID changes to 1 (init)
        printf("Parent PID after parent exits: %d\n", getppid());
        printf("Child exiting.\n");
        exit(0);
    } 
    else {
        // Parent process
        printf("Parent process PID: %d\n", getpid());
        printf("Parent exiting immediately.\n");
        exit(0);
    }

    return 0;
}


/*
OUTPUT : 
=============================
** TERMINAL 1 **
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/24$ g++ 24.c -o 24
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/24$ ./24 
Parent process PID: 39968
Parent exiting immediately.
Child process started. PID: 39969
Parent PID before sleep: 1353
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/24$ Parent PID after parent exits: 1353
Child exiting.


** TERMINAL 2 **
atharva0300@systems-software:~/Desktop/Github/systems-software-programs$ ps -o pid,ppid,cmd -p 39969      
    PID    PPID CMD
  39969    1353 ./24


*/




