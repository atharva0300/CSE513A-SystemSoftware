/*
==============================
Name: 22.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 23rd Sept 2025
==============================
*/


/*
==============================
Name: 22_fifo_select.c
Author: Atharva Ratnadeep Pingale
Description: Wait for data in FIFO using select() for 10 seconds
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>


int main() {
    const char *fifo = "fifo_select";
    char buffer[100];

    // Create FIFO if it does not exist
    mkfifo(fifo, 0666);

    // Open FIFO for reading
    int fd = open(fifo, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("Waiting for data in FIFO '%s' for 10 seconds...\n", fifo);

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 10;     // 10 seconds
    timeout.tv_usec = 0;

    int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select");
        close(fd);
        exit(1);
    } else if (ret == 0) {
        printf("Timeout! No data received in 10 seconds.\n");
    } else {
        if (FD_ISSET(fd, &readfds)) {
            int n = read(fd, buffer, sizeof(buffer));
            if (n > 0) {
                buffer[n] = '\0'; // Ensure null-terminated
                printf("Received data: %s\n", buffer);
            } else {
                printf("FIFO closed or no data read.\n");
            }
        }
    }

    close(fd);
    return 0;
}

/*
OUTPUT: 
===========================
TERMINAL 1 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/22$ g++ 22.c -o 22
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/22$ ./22
Waiting for data in FIFO 'fifo_select' for 10 seconds...
Received data: writing something here


TERMINAL 2 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/22$ echo "writing something here" > fifo_select


*/

