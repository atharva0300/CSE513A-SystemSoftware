/*
==============================
Name: 23.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create a Zombie state of the running program.
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
        // Child exits immediately
        printf("Child exiting with PID %d\n", getpid());
        exit(0);
    } 
    else {
        // Parent sleeps for 30 seconds - zombie should form
        printf("Parent sleeping with PID %d, child PID: %d\n", getpid(), pid);
        sleep(30);  // Observe here with: ps aux | grep <child_pid>
        printf("Parent exiting\n");
    }

    return 0;
}


/*
OUTPUT : 
==========================
** TERMINAL 1 **
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/23$ g++ 23.c -o 23 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/23$ ./23
Parent sleeping with PID 39313, child PID: 39314
Child exiting with PID 39314


** TERMINAL 2 **
atharva0300@systems-software:~/Desktop/Github/systems-software-programs$ ps -ef | grep defunct
atharva+   39314   39313  0 21:00 pts/3    00:00:00 [23] <defunct>
atharva+   39338   38866  0 21:00 pts/5    00:00:00 grep --color=auto defunct


comment => here PID 31314 is the zombie process which has not been reaped by the parent process.
=> defunct means zombie process

*/