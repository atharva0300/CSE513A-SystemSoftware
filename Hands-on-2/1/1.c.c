/*
==============================
Name: 1.c.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second 
a. ITIMER_REAL      
b. ITIMER_VIRTUAL   
c. ITIMER_PROF      [X]
Date: 23rd Sept 2025
==============================
*/


// timer_prof.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("ITIMER_PROF expired! Signal: %d\n", sig);
}

int main() {
    struct itimerval timer;

    // Install handler for SIGPROF
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGPROF, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_PROF set for 10 sec + 10 µs...\n");

    // Burn CPU so both user+kernel time accumulate
    while (1) {
        // simulate syscalls to consume kernel time
        getpid();
    }
}


/*
OUTPUT : 
===========================



*/