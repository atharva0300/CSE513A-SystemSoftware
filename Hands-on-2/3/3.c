/*
==============================
Name: 3.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 23rd Sept 2025
==============================
*/

// set_limit.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

int main(void) {
    struct rlimit rl;

    // First, get current limit
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Current RLIMIT_NOFILE: Soft = %llu, Hard = %llu\n",
           (unsigned long long)rl.rlim_cur,
           (unsigned long long)rl.rlim_max);

    // Try to set new soft limit (hard limit unchanged)
    rl.rlim_cur = 512;   // New soft limit
    // rl.rlim_max = 512; // Uncomment if you want to set hard too (needs root)

    if (setrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    // Verify change
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("New RLIMIT_NOFILE: Soft = %llu, Hard = %llu\n",
           (unsigned long long)rl.rlim_cur,
           (unsigned long long)rl.rlim_max);

    return 0;
}


/*
OUTPUT : 
=========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/3$ g++ 3.c -o 3 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/3$ ./3
Current RLIMIT_NOFILE: Soft = 1048576, Hard = 1048576
New RLIMIT_NOFILE: Soft = 512, Hard = 1048576

*/