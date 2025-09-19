/*
==============================
Name: 12.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to find out the opening mode of a file. Use fcntl.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, flags, accmode;

    // Open file in Read-Write mode
    fd = open("mode_check.txt", O_RDONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // Get file status flags
    flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        perror("fcntl");
        close(fd);
        exit(1);
    }

    // Extract access mode (mask with O_ACCMODE)
    accmode = flags & O_ACCMODE;

    // Identify the mode
    if (accmode == O_RDONLY)
        printf("File opened in: READ ONLY mode\n");
    else if (accmode == O_WRONLY)
        printf("File opened in: WRITE ONLY mode\n");
    else if (accmode == O_RDWR)
        printf("File opened in: READ-WRITE mode\n");
    else
        printf("Unknown mode\n");

    close(fd);
    return 0;
}


/*
OUTPUT : 
===================================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/12$ g++ 12.c -o 12
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/12$ ./12 
File opened in: READ ONLY mode



*/