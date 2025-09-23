/*
==============================
Name: 28.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to change the exiting message queue permission. (use msqid_ds structure)
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
    struct msqid_ds buf;

    // Generate key (same as existing queue)
    key = ftok("/tmp", 'R');  // use same path & project id as queue
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the existing message queue
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Current message queue ID: %d\n", msgid);

    // Get current attributes
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl IPC_STAT");
        exit(1);
    }

    printf("Current permissions: %o\n", buf.msg_perm.mode & 0777);

    // Change permission: e.g., make it read/write for user only (0600)
    buf.msg_perm.mode = 0600;

    if (msgctl(msgid, IPC_SET, &buf) == -1) {
        perror("msgctl IPC_SET");
        exit(1);
    }

    printf("Permissions changed successfully!\n");

    // Verify
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl IPC_STAT");
        exit(1);
    }
    printf("Updated permissions: %o\n", buf.msg_perm.mode & 0777);

    return 0;
}


/*
OUTPUT: 
=========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/28$ g++ 28.c -o 28
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/28$ ./28
Current message queue ID: 4
Current permissions: 666
Permissions changed successfully!
Updated permissions: 600

*/