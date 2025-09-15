/*
==============================
Name: 18.write_lock.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to perform Record locking.
            a. Implement write lock [X]
            b. Implement read lock
            Create three records in a file. Whenever you access a particular record, first lock it then modify/access
            to avoid race condition.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define RECORD_SIZE sizeof(int)

void lock_record(int fd, int rec_no, short lock_type) {
    struct flock lock = {0};
    lock.l_type = lock_type;
    lock.l_whence = SEEK_SET;
    lock.l_start = rec_no * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl lock");
        close(fd);
        exit(EXIT_FAILURE);
    }
}

void unlock_record(int fd, int rec_no) {
    struct flock lock = {0};
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = rec_no * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl unlock");
    }
}

int main() {
    int rec_no;
    int incr;
    printf("Enter the Record Number: ");
    scanf("%d" , &rec_no);
    printf("Enter the increment: ");
    scanf("%d" , &incr);

    int fd = open("records.txt", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    int num_records = st.st_size / RECORD_SIZE;
    if (rec_no < 0 || rec_no >= num_records) {
        fprintf(stderr, "Record number must be between 0 and %d\n", num_records - 1);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Lock record for writing
    lock_record(fd, rec_no, F_WRLCK);

    if (lseek(fd, rec_no * RECORD_SIZE, SEEK_SET) == -1) {
        perror("lseek");
        unlock_record(fd, rec_no);
        close(fd);
        exit(EXIT_FAILURE);
    }

    int val;
    if (read(fd, &val, RECORD_SIZE) != RECORD_SIZE) {
        perror("read");
        unlock_record(fd, rec_no);
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Current value at record %d: %d\n", rec_no, val);

    val += incr;  // modify

    if (lseek(fd, rec_no * RECORD_SIZE, SEEK_SET) == -1) {
        perror("lseek for write");
        unlock_record(fd, rec_no);
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (write(fd, &val, RECORD_SIZE) != RECORD_SIZE) {
        perror("write");
        unlock_record(fd, rec_no);
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Updated value at record %d: %d\n", rec_no, val);

    unlock_record(fd, rec_no);
    close(fd);
    return 0;
}


/*
OUTPUT: 
==================================
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/18$ cat records.txt
Atharva
Pingale
IIITB
System Software


AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/18$ g++ 18.write_lock.c -o 18.write_lock
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/18$ ./18.write_lock
Enter the Record Number: 2
Enter the increment: 3
Current value at record 2: 1735289168
Updated value at record 2: 1735289171
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/18$ cat records.txt
Atharva
Singale
IIITB
System Software
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/18$ ./18.write_lock
Enter the Record Number: 4
Enter the increment: 16
Current value at record 4: 1414089033
Updated value at record 4: 1414089049
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/18$ cat records.txt
Atharva
Singale
YIITB
System Software



*/