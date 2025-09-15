/*
==============================
Name: 11.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to open a file, duplicate the file descriptor and append the file with both the
descriptors and check whether the file is updated properly or not.
a. use dup
b. use dup2
c. use fcntl
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, fd_dup1, fd_dup2, fd_dup3;

    // Open file in append mode
    fd = open("duplicate.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // =========================
    /* (a) Using dup() */
    fd_dup1 = dup(fd);
    if (fd_dup1 < 0) {
        perror("dup");
        close(fd);
        exit(1);
    }
    write(fd, "Hello from original fd\n", 24);
    write(fd_dup1, "Hello from dup()\n", 17);
    // =========================


    // =========================
    /* (b) Using dup2() */
    fd_dup2 = dup2(fd, 100); // Duplicate fd into descriptor 100
    if (fd_dup2 < 0) {
        perror("dup2");
        close(fd);
        close(fd_dup1);
        exit(1);
    }
    write(fd_dup2, "Hello from dup2()\n", 18);
    // =========================


    // =========================
    /* (c) Using fcntl() */
    fd_dup3 = fcntl(fd, F_DUPFD, 200); // Duplicate into first available >= 200
    if (fd_dup3 < 0) {
        perror("fcntl");
        close(fd);
        close(fd_dup1);
        close(fd_dup2);
        exit(1);
    }
    write(fd_dup3, "Hello from fcntl()\n", 19);
    // =========================

    // close all descriptors
    close(fd);
    close(fd_dup1);
    close(fd_dup2);
    close(fd_dup3);

    printf("All writes done\n");
    return 0;
}

/*
OUTPUT : 
===============================
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/11$ echo 'This is Atharva Pingale' > duplicate.txt
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/11$ ls -l 
total 156
-rwxrwxr-x 1 atharva0300 atharva0300  2707 Sep  6 23:20 11.c
-rw-rw-r-- 1 atharva0300 atharva0300    24 Sep  6 23:22 duplicate.txt



AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/11$ g++ 11.c -o 11
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/11$ ./11
All writes done
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/11$ cat duplicate.txt
This is Atharva Pingale
Hello from original fd
Hello from dup()
Hello from dup2()
Hello from fcntl()

*/