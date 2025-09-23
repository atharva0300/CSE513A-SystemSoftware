/*
==============================
Name: 32.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to implement semaphore to protect any critical section.
                a. rewrite the ticket number creation program using semaphore
                b. protect shared memory from concurrent write access
                c. protect multiple pseudo resources ( may be two) using counting semaphore
                d. remove the created semaphore
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Function to perform P (wait) operation
void sem_wait(int semid) {
    struct sembuf op = {0, -1, 0};
    if (semop(semid, &op, 1) == -1) {
        perror("semop wait");
        exit(1);
    }
}

// Function to perform V (signal) operation
void sem_signal(int semid) {
    struct sembuf op = {0, 1, 0};
    if (semop(semid, &op, 1) == -1) {
        perror("semop signal");
        exit(1);
    }
}

int main() {
    key_t key_sem, key_shm;
    int semid, shmid;
    int *shared_ticket;
    int i;

    // =======================
    // a. Create a binary semaphore to protect critical section
    // =======================
    key_sem = ftok("/tmp", 'S');
    if (key_sem == -1) { perror("ftok"); exit(1); }

    semid = semget(key_sem, 1, IPC_CREAT | 0666);
    if (semid == -1) { perror("semget"); exit(1); }

    union semun arg;
    arg.val = 1; // binary semaphore
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }
    printf("Binary semaphore created for critical section.\n");

    // =======================
    // b. Create shared memory to store ticket number
    // =======================
    key_shm = ftok("/tmp", 'M');
    if (key_shm == -1) { perror("ftok shm"); exit(1); }

    shmid = shmget(key_shm, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); exit(1); }

    shared_ticket = (int *)shmat(shmid, NULL, 0);
    if (shared_ticket == (int *)-1) { perror("shmat"); exit(1); }

    *shared_ticket = 0; // initialize ticket number

    // =======================
    // Fork multiple child processes to simulate concurrent access
    // =======================
    for (i = 0; i < 5; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            sem_wait(semid); // enter critical section
            int t = *shared_ticket;
            usleep(100000); // simulate some processing
            t++;
            *shared_ticket = t;
            printf("Child %d incremented ticket number to %d\n", i+1, t);
            sem_signal(semid); // exit critical section
            shmdt(shared_ticket);
            exit(0);
        }
    }

    // Wait for all children
    for (i = 0; i < 5; i++) wait(NULL);

    printf("Final ticket number: %d\n", *shared_ticket);

    // =======================
    // c. Counting semaphore example for 2 pseudo-resources
    // =======================
    int sem_count_id;
    key_t key_count = ftok("/tmp", 'C');
    if (key_count == -1) { perror("ftok count"); exit(1); }

    sem_count_id = semget(key_count, 1, IPC_CREAT | 0666);
    if (sem_count_id == -1) { perror("semget count"); exit(1); }

    arg.val = 2; // two pseudo resources
    if (semctl(sem_count_id, 0, SETVAL, arg) == -1) { perror("semctl count"); exit(1); }

    printf("Counting semaphore created with 2 resources.\n");

    // Example usage: try to acquire both resources sequentially
    printf("Acquiring first pseudo-resource...\n");
    sem_wait(sem_count_id);
    printf("Acquired first resource.\n");

    printf("Acquiring second pseudo-resource...\n");
    sem_wait(sem_count_id);
    printf("Acquired second resource.\n");

    // Release resources
    sem_signal(sem_count_id);
    sem_signal(sem_count_id);
    printf("Released both resources.\n");

    // =======================
    // d. Remove semaphores
    // =======================
    if (semctl(semid, 0, IPC_RMID) == -1) { perror("semctl remove binary"); exit(1); }
    if (semctl(sem_count_id, 0, IPC_RMID) == -1) { perror("semctl remove count"); exit(1); }
    printf("Semaphores removed successfully.\n");

    // Detach and remove shared memory
    shmdt(shared_ticket);
    if (shmctl(shmid, IPC_RMID, NULL) == -1) { perror("shmctl remove"); exit(1); }
    printf("Shared memory removed successfully.\n");

    return 0;
}



/*
OUTPUT: 
========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/32$ g++ 32.c -o 32
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/32$ ./32
Binary semaphore created for critical section.
Child 2 incremented ticket number to 1
Child 3 incremented ticket number to 2
Child 4 incremented ticket number to 3
Child 5 incremented ticket number to 4
Child 1 incremented ticket number to 5
Final ticket number: 5
Counting semaphore created with 2 resources.
Acquiring first pseudo-resource...
Acquired first resource.
Acquiring second pseudo-resource...
Acquired second resource.
Released both resources.
Semaphores removed successfully.
Shared memory removed successfully.


*/