/*
==============================
Name: 8.f.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV                                  
                b. SIGINT                                   
                c. SIGFPE                               
                d. SIGALRM (use alarm system call)      
                e. SIGALRM (use setitimer system call)  
                f. SIGVTALRM (use setitimer system call)    [X]
                g. SIGPROF (use setitimer system call)
Date: 23rd Sept 2025
==============================
*/

// sigvtalrm.c
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGVTALRM!\n");
}

int main() {
    signal(SIGVTALRM, handler);

    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 500000; // 0.5 sec
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 500000; // repeat every 0.5 sec

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    // Consume CPU so virtual time elapses
    while (1);
}


/*
OUTPUT : 
===================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ g++ 8.f.c -o 8.f
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ ./8.f
Caught SIGVTALRM!
Caught SIGVTALRM!
Caught SIGVTALRM!
Caught SIGVTALRM!
Caught SIGVTALRM!
Caught SIGVTALRM!
Caught SIGVTALRM!
Caught SIGVTALRM!
Caught SIGVTALRM!
^C


*/