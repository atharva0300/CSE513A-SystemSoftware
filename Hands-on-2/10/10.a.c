/*
==============================
Name: 10.a.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using sigaction system call to catch the following signals.
                a. SIGSEGV  [X]
                b. SIGINT
                c. SIGFPE
Date: 23rd Sept 2025
==============================
*/

// sigsegv_sigaction.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig, siginfo_t *si, void *unused) {
    printf("Caught SIGSEGV! Faulting address = %p\n", si->si_addr);
    _exit(1);
}

int main() {
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO; // Use sa_sigaction
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Triggering SIGSEGV...\n");
    int *p = NULL;
    *p = 42; // Cause segmentation fault

    return 0;
}

/*
OUTPUT: 
==================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/10$ g++ 10.a.c -o 10.a
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/10$ ./10.a
Triggering SIGSEGV...
Caught SIGSEGV! Faulting address = (nil)

*/
