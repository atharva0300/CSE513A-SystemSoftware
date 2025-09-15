/*
==============================
Name: 22.c
Author: Atharva Ratnadeep Pingale
Description: Write a program, open a file, call fork, and then write to the file by both the child as well as the
parent processes. Check output of the file.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    const char *filename = "output.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        close(fd);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process
        const char *child_msg = "Child process writing.\n";
        if (write(fd, child_msg, strlen(child_msg)) == -1) {
            perror("write child");
            close(fd);
            exit(EXIT_FAILURE);
        }
        printf("Child wrote to file.\n");
    }
    else {
        // Parent process
        // Optionally wait for the child to finish writing first
        wait(NULL);

        const char *parent_msg = "Parent process writing.\n";
        if (write(fd, parent_msg, strlen(parent_msg)) == -1) {
            perror("write parent");
            close(fd);
            exit(EXIT_FAILURE);
        }
        printf("Parent wrote to file.\n");
    }

    close(fd);
    return 0;
}

/*
OUTPUT : 
============================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/22$ g++ 22.c -o 22
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/22$ ./22
Child wrote to file.
Parent wrote to file.
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/22$ cat output.txt
Child process writing.
Parent process writing.


*/
