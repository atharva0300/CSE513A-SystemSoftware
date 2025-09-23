/*
==============================
Name: 27.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to receive messages from the message queue.
                a. with 0 as a flag
                b. with IPC_NOWAIT as a flag
Date: 23rd Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

struct my_msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct my_msgbuf message;
    ssize_t n;

    // Shared key
    key = ftok("/tmp", 'R');
    if (key == -1) { perror("ftok"); exit(1); }

    // Create or get message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) { perror("msgget"); exit(1); }

    printf("Message queue ID: %d\n", msgid);

    // Blocking receive
    printf("=== Blocking receive (flag = 0) ===\n");
    n = msgrcv(msgid, &message, sizeof(message.mtext), 0, 0);
    if (n == -1) {
        perror("msgrcv");
    } else {
        message.mtext[n] = '\0';
        printf("Received (blocking): %s\n", message.mtext);
    }

    // Non-blocking receive
    printf("\n=== Non-blocking receive (flag = IPC_NOWAIT) ===\n");
    n = msgrcv(msgid, &message, sizeof(message.mtext), 0, IPC_NOWAIT);
    if (n == -1) {
        if (errno == ENOMSG) {
            printf("No message available (non-blocking).\n");
        } else {
            perror("msgrcv");
        }
    } else {
        message.mtext[n] = '\0';
        printf("Received (non-blocking): %s\n", message.mtext);
    }

    return 0;
}


/*
OUTPUT: 
===============================
TERMINAL 1 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/27$ g++ 27.receiver.c -o 27.receiver
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/27$ ./27.receiver
Message queue ID: 4
=== Blocking receive (flag = 0) ===
Received (blocking): Atharva is sending a message!

=== Non-blocking receive (flag = IPC_NOWAIT) ===
No message available (non-blocking).



TERMINAL 2 => 
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/27$ g++ 27.sender.c -o 27.sender
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/27$ ./27.sender
Message sent successfully!


*/