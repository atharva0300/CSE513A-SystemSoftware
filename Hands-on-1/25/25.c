/*
==============================
Name: 25.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create three child processes. The parent should wait for a particular child (use
waitpid system call).
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];
    int i;

    for (i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {
            // Child process
            printf("Child %d started with PID: %d\n", i + 1, getpid());
            sleep(3 + i);  // Different sleep times
            printf("Child %d exiting.\n", i + 1);
            exit(i + 1);  // Exit with status code = child number
        }
    }

    // Parent process waits for a specific child, for example, the second child
    int status;
    pid_t waited_pid = waitpid(pids[1], &status, 0);

    if (waited_pid == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    printf("Parent waited for child with PID: %d\n", waited_pid);
    if (WIFEXITED(status)) {
        printf("Child exited with status: %d\n", WEXITSTATUS(status));
    }

    // Wait for remaining children to avoid zombies
    for (i = 0; i < 3; i++) {
        if (pids[i] != waited_pid) {
            waitpid(pids[i], NULL, 0);
        }
    }

    printf("Parent exiting.\n");
    return 0;
}

/*
OUTPUT : 
=============================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/25$ g++ 25.c -o 25
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/25$ ./25
Child 2 started with PID: 40951
Child 1 started with PID: 40950
Child 3 started with PID: 40952
Child 1 exiting.
Child 2 exiting.
Parent waited for child with PID: 40951
Child exited with status: 2
Child 3 exiting.
Parent exiting.


*/