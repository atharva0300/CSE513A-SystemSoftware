/*
==============================
Name: 12.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date: 23rd Sept 2025
==============================
*/


// orphan_process.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid, parent_pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        parent_pid = getppid();
        printf("Child PID = %d, Parent PID = %d\n", getpid(), parent_pid);

        // Give parent time to print
        sleep(2);

        printf("Child sending SIGKILL to parent PID %d...\n", parent_pid);
        if (kill(parent_pid, SIGKILL) == -1) {
            perror("kill failed");
            exit(EXIT_FAILURE);
        }

        // Sleep to show that child is now orphan
        sleep(3);
        printf("After parent termination: Child PID = %d, New Parent PID = %d\n",
               getpid(), getppid());

    } else {  // Parent process
        printf("Parent PID = %d, Child PID = %d\n", getpid(), pid);

        // Sleep to allow child to send SIGKILL
        while (1) {
            printf("Parent is running...\n");
            sleep(1);
        }
    }

    return 0;
}

/*
OUTPUT: 
==============================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/12$ g++ 12.c -o 12 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/12$ ./12
Parent PID = 11529, Child PID = 11530
Parent is running...
Child PID = 11530, Parent PID = 11529
Parent is running...
Child sending SIGKILL to parent PID 11529...
Killed
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/12$ After parent termination: Child PID = 11530, New Parent PID = 1350
^C

*/
