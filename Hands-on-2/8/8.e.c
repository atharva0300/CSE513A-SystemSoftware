/*
==============================
Name: 8.e.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV                                  
                b. SIGINT                                   
                c. SIGFPE                               
                d. SIGALRM (use alarm system call)      
                e. SIGALRM (use setitimer system call)  [X]
                f. SIGVTALRM (use setitimer system call)
                g. SIGPROF (use setitimer system call)
Date: 23rd Sept 2025
==============================
*/

// sigalrm_itimer.c
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGALRM (setitimer)!\n");
}

int main() {
    signal(SIGALRM, handler);

    struct itimerval timer;
    timer.it_value.tv_sec = 3;   // first expiration
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0; // no repeat
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);
    pause();
    return 0;
}


/*
OUTPUT : 
========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ g++ 8.e.c -o 8.e
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ ./8.e
Caught SIGALRM (setitimer)!

*/