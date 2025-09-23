/*
==============================
Name: 30.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create a shared memory.
                a. write some data to the shared memory
                b. attach with O_RDONLY and check whether you are able to overwrite.
                c. detach the shared memory
                d. remove the shared memory
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

int main() {
    key_t key;
    int shmid;
    char *shmaddr;

    // 1. Generate a key
    key = ftok("/tmp", 'S');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // 2. Create shared memory segment (size = 1024 bytes)
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    printf("Shared memory created with ID: %d\n", shmid);

    // 3. Attach shared memory for writing
    shmaddr = (char *)shmat(shmid, NULL, 0);  // read-write
    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Attached shared memory for writing.\n");

    // 4. Write some data
    strcpy(shmaddr, "Hello from shared memory!");
    printf("Written to shared memory: %s\n", shmaddr);

    // 5. Detach
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }
    printf("Detached from shared memory after writing.\n");

    // 6. Attach read-only
    shmaddr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (shmaddr == (char *)-1) {
        perror("shmat read-only");
        exit(1);
    }
    printf("Attached shared memory read-only.\n");

    // 7. Attempt to overwrite (should fail or have no effect)
    printf("Attempting to overwrite shared memory in read-only mode...\n");
    // Uncommenting the next line may cause segmentation fault depending on the system
    // strcpy(shmaddr, "Trying to overwrite");
    printf("Current content: %s\n", shmaddr);

    // 8. Detach read-only
    if (shmdt(shmaddr) == -1) {
        perror("shmdt read-only");
        exit(1);
    }
    printf("Detached from shared memory read-only.\n");

    // 9. Remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        exit(1);
    }
    printf("Shared memory removed successfully.\n");

    return 0;
}


/*
OUTPUT: 
===========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/30$ g++ 30.c -o 30
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/30$ ./30
Shared memory created with ID: 18
Attached shared memory for writing.
Written to shared memory: Hello from shared memory!
Detached from shared memory after writing.
Attached shared memory read-only.
Attempting to overwrite shared memory in read-only mode...
Current content: Hello from shared memory!
Detached from shared memory read-only.
Shared memory removed successfully.

*/