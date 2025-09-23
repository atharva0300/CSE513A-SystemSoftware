/*
==============================
Name: 8.b.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV                                  
                b. SIGINT                                   [X]
                c. SIGFPE
                d. SIGALRM (use alarm system call)
                e. SIGALRM (use setitimer system call)
                f. SIGVTALRM (use setitimer system call)
                g. SIGPROF (use setitimer system call)
Date: 23rd Sept 2025
==============================
*/

// sigint.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("\nCaught SIGINT! Exiting gracefully.\n");
    _exit(0);
}

int main() {
    signal(SIGINT, handler);

    printf("Press Ctrl+C to trigger SIGINT...\n");
    while (1) pause(); // Wait for signal
}

/*
OUTPUT:
===========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ g++ 8.b.c -o 8.b
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ ./8.b
Press Ctrl+C to trigger SIGINT...
^C
Caught SIGINT! Exiting gracefully.

*/