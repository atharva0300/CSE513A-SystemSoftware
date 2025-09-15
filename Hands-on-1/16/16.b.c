/*
==============================
Name: 16.b.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to perform mandatory locking.
            b. Implement read lock
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void readingFromFile(int fd){
    char buffer[1024];
    ssize_t bytes_read;
    lseek(fd, 0, SEEK_SET);  // reset file offset to start

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            
            // unlocking the file ( not necessary though, as the kernel releases the lock on fd.close() )
            struct flock unlock = {0};
            unlock.l_type = F_UNLCK;
            unlock.l_whence = SEEK_SET;
            unlock.l_start = 0;
            unlock.l_len = 0;
            fcntl(fd, F_SETLK, &unlock);

            close(fd);
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (bytes_read == -1) {
        perror("read");
    }
}

int main() {

    // open the file in read-write mode
    int fd = open("fileRead.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // setting the lcok struct variables
    struct flock lock;
    lock.l_type = F_RDLCK;  // read lock 
    lock.l_whence = SEEK_SET;   // set the file pointer to an exact offset from the beginning of the file
    lock.l_start = 0;   // start offset
    lock.l_len = 0;  // whole file

    printf("Acquiring read lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Read lock acquired. Inside critical section.\n");
    readingFromFile(fd);
    sleep(5);   // sleeping just ot create an observable delay. Does not have any effect on the locking. 

    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl unlock");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Read lock released.\n");

    close(fd);
    return 0;
}


/*
OUTPUT : 
==============================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/16$ echo 'This is Atharva Pingale. Reading from fileRead.txt' > fileRead.txt
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/16$ g++ 16.b.c -o 16.b
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/16$ ./16.b
Acquiring read lock...
Read lock acquired. Inside critical section.
This is Atharva Pingale. Reading from fileRead.txt
Read lock released.



*/