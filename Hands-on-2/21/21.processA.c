/*
==============================
Name: 21.processA.c
Author: Atharva Ratnadeep Pingale
Description: Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 23rd Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *fifo_write = "fifo1";  // write to B
    const char *fifo_read = "fifo2";   // read from B
    char buffer[100];

    // Open FIFO for writing (blocks until reader opens fifo1)
    int fd_write = open(fifo_write, O_WRONLY);
    if (fd_write == -1) { perror("open write"); exit(1); }

    // Open FIFO for reading (blocks until writer opens fifo2)
    int fd_read = open(fifo_read, O_RDONLY);
    if (fd_read == -1) { perror("open read"); exit(1); }

    // Send message to B
    const char *msg = "Hello from A!";
    write(fd_write, msg, strlen(msg) + 1);
    printf("A sent: %s\n", msg);

    // Read message from B
    read(fd_read, buffer, sizeof(buffer));
    printf("A received: %s\n", buffer);

    close(fd_write);
    close(fd_read);

    return 0;
}


/*
OUTPUT: 
===========================
TERMINAL 1 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/21$ mkfifo fifo1 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/21$ mkfifo fifo2
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/21$ g++ 21.processA.c -o 21.processA
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/21$ ./21.processA
A sent: Hello from A!
A received: Hello from B!


TERMINAL 2 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/21$ g++ 21.processB.c -o 21.processB
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/21$ ./21.processB
B received: Hello from A!
B sent: Hello from B!


*/