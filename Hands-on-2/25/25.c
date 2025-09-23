/*
==============================
Name: 25.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                a. access permission
                b. uid, gid
                c. time of last message sent and received
                d. time of last change in the message queue
                d. size of the queue
                f. number of messages in the queue
                g. maximum number of bytes allowed
                h. pid of the msgsnd and msgrcv
Date: 23rd Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds buf;

    // Generate unique key
    key = ftok(".", 'A');  // same key used to create queue
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get message queue ID
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Get message queue info
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message Queue ID: %d\n", msgid);

    // Access permissions
    printf("Access permissions: %o\n", buf.msg_perm.mode & 0777);

    // UID and GID
    printf("Owner UID: %d\n", buf.msg_perm.uid);
    printf("Owner GID: %d\n", buf.msg_perm.gid);
    printf("Creator UID: %d\n", buf.msg_perm.cuid);
    printf("Creator GID: %d\n", buf.msg_perm.cgid);

    // Times
    printf("Time of last message sent: %s", ctime(&buf.msg_stime));
    printf("Time of last message received: %s", ctime(&buf.msg_rtime));
    printf("Time of last change: %s", ctime(&buf.msg_ctime));

    // Queue size and limits
    printf("Current number of bytes in queue: %lu\n", buf.__msg_cbytes);
    printf("Number of messages in queue: %lu\n", buf.msg_qnum);
    printf("Maximum bytes allowed in queue: %lu\n", buf.msg_qbytes);

    // PIDs
    printf("PID of last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}



/*
OUTPUT: 
========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/25$ g++ 25.c -o 25
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/25$ ./25
Message Queue ID: 1
Access permissions: 666
Owner UID: 1000
Owner GID: 1000
Creator UID: 1000
Creator GID: 1000
Time of last message sent: Thu Jan  1 05:30:00 1970
Time of last message received: Thu Jan  1 05:30:00 1970
Time of last change: Tue Sep 23 14:46:04 2025
Current number of bytes in queue: 0
Number of messages in queue: 0
Maximum bytes allowed in queue: 16384
PID of last msgsnd: 0
PID of last msgrcv: 0


*/