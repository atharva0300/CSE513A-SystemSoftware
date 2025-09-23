/*
==============================
Name: 29.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to remove the message queue.
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {
    key_t key;
    int msgid;

    // Generate key (use same path & project id as the queue)
    key = ftok("/tmp", 'R');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the existing message queue ID
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message queue ID: %d\n", msgid);

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        exit(1);
    }

    printf("Message queue removed successfully!\n");

    return 0;
}


/*
OUTPUT: 
=======================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/29$ g++ 29.c -o 29
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/29$ ./29
Message queue ID: 4
Message queue removed successfully!

*/