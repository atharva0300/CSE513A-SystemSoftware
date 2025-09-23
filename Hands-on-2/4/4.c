/*
==============================
Name: 4.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date: 23rd Sept 2025
==============================
*/

// measure_getppid.c
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

// Read Time Stamp Counter
static __inline__ uint64_t rdtsc(void) {
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main(void) {
    uint64_t start, end;
    pid_t ppid;
    int i;

    // Warm-up (avoid cold cache effects)
    for (i = 0; i < 10; i++) getppid();

    start = rdtsc();

    for (i = 0; i < 100; i++) {
        ppid = getppid();
    }

    end = rdtsc();

    printf("Parent PID = %d\n", ppid);
    printf("Cycles taken for 100 getppid() calls: %llu\n",
           (unsigned long long)(end - start));
    printf("Average cycles per call: %llu\n",
           (unsigned long long)((end - start) / 100));

    return 0;
}


/*
OUTPUT : 
========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/4$ g++ 4.c -o 4
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/4$ ./4
Parent PID = 4678
Cycles taken for 100 getppid() calls: 42969
Average cycles per call: 429



*/