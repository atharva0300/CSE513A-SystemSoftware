/*
==============================
Name: 26.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to send messages to the message queue. Check $ipcs -q
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main() {
    key_t key;
    int msgid;

    // Generate key
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get or create message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Use struct msgbuf from sys/msg.h
    struct msgbuf {
        long mtype;
        char mtext[100];
    } message;

    message.mtype = 1;
    strcpy(message.mtext, "Hello, this is a message to the queue!");

    // Send message
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent to queue successfully!\n");

    // Optional: show message queue info
    system("ipcs -q");

    return 0;
}


/*
OUTPUT: 
========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/26$ g++ 26.c -o 26
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/26$ ./26
Message sent to queue successfully!

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x4103624f 0          atharva030 666        0            0           
0x41036353 1          atharva030 666        0            0           
0x41036394 2          atharva030 666        100          1 

*/