/*
==============================
Name: 10.b.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using sigaction system call to catch the following signals.
                a. SIGSEGV  
                b. SIGINT   [X]
                c. SIGFPE
Date: 23rd Sept 2025
==============================
*/


// sigint_sigaction.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig, siginfo_t *si, void *unused) {
    printf("\nCaught SIGINT! Exiting gracefully.\n");
    _exit(0);
}

int main() {
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Press Ctrl+C to trigger SIGINT...\n");
    while (1) pause();

    return 0;
}


/*
OUTPUT: 
====================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/10$ g++ 10.b.c -o 10.b
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/10$ ./10.b
Press Ctrl+C to trigger SIGINT...
^C
Caught SIGINT! Exiting gracefully.


*/