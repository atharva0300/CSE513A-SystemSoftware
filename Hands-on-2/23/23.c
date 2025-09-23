/*
==============================
Name: 23.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Maximum number of files per process
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("getrlimit");
        exit(1);
    }
    printf("Maximum number of files that can be opened per process:\n");
    printf("Soft limit: %ld\n", rl.rlim_cur);
    printf("Hard limit: %ld\n", rl.rlim_max);

    // Size of a pipe (circular buffer)
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    int pipe_size = fcntl(pipefd[0], F_GETPIPE_SZ);
    if (pipe_size == -1) {
        perror("fcntl F_GETPIPE_SZ");
        exit(1);
    }
    printf("Size of a pipe (circular buffer): %d bytes\n", pipe_size);

    // Close the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}


/*
OUTPUT: 
====================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/23$ g++ 23.c -o 23
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/23$ ./23
Maximum number of files that can be opened per process:
Soft limit: 1048576
Hard limit: 1048576
Size of a pipe (circular buffer): 65536 bytes

*/