/*
==============================
Name: 5.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to print the system limitation of
                a. maximum length of the arguments to the exec family of functions.
                b. maximum number of simultaneous process per user id.
                c. number of clock ticks (jiffy) per second.
                d. maximum number of open files
                e. size of a page
                f. total number of pages in the physical memory
                g. number of currently available pages in the physical memory.
Date: 6th Sept 2025
==============================
*/

// sys_limits.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <errno.h>

int main(void) {
    long arg_max, proc_max, ticks, page_size;
    struct rlimit rl;
    long total_pages, avail_pages;

    // a. Max length of arguments to exec
    arg_max = sysconf(_SC_ARG_MAX);
    if (arg_max == -1) perror("sysconf(_SC_ARG_MAX)");
    else printf("a. Max length of arguments (exec): %ld bytes\n", arg_max);

    // b. Max number of simultaneous processes per user
    if (getrlimit(RLIMIT_NPROC, &rl) == -1) perror("getrlimit(RLIMIT_NPROC)");
    else printf("b. Max simultaneous processes per user: %llu\n",
                (unsigned long long)rl.rlim_cur);

    // c. Number of clock ticks per second
    ticks = sysconf(_SC_CLK_TCK);
    if (ticks == -1) perror("sysconf(_SC_CLK_TCK)");
    else printf("c. Number of clock ticks per second: %ld\n", ticks);

    // d. Max number of open files
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) perror("getrlimit(RLIMIT_NOFILE)");
    else printf("d. Max number of open files: %llu\n",
                (unsigned long long)rl.rlim_cur);

    // e. Size of a page
    page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) perror("sysconf(_SC_PAGESIZE)");
    else printf("e. Page size: %ld bytes\n", page_size);

    // f & g. Total and available pages in physical memory (Linux-specific)
    total_pages = sysconf(_SC_PHYS_PAGES);
    avail_pages = sysconf(_SC_AVPHYS_PAGES);
    if (total_pages == -1 || avail_pages == -1) perror("sysconf(PHYS_PAGES/AVPHYS_PAGES)");
    else {
        printf("f. Total physical memory pages: %ld\n", total_pages);
        printf("   Total memory = %ld MB\n", (total_pages * page_size) / (1024*1024));
        printf("g. Available physical memory pages: %ld\n", avail_pages);
        printf("   Available memory = %ld MB\n", (avail_pages * page_size) / (1024*1024));
    }

    return 0;
}

/*
OUTPUT : 
================================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/5$ g++ 5.c -o 5
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/5$ ./5
a. Max length of arguments (exec): 2097152 bytes
b. Max simultaneous processes per user: 15370
c. Number of clock ticks per second: 100
d. Max number of open files: 1048576
e. Page size: 4096 bytes
f. Total physical memory pages: 1002440
   Total memory = 3915 MB
g. Available physical memory pages: 40497
   Available memory = 158 MB

*/
