/*
==============================
Name: 11.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date: 23rd Sept 2025
==============================
*/


// sigint_ignore_reset_sigaction.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa_ignore, sa_default;

    // Step 1: Ignore SIGINT
    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;

    if (sigaction(SIGINT, &sa_ignore, NULL) == -1) {
        perror("sigaction ignore");
        return 1;
    }

    printf("SIGINT is now ignored. Try pressing Ctrl+C (will have no effect) for 5 seconds...\n");
    sleep(5);

    // Step 2: Reset SIGINT to default action
    sa_default.sa_handler = SIG_DFL;
    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;

    if (sigaction(SIGINT, &sa_default, NULL) == -1) {
        perror("sigaction default");
        return 1;
    }

    printf("SIGINT reset to default. Try pressing Ctrl+C now (program will terminate).\n");

    // Wait so user can test Ctrl+C
    while (1) {
        pause();
    }

    return 0;
}

/*
OUTPUT: 
======================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/11$ g++ 11.c -o 11 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/11$ ./11
SIGINT is now ignored. Try pressing Ctrl+C (will have no effect) for 5 seconds...
SIGINT reset to default. Try pressing Ctrl+C now (program will terminate).
^C
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/11$ ./11
SIGINT is now ignored. Try pressing Ctrl+C (will have no effect) for 5 seconds...
^C^C^CSIGINT reset to default. Try pressing Ctrl+C now (program will terminate).
^C

*/
