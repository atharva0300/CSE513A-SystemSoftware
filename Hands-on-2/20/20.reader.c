/*
==============================
Name: 20.reader.c
Author: Atharva Ratnadeep Pingale
Description: Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 23rd Sept 2025
==============================
*/


// fifo_reader.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo = "myfifo";
    int fd;
    char buffer[100];

    // Open FIFO for reading
    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    read(fd, buffer, sizeof(buffer));
    printf("Reader: Received message -> %s\n", buffer);

    close(fd);
    return 0;
}


/*
OUTPUT: 
==================================
TERMINAL 1 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/20$ mkfifo myfifo
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/20$ g++ 20.writer.c -o 20.writer
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/20$ ./20.writer
Writer: Sent message -> Hello from writer!


TERMINAL 2 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/20$ g++ 20.reader.c -o 20.reader
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/20$ ./20.reader
Reader: Received message -> Hello from writer!

*/