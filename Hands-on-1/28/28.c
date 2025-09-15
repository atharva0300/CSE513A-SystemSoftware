/*
==============================
Name: 28.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to get maximum and minimum real time priority.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <sched.h>
#include <unistd.h>

int main() {
    int policy = SCHED_FIFO;

    int max_priority = sched_get_priority_max(policy);
    if (max_priority == -1) {
        perror("sched_get_priority_max");
        return 1;
    }

    int min_priority = sched_get_priority_min(policy);
    if (min_priority == -1) {
        perror("sched_get_priority_min");
        return 1;
    }

    printf("Real-time scheduling policy: SCHED_FIFO\n");
    printf("Maximum priority: %d\n", max_priority);
    printf("Minimum priority: %d\n", min_priority);

    return 0;
}

/*
OUTPUT : 
======================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/28$ g++ 28.c -o 28
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/28$ ./28
Real-time scheduling policy: SCHED_FIFO
Maximum priority: 99
Minimum priority: 1


*/

