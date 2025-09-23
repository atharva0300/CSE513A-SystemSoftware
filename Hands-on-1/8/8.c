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

#define MAX_LINE 1024  // buffer for one line

int main() {
    int fd;
    char ch;
    ssize_t bytesRead;
    char line[MAX_LINE];
    int pos = 0;

    const char *filename = "file.txt";

    // opening the file in read-only mode
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }

    while ((bytesRead = read(fd, &ch, 1)) > 0) {
        line[pos++] = ch;

        if (ch == '\n' || pos == MAX_LINE - 1) {
            if (write(STDOUT_FILENO, line, pos) != pos) {
                perror("Error writing to STDOUT");
                close(fd);
                exit(1);
            }
            pos = 0; 
        }
    }

    // note : flush remaining characters if file does not end with '\n'
    if (pos > 0) {
        if (write(STDOUT_FILENO, line, pos) != pos) {
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