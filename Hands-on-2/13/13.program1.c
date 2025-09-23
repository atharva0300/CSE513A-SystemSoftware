/*
==============================
Name: 13.program1.c
Author: Atharva Ratnadeep Pingale
Description: Write two programs: 
                first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). 
                Find out whether the first program is able to catch the signal or not.
Date: 23rd Sept 2025
==============================
*/

// catch_sigstop.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught signal %d!\n", sig);
}

int main() {
    // Attempt to set a handler for SIGSTOP
    if (signal(SIGSTOP, handler) == SIG_ERR) {
        perror("signal(SIGSTOP) failed");
    }

    printf("PID = %d. Waiting... (try sending SIGSTOP from another process)\n", getpid());

    while (1) {
        sleep(1); // Wait indefinitely
    }

    return 0;
}


/*
OUTPUT: 
===========================
TERMINAL 1 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/13$ g++ 13.program1.c -o 13.program1
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/13$ ./13.program1
signal(SIGSTOP) failed: Invalid argument
PID = 12011. Waiting... (try sending SIGSTOP from another process)

[1]+  Stopped                 ./13.program1


TERMINAL 2 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/13$ g++ 13.program2.c -o 13.program2
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/13$ ./13.program2 12011
Sending SIGSTOP to PID 12011
SIGSTOP sent.



*/