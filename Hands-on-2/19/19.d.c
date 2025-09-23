/*
==============================
Name: 19.d.c
Author: Atharva Ratnadeep Pingale
Description: Create a FIFO file by
                a. mknod command           
                b. mkfifo command       
                c. use strace command to find out, which command (mknod or mkfifo) is better.
                c. mknod system call
                d. mkfifo library function      [X]
Date: 23rd Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifo = "mkfifo_pipe_system_call";

    if (mkfifo(fifo, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO '%s' created using mkfifo() system call\n", fifo);
    return 0;
}



/*
OUTPUT: 
==========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/19$ ls -l 
total 56
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep 23 13:33 19.a
-rw-rw-r-- 1 atharva0300 atharva0300   706 Sep 23 13:43 19.a.sh
-rw-rw-r-- 1 atharva0300 atharva0300   661 Sep 23 13:44 19.b.sh
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep 23 13:51 19.c
-rw-rw-r-- 1 atharva0300 atharva0300  2686 Sep 23 13:51 19.c.c
-rw-rw-r-- 1 atharva0300 atharva0300  6313 Sep 23 13:39 19.c.sh
-rw-rw-r-- 1 atharva0300 atharva0300  1899 Sep 23 13:49 19.d.c
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep 23 13:51 mknod_pipe_system_call
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep 23 13:43 myfifo1
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep 23 13:44 myfifo2
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep 23 13:49 myfifo_mkfifo
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/19$ g++ 19.d.c -o 19.d
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/19$ ./19.d
FIFO 'mkfifo_pipe_system_call' created using mkfifo() system call
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/19$ ls -l
total 72
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep 23 13:33 19.a
-rw-rw-r-- 1 atharva0300 atharva0300   706 Sep 23 13:43 19.a.sh
-rw-rw-r-- 1 atharva0300 atharva0300   661 Sep 23 13:44 19.b.sh
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep 23 13:51 19.c
-rw-rw-r-- 1 atharva0300 atharva0300  2686 Sep 23 13:51 19.c.c
-rw-rw-r-- 1 atharva0300 atharva0300  6313 Sep 23 13:39 19.c.sh
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep 23 13:52 19.d
-rw-rw-r-- 1 atharva0300 atharva0300  1899 Sep 23 13:49 19.d.c
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep 23 13:52 mkfifo_pipe_system_call
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep 23 13:51 mknod_pipe_system_call
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep 23 13:43 myfifo1
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep 23 13:44 myfifo2
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep 23 13:49 myfifo_mkfifo


*/
