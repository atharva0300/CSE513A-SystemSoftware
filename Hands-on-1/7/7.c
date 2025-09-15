/*
==============================
Name: 7.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to copy file1 into file2 ($cp file1 file2).
Date: 6th Sept 2025
==============================
*/


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    const char *file1 = "file1";
    const char *file2 = "file2";
    const char *content = "This is Atharva Pingale, MT2025026, doing the System software assignment right now :)\n";
    
    // creating and writing
    int fd1 = open(file1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0) {
        perror("Error creating file1");
        return 1;
    }
    if (write(fd1, content, strlen(content)) != (ssize_t)strlen(content)) {
        perror("Error writing to file1");
        close(fd1);
        return 1;
    }
    close(fd1);
    
    // copying
    int src_fd = open(file1, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening file1 for reading");
        return 1;
    }
    int dest_fd = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening file2 for writing");
        close(src_fd);
        return 1;
    }
    
    // writing in to the file2
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to file2");
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }
    if (bytesRead < 0) {
        perror("Error reading file1");
    }
    close(src_fd);
    close(dest_fd);
    
    // reading and printing hte contents of file2 
    int fd2 = open(file2, O_RDONLY);
    if (fd2 < 0) {
        perror("Error opening file2 for reading");
        return 1;
    }
    printf("Contents of file2:\n");
    while ((bytesRead = read(fd2, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error writing to stdout");
            close(fd2);
            return 1;
        }
    }
    if (bytesRead < 0) {
        perror("Error reading file2");
    }
    close(fd2);
    
    return 0;
}


/*
OUTPUT: 
================================
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/7$ ls -l 
total 92
-rwxrwxr-x 1 atharva0300 atharva0300  2363 Sep  6 22:42 7.c


AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/7$ g++ 7.c -o 7
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/7$ ./7
Contents of file2:
This is Atharva Pingale, MT2025026, doing the System software assignment right now :)
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/7$ ls -l
total 116
-rwxrwxr-x 1 atharva0300 atharva0300 16256 Sep  6 22:43 7
-rwxrwxr-x 1 atharva0300 atharva0300  2548 Sep  6 22:43 7.c
-rw-r--r-- 1 atharva0300 atharva0300    86 Sep  6 22:43 file1
-rw-r--r-- 1 atharva0300 atharva0300    86 Sep  6 22:43 file2
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/7$ cat file1
This is Atharva Pingale, MT2025026, doing the System software assignment right now :)
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/7$ cat file2
This is Atharva Pingale, MT2025026, doing the System software assignment right now :)


*/