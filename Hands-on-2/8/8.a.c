/*
==============================
Name: 8.a.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV                                  [X]
                b. SIGINT
                c. SIGFPE
                d. SIGALRM (use alarm system call)
                e. SIGALRM (use setitimer system call)
                f. SIGVTALRM (use setitimer system call)
                g. SIGPROF (use setitimer system call)
Date: 23rd Sept 2025
==============================
*/

// sigsegv.c
#include <stdio.h>
#include <signal.h>

void handler(int sig) {
    printf("Caught SIGSEGV!\n");
    _exit(1); // Exit after segmentation fault
}

int main() {
    signal(SIGSEGV, handler);

    printf("Triggering SIGSEGV...\n");
    int *p = NULL;
    *p = 42; // Cause segmentation fault

    return 0;
}


/*
OUTPUT : 
===================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ g++ 8.a.c -o 8.a
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ ./8.a
Triggering SIGSEGV...
Caught SIGSEGV!

*/