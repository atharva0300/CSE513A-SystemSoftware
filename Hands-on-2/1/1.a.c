/*
==============================
Name: 1.a.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second 
a. ITIMER_REAL      [X]
b. ITIMER_VIRTUAL 
c. ITIMER_PROF
Date: 23rd Sept 2025
==============================
*/

// timer_real.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("ITIMER_REAL expired! Signal: %d\n", sig);
}

int main() {
    struct itimerval timer;

    // Install handler for SIGALRM
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Configure timer: first expiration = 10 sec + 10 µs
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    // Interval for periodic expiration
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_REAL set for 10 sec + 10 µs...\n");

    // Loop forever to catch signals
    while (1) pause();
}


/*
OUTPUT : 
=======================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/1$ ./1.a
ITIMER_REAL set for 10 sec + 10 µs...
ITIMER_REAL expired! Signal: 14
ITIMER_REAL expired! Signal: 14
ITIMER_REAL expired! Signal: 14
ITIMER_REAL expired! Signal: 14
ITIMER_REAL expired! Signal: 14
^C



*/