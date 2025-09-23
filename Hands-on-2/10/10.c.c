/*
==============================
Name: 10.c.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using sigaction system call to catch the following signals.
                a. SIGSEGV  
                b. SIGINT   
                c. SIGFPE   [X]
Date: 23rd Sept 2025
==============================
*/


// sigfpe_sigaction.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig, siginfo_t *si, void *unused) {
    printf("Caught SIGFPE! Signal = %d\n", sig);
    _exit(1);
}

int main() {
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Triggering SIGFPE (divide by zero)...\n");
    int x = 1 / 0; // Cause divide by zero

    return 0;
}


/*
OUTPUT: 
=============================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/10$ g++ 10.c.c -o 10.c
10.c.c: In function ‘int main()’:
10.c.c:37:15: warning: division by zero [-Wdiv-by-zero]
   37 |     int x = 1 / 0; // Cause divide by zero
      |             ~~^~~
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/10$ ./10.c
Triggering SIGFPE (divide by zero)...
Caught SIGFPE! Signal = 8

*/