/*
==============================
Name: 6.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 6th Sept 2025
==============================
*/


#include <unistd.h>  
#include <stdlib.h> 

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    // Read from STDIN (fd = 0) until EOF (Ctrl+D) or error
    while ((bytesRead = read(0, buffer, BUFFER_SIZE)) > 0) {
        // Write to STDOUT (fd = 1)
        if (write(1, buffer, bytesRead) != bytesRead) {
            write(2, "Write error\n", 12); // Write error message to STDERR (fd = 2)
            exit(1);
        }
    }

    if (bytesRead < 0) {
        write(2, "Read error\n", 11); // Error while reading
        exit(1);
    }

    return 0;
}


/*
OUTPUT : 
=============================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/6$ g++ 6.c -o 6
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/6$ ./6
This is Atharva Pingale, MT2025026. I am doing this System Software Assignment. 
This is Atharva Pingale, MT2025026. I am doing this System Software Assignment. 



This is line 2 
This is line 2


This is line 3 
This is line 3 


Cool
Cool


*/