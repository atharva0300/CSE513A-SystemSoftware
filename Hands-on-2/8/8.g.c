/*
==============================
Name: 8.g.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV                                  
                b. SIGINT                                   
                c. SIGFPE                               
                d. SIGALRM (use alarm system call)      
                e. SIGALRM (use setitimer system call)  
                f. SIGVTALRM (use setitimer system call)    
                g. SIGPROF (use setitimer system call)      [X]
Date: 23rd Sept 2025
==============================
*/


// sigprof.c
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught SIGPROF!\n");
}

int main() {
    signal(SIGPROF, handler);

    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 500000; // 0.5 sec
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 500000; // repeat every 0.5 sec

    setitimer(ITIMER_PROF, &timer, NULL);

    // Consume CPU so user+kernel time elapses
    while (1) {
        getpid(); // simple syscall to consume some kernel time
    }
}

/*
OUTPUT : 
=========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ g++ 8.g.c -o 8.g
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ ./8.g
Caught SIGPROF!
Caught SIGPROF!
Caught SIGPROF!
Caught SIGPROF!
Caught SIGPROF!
Caught SIGPROF!
Caught SIGPROF!
Caught SIGPROF!
Caught SIGPROF!
Caught SIGPROF!
^C

*/