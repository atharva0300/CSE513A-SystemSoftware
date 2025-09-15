/*
==============================
Name: 18.read_lock.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to perform Record locking.
            a. Implement write lock 
            b. Implement read lock  [X]
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
    printf("Enter Record Number: ");
    scanf("%d" , &rec_no);

    const char *fileName = "records.txt";

    int fd = open(fileName, O_RDONLY);
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

    // Lock record for reading
    lock_record(fd, rec_no, F_RDLCK);

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

    printf("Value at record %d: %d\n", rec_no, val);    
    // it reads the file content in binary format which is expected to be stored as raw bytes and not text


    unlock_record(fd, rec_no);
    close(fd);
    return 0;
}


/*
OUTPUT: 
============================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/18$ g++ 18.read_lock.c -o 18.read_lock
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/18$ ./18.read_lock
Enter Record Number: 5
Value at record 5: 2035485254
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/18$ ./18.read_lock
Enter Record Number: 3
Value at record 3: 174419041


*/