/*
==============================
Name: 16.a.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to perform mandatory locking.
            a. Implement write lock
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void writingintoFile(int fd , const char *data){
    if (write(fd, data, strlen(data)) == -1) {
        perror("Error writing to file");
        
        // error caught
        // unlock the file before exiting ( not necessary though as the kernel unlocks the file during fd.close() )
        struct flock unlock = {0};
        unlock.l_type = F_UNLCK;
        unlock.l_whence = SEEK_SET;
        unlock.l_start = 0;
        unlock.l_len = 0;
        fcntl(fd, F_SETLK, &unlock);

        close(fd);
        exit(EXIT_FAILURE);  
    }
}

int main() {
    // open the file in read-write mode
    int fd = open("fileWrite.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // defining the variables of the lock struct
    struct flock lock;
    lock.l_type = F_WRLCK;  // write lock
    lock.l_whence = SEEK_SET;   // set the file pointer to an exact offset from the beginning of the file
    lock.l_start = 0;   // starting offset
    lock.l_len = 0;  // whole file
    // note => when the l_start = 0 and the l_len = 0 at the same time, then this means to lock the entire file ( mandatory locking ).
    // it DOES NOT mean, start from the beginning of the file and lock 0 bytes. 

    printf("Acquiring write lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Write lock acquired. Inside critical section.\n");
    const char *data = "This is Atharva Pingale. I am writing this under the Write Lock.\n";
    writingintoFile(fd , data);
    sleep(5);   // sleeping just to create a observable delay, does not have any affect on the locking.

    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl unlock");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Write lock released.\n");

    close(fd);
    return 0;
}


/*
OUTPUT: 
=========================
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/16$ ls -l
total 8
-rwxrwxr-x 1 atharva0300 atharva0300 2007 Sep  7 11:09 16.a.c
-rwxrwxr-x 1 atharva0300 atharva0300  845 Sep  7 11:01 16.b.c



AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/16$ touch fileWrite.txt
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/16$ g++ 16.a.c -o 16.a
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/16$ ./16.a
Acquiring write lock...
Write lock acquired. Inside critical section.
Write lock released.
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/16$ cat fileWrite.txt
This is Atharva Pingale. I am writing this under the Write Lock.



*/
