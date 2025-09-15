/*
==============================
Name: 17.reserve_ticket.c
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

int main() {
    // open the file in read-write mode
    int fd = open("ticket.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // set the lock struct variables
    struct flock lock;
    lock.l_type = F_WRLCK;    // write lock
    lock.l_whence = SEEK_SET;   // set the file pointer to an exact offset from the beginning of the file
    lock.l_start = 0;           // start offset
    lock.l_len = 0;           // lock whole file

    printf("Acquiring write lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl lock");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Write lock acquired.\n");
    // Read ticket number
    int ticket_number;
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        // unlock before exit
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        return EXIT_FAILURE;
    }
    if (read(fd, &ticket_number, sizeof(ticket_number)) != sizeof(ticket_number)) {
        perror("read");
        // unlock before exit
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Ticket Number read: %d\n" , ticket_number);
    ticket_number++;   // increment ticket number
    printf("Reserved ticket number: %d\n", ticket_number);

    // Write updated ticket number back to file
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        return EXIT_FAILURE;
    }
    if (write(fd, &ticket_number, sizeof(ticket_number)) != sizeof(ticket_number)) {
        perror("write");
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        return EXIT_FAILURE;
    }

    // Unlock and close file
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl unlock");
    }

    close(fd);
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
