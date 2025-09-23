/*
==============================
Name: 1.b.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second 
a. ITIMER_REAL      
b. ITIMER_VIRTUAL   [X]
c. ITIMER_PROF
Date: 23rd Sept 2025
==============================
*/

// timer_virtual.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("ITIMER_VIRTUAL expired! Signal: %d\n", sig);
}

int main() {
    struct itimerval timer;

    // Install handler for SIGVTALRM
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGVTALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_VIRTUAL set for 10 sec + 10 µs...\n");

    // Burn CPU so virtual time elapses
    while (1);  
}
