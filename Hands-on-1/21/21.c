/*
==============================
Name: 21.c
Author: Atharva Ratnadeep Pingale
Description: Write a program, call fork and print the parent and child process id.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child process. PID: %d\n", getpid());
    }
    else {
        // Parent process
        printf("Parent process. PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}

/*
OUTPUT : 
===========================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/21$ g++ 21.c -o 21
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/21$ ./21
Parent process. PID: 38206, Child PID: 38207
Child process. PID: 38207



*/
