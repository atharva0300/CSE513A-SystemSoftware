/*
==============================
Name: 31.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create a semaphore and initialize value to the semaphore.
                a. create a binary semaphore
                b. create a counting semaphore
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

int main() {
    key_t key_bin, key_count;
    int semid_bin, semid_count;
    union semun {
        int val;               // value for SETVAL
        struct semid_ds *buf;  // buffer for IPC_STAT, IPC_SET
        unsigned short *array; // array for SETALL
    } arg;

    // ================================
    // a. Binary semaphore (0 or 1)
    // ================================
    key_bin = ftok("/tmp", 'B');
    if (key_bin == -1) { perror("ftok binary"); exit(1); }

    semid_bin = semget(key_bin, 1, IPC_CREAT | 0666); // single semaphore
    if (semid_bin == -1) { perror("semget binary"); exit(1); }

    arg.val = 1; // initialize to 1 (binary semaphore)
    if (semctl(semid_bin, 0, SETVAL, arg) == -1) {
        perror("semctl binary SETVAL");
        exit(1);
    }

    printf("Binary semaphore created with ID: %d, initial value: %d\n", semid_bin, arg.val);

    // ================================
    // b. Counting semaphore (n > 1)
    // ================================
    key_count = ftok("/tmp", 'C');
    if (key_count == -1) { perror("ftok counting"); exit(1); }

    semid_count = semget(key_count, 1, IPC_CREAT | 0666); // single counting semaphore
    if (semid_count == -1) { perror("semget counting"); exit(1); }

    arg.val = 5; // initialize to 5 (counting semaphore)
    if (semctl(semid_count, 0, SETVAL, arg) == -1) {
        perror("semctl counting SETVAL");
        exit(1);
    }

    printf("Counting semaphore created with ID: %d, initial value: %d\n", semid_count, arg.val);

    return 0;
}


/*
OUTPUT: 
============================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/31$ g++ 31.c -o 31
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/31$ ./31
Binary semaphore created with ID: 0, initial value: 1
Counting semaphore created with ID: 1, initial value: 5


*/