/*
==============================
Name: 19.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to find out time taken to execute getpid system call. Use time stamp counter.
Date: 6th Sept 2025
==============================
*/



#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <inttypes.h>

// read Time Stamp Counter using inline assembly
static __inline__ uint64_t rdtsc(void) {
    unsigned int hi, lo;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi)); // eax and edx
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    uint64_t start, end;
    pid_t pid;

    start = rdtsc();
    pid = getpid();
    end = rdtsc();

    printf("PID: %d\n", pid);
    printf("CPU cycles taken by getpid(): %" PRIu64 "\n", (end - start));

    return 0;
}



/*
OUTPUT : 
===========================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/19$ g++ 19.c -o 19
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/19$ ./19
PID: 36435
CPU cycles taken by getpid(): 5170

*/
