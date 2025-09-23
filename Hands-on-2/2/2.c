/*
==============================
Name: 2.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to print the system resource limits. Use getrlimit system call.
Date: 23rd Sept 2025
==============================
*/

// limits.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

void print_limit(int resource, const char *name) {
    struct rlimit rl;

    if (getrlimit(resource, &rl) == -1) {
        perror("getrlimit");
        return;
    }

    printf("%-15s : ", name);

    if (rl.rlim_cur == RLIM_INFINITY)
        printf("Soft = unlimited, ");
    else
        printf("Soft = %llu, ", (unsigned long long)rl.rlim_cur);

    if (rl.rlim_max == RLIM_INFINITY)
        printf("Hard = unlimited\n");
    else
        printf("Hard = %llu\n", (unsigned long long)rl.rlim_max);
}

int main(void) {
    print_limit(RLIMIT_CPU, "CPU time");
    print_limit(RLIMIT_FSIZE, "File size");
    print_limit(RLIMIT_DATA, "Data seg size");
    print_limit(RLIMIT_STACK, "Stack size");
    print_limit(RLIMIT_CORE, "Core file size");
#ifdef RLIMIT_RSS
    print_limit(RLIMIT_RSS, "Resident set");
#endif
    print_limit(RLIMIT_NOFILE, "Open files");
#ifdef RLIMIT_AS
    print_limit(RLIMIT_AS, "Address space");
#endif
#ifdef RLIMIT_NPROC
    print_limit(RLIMIT_NPROC, "Processes");
#endif
#ifdef RLIMIT_MEMLOCK
    print_limit(RLIMIT_MEMLOCK, "Locked memory");
#endif
#ifdef RLIMIT_MSGQUEUE
    print_limit(RLIMIT_MSGQUEUE, "POSIX msgqueue");
#endif
#ifdef RLIMIT_NICE
    print_limit(RLIMIT_NICE, "Nice priority");
#endif
#ifdef RLIMIT_RTPRIO
    print_limit(RLIMIT_RTPRIO, "Realtime prio");
#endif
#ifdef RLIMIT_RTTIME
    print_limit(RLIMIT_RTTIME, "RT CPU time");
#endif

    return 0;
}


/*
OUTPUT : 
=========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/2$ g++ 2.c -o 2
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/2$ ./2
CPU time        : Soft = unlimited, Hard = unlimited
File size       : Soft = unlimited, Hard = unlimited
Data seg size   : Soft = unlimited, Hard = unlimited
Stack size      : Soft = 8388608, Hard = unlimited
Core file size  : Soft = 0, Hard = unlimited
Resident set    : Soft = unlimited, Hard = unlimited
Open files      : Soft = 1048576, Hard = 1048576
Address space   : Soft = unlimited, Hard = unlimited
Processes       : Soft = 15370, Hard = 15370
Locked memory   : Soft = 513249280, Hard = 513249280
POSIX msgqueue  : Soft = 819200, Hard = 819200
Nice priority   : Soft = 0, Hard = 0
Realtime prio   : Soft = 0, Hard = 0
RT CPU time     : Soft = unlimited, Hard = unlimited


*/