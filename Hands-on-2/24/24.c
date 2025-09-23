/*
==============================
Name: 24.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create a message queue and print the key and message queue id.
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    // Generate unique key
    key = ftok(".", 'A');  // '.' = current directory, 'A' = project identifier
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create message queue (IPC_CREAT | 0666 permissions)
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message queue created successfully!\n");
    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}


/*
OUTPUT: 
============================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/24$ g++ 24.c -o 24 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/24$ ./24
Message queue created successfully!
Key: 1090740815
Message Queue ID: 0

*/