/*
==============================
Name: 8.d.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV                                  
                b. SIGINT                                   
                c. SIGFPE                               
                d. SIGALRM (use alarm system call)      [X]
                e. SIGALRM (use setitimer system call)
                f. SIGVTALRM (use setitimer system call)
                g. SIGPROF (use setitimer system call)
Date: 23rd Sept 2025
==============================
*/

// sigalrm_alarm.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGALRM (alarm)!\n");
}

int main() {
    signal(SIGALRM, handler);

    printf("Setting alarm for 3 seconds...\n");
    alarm(3);

    pause(); // Wait for signal
    return 0;
}


/*
OUTPUT : 
======================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ g++ 8.d.c -o 8.d
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ ./8.d
Setting alarm for 3 seconds...
Caught SIGALRM (alarm)!

*/