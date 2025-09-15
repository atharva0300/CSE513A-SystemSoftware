/*
==============================
Name: 4.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to open an existing file with read write mode. Try O_EXCL flag also.
Date: 6th Sept 2025
==============================
*/

#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h>  

int main() {
    const char *filename = "dummyExistingFile.txt";
    int fd;

    fd = creat(filename, 0644); // note -> the file should already be created for it to be opened
    if (fd == -1) {
        perror("creat failed");
        return 1;
    }
    close(fd);

    // Open existing file in read-write mode
    fd = open(filename, O_RDWR);    // O_RDWR -> read-write mode
    if (fd == -1) {
        perror("open (O_RDWR) failed");
        return 1;
    }
    printf("File opened (O_RDWR). FD = %d\n", fd);
    close(fd);

    // try opening with O_EXCL (only makes sense with O_CREAT)
    fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("open (O_CREAT | O_EXCL) failed");
    } else {
        printf("File opened (O_CREAT | O_EXCL). FD = %d\n", fd);
        close(fd);
    }

    return 0;
}


/*
OUTPUT : 
=========================
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/4$ ls -l 
total 168
-rwxrwxr-x 1 atharva0300 atharva0300   1627 Sep  6 22:15 4.c
-rwxr-xr-x 1 atharva0300 atharva0300      0 Sep  6 22:09 dummyExistingFile.txt


AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/4$ g++ 4.c -o 4 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/4$ ./4
File opened (O_RDWR). FD = 3
open (O_CREAT | O_EXCL) failed: File exists


*/