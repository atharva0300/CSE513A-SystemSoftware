/*
==============================
Name: 17.create_ticket_number.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to
open the file, implement write lock, read the ticket number, increment the number and print
the new ticket number then close the file.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "ticket.txt";
    int fd;
    struct stat st;

    // Check if file exists
    if (stat(filename, &st) == 0) {
        // File exists - do not reset ticket number
        printf("%s already exists, skipping initialization.\n", filename);
        return EXIT_SUCCESS;
    }

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    int ticket_number = 1000; // initial ticket number
    if (write(fd, &ticket_number, sizeof(ticket_number)) != sizeof(ticket_number)) {
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);
    printf("Initialized ticket number: %d\n", ticket_number);
    return EXIT_SUCCESS;
}


/*
OUTPUT : 
==============================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/17$ g++ 17.create_ticket_number.c -o 17.create_ticket_number
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/17$ ./17.create_ticket_number
Initialized ticket number: 1000
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/17$ od -t d4 ticket.txt
0000000        1000
0000004
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/17$ g++ 17.reserve_ticket.c -o 17.reserve_ticket
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/17$ ./17.reserve_ticket
Acquiring write lock...
Write lock acquired.
Ticket Number read: 1000
Reserved ticket number: 1001
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/17$ od -t d4 ticket.txt
0000000        1001
0000004
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/17$ ./17.reserve_ticket
Acquiring write lock...
Write lock acquired.
Ticket Number read: 1001
Reserved ticket number: 1002
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/17$ od -t d4 ticket.txt
0000000        1002
0000004



*/