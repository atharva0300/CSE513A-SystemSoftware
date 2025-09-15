/*
==============================
Name: 29.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO,
SCHED_RR).
Date: 6th Sept 2025
==============================
*/



#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>

void print_policy(int policy) {
    switch (policy) {
        case SCHED_OTHER:
            printf("Current scheduling policy: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Current scheduling policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Current scheduling policy: SCHED_RR\n");
            break;
        default:
            printf("Current scheduling policy: UNKNOWN (%d)\n", policy);
    }
}

int main() {
    pid_t pid = getpid();

    // Get current scheduling policy
    int policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    print_policy(policy);

    // Set new scheduling policy: example SCHED_FIFO with priority 10
    struct sched_param param;
    param.sched_priority = 10;

    printf("Setting scheduling policy to SCHED_FIFO with priority %d\n", param.sched_priority);
    if (sched_setscheduler(pid, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler");
        printf("Requires appropriate privileges (which is usually root) for real-time policies.\n");
        return 1;
    }

    // Get updated policy
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    print_policy(policy);

    return 0;
}


/*
OUTPUT : 
==========================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/29$ g++ 29.c -o 29
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/29$ ./29
Current scheduling policy: SCHED_OTHER
Setting scheduling policy to SCHED_FIFO with priority 10
sched_setscheduler: Operation not permitted
Requires appropriate privileges (which is usually root) for real-time policies.


*/