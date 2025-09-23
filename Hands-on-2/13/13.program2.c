/*
==============================
Name: 13.program2.c
Author: Atharva Ratnadeep Pingale
Description: Write two programs: 
                first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). 
                Find out whether the first program is able to catch the signal or not.
Date: 23rd Sept 2025
==============================
*/

// send_sigstop.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    printf("Sending SIGSTOP to PID %d\n", pid);
    if (kill(pid, SIGSTOP) == -1) {
        perror("kill failed");
        return 1;
    }

    printf("SIGSTOP sent.\n");
    return 0;
}
