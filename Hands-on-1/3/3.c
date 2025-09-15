/*
==============================
Name: 3.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 6th Sept 2025
==============================
*/

#include <stdio.h>
#include <fcntl.h>  // for creating the file 
#include <unistd.h>     // for closing the  file

int main() {
    const char *filename = "dummyFile.txt";

    int fd = creat(filename, 0644); // octal number => rw-r--r-- permissions

    if (fd == -1) {
        perror("creat failed");
        return 1;
    }

    printf("File created: %s\n", filename);
    printf("File descriptor: %d\n", fd);

    close(fd);
    return 0;
}


/*
OUTPUT : 
=================================
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/3$ ls -l 
total 152
-rwxrwxr-x 1 atharva0300 atharva0300   700 Sep  6 22:00 3.c

AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/3$ g++ 3.c -o 3
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/3$ ./3
File created: dummyFile.txt
File descriptor: 3


*/