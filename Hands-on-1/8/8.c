/*
==============================
Name:  8.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.
Date: 6th Sept 2025
==============================
*/

#include <fcntl.h>   
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>   

#define BUFFER_SIZE 1  // reading one character at a time so that we can deect a new line (/n)

int main() {
    int fd;
    char ch;
    ssize_t bytesRead;

    const char *filename = "file.txt";

    // opening the file in read-only mode
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }

    // reading character by character
    while ((bytesRead = read(fd, &ch, BUFFER_SIZE)) > 0) {
        // writing each character immediately
        if (write(STDOUT_FILENO, &ch, BUFFER_SIZE) != BUFFER_SIZE) {
            perror("Error writing to STDOUT");
            close(fd);
            exit(1);
        }
    }

    if (bytesRead < 0) {
        perror("Error reading file");
    }

    close(fd);
    return 0;
}


/*
OUTPUT : 
==================================
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/8$ ls -l 
total 148
-rwxrwxr-x 1 atharva0300 atharva0300  1217 Sep  6 22:48 8.c
-rw-rw-r-- 1 atharva0300 atharva0300    76 Sep  6 22:49 file.txt
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/8$ cat file.txt
This is Atharva Pingale, MT2025026 doing this System Software Assignment :)


AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/8$ g++ 8.c -o 8
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/8$ ./8
This is Atharva Pingale, MT2025026 doing this System Software Assignment :)


*/