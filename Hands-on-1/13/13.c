/*
==============================
Name: 13.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
verify whether the data is available within 10 seconds or not (check in $man 2 select).
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    fd_set readfds;             // File descriptor set for select
    struct timeval timeout;     // Timeout struct

    FD_ZERO(&readfds);          // Clear the set
    FD_SET(STDIN_FILENO, &readfds); // Add STDIN (fd=0) to the set

    timeout.tv_sec = 10;        // Wait for 10 seconds
    timeout.tv_usec = 0;        // No microseconds

    printf("Waiting for input on STDIN for 10 seconds...\n");
    printf("Type something and press Enter, or wait for timeout.\n");

    // Select syscall arguments => select(nfds, readfds, writefds, exceptfds, timeout)
    int retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select");
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        printf("No data entered within 10 seconds. Timeout!\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            char buffer[1024];
            ssize_t bytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
            if (bytes > 0) {
                buffer[bytes] = '\0';
                printf("Data entered: %s\n", buffer);
            }
        }
    }

    return 0;
}


/*
OUTPUT : 
==================================
WHEN INPUT ON STDIN : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/13$ g++ 13.c -o 13 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/13$ ./13
Waiting for input on STDIN for 10 seconds...
Type something and press Enter, or wait for timeout.
This is ATharva Pingale, MT2025026
Data entered: This is ATharva Pingale, MT2025026



WHEN TIMEOUT : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/13$ ./13
Waiting for input on STDIN for 10 seconds...
Type something and press Enter, or wait for timeout.
No data entered within 10 seconds. Timeout!



*/