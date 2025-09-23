/*
==============================
Name: 9.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 23rd Sept 2025
==============================
*/



// sigint_ignore_reset.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    // Step 1: Ignore SIGINT
    if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    printf("SIGINT is now ignored. Try pressing Ctrl+C (will have no effect).\n");
    sleep(5);

    // Step 2: Reset SIGINT to default action
    if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
        perror("signal");
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
OUTPUT : 
======================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/9$ g++ 9.c -o 9
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/9$ ./9
SIGINT is now ignored. Try pressing Ctrl+C (will have no effect).
^CSIGINT reset to default. Try pressing Ctrl+C now (program will terminate).
^C

*/