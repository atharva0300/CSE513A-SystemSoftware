/*
==============================
Name: 9.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to print the following information about a given file.
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change
Date: 6th Sept 2025
==============================
*/


#include <sys/stat.h>  // for stat structure
#include <stdio.h>     // for printf(), perror()
#include <stdlib.h>    // for exit()
#include <time.h>      // for ctime()

int main() {
    struct stat fileStat;
    const char *fileName = "file.txt";

    // get the file status
    if (stat(fileName, &fileStat) < 0) {
        perror("Error getting file information");
        exit(1);
    }

    printf("File: %s\n", fileName);
    printf("Inode: %ld\n", (long)fileStat.st_ino);
    printf("Number of hard links: %ld\n", (long)fileStat.st_nlink);
    printf("UID: %d\n", fileStat.st_uid);
    printf("GID: %d\n", fileStat.st_gid);
    printf("Size: %ld bytes\n", (long)fileStat.st_size);
    printf("Block size: %ld bytes\n", (long)fileStat.st_blksize);   // not same as the FS block size
    printf("Number of blocks: %ld\n", (long)fileStat.st_blocks);
    printf("Time of last access: %s", ctime(&fileStat.st_atime));
    printf("Time of last modification: %s", ctime(&fileStat.st_mtime));
    printf("Time of last status change: %s", ctime(&fileStat.st_ctime));

    return 0;
}


/*
OUTPUT : 
======================================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/9$ g++ 9.c -o 9
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/9$ ./9
File: file.txt
Inode: 798184
Number of hard links: 1
UID: 1000
GID: 1000
Size: 48 bytes
Block size: 4096 bytes
Number of blocks: 8
Time of last access: Sat Sep  6 22:54:37 2025
Time of last modification: Sat Sep  6 22:54:37 2025
Time of last status change: Sat Sep  6 22:54:37 2025


*/