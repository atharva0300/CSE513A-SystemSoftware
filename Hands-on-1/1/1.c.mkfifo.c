/*
==============================
Name: 1.c.mkfifo.c
Author: Atharva Ratnadeep Pingale 
Description: Create a FIFO using mkfifo syscall
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifo_path = "myfifo";

    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo failed");
        return 1;
    }

    printf("FIFO created: %s\n", fifo_path);
    return 0;
}


/*
OUTPUT : 
=============================
BEFORE :
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
total 348
-rwxrwxr-x 1 atharva0300 atharva0300   276 Aug 14 01:19 1.c.mkfifo.c


AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ g++ 1.c.mkfifo.c -o 1.c.mkfifo
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ./1.c.mkfifo
FIFO created: myfifo
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
total 364
-rwxrwxr-x 1 atharva0300 atharva0300 16056 Sep  6 21:37 1.c.mkfifo
-rwxrwxr-x 1 atharva0300 atharva0300   587 Sep  6 21:37 1.c.mkfifo.c
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep  6 21:37 myfifo
-rw-rw-r-- 3 atharva0300 atharva0300    21 Sep  6 21:24 original.txt

*/