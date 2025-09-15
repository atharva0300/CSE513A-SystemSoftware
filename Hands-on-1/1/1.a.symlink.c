/*
==============================
Name: 1.a.syscall.c
Author: Atharva Ratnadeep Pingale
Description: Create a softlink using Symlink syscall
Date: 6th Sept 2025
==============================
*/

#include <stdio.h>
#include <unistd.h>

int main() {

    const char *target = "original.txt";    // file to link to
    const char *linkpath = "softlink-with-symlink.txt";  // name of soft link

    if (symlink(target, linkpath) == -1) {
        perror("symlink failed");
        return 1;
    }

    printf("Soft link created: %s -> %s\n", linkpath, target);
    return 0;
}


// OUTPUT 
/* 
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
total 320
-rwxrwxr-x 1 atharva0300 atharva0300  1110 Sep  6 21:11 1.a.sh
-rwxrwxr-x 1 atharva0300 atharva0300  1464 Sep  6 21:06 1.a.symlink.c
-rwxrwxr-x 1 atharva0300 atharva0300    21 Sep  6 21:08 original.txt

AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ g++ 1.a.symlink.c -o 1.a.symlink
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ./1.a.symlink
Soft link created: softlink-with-symlink.txt -> original.txt

atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
total 320
-rwxrwxr-x 1 atharva0300 atharva0300  1110 Sep  6 21:11 1.a.sh
-rwxrwxr-x 1 atharva0300 atharva0300 16056 Sep  6 21:12 1.a.symlink
-rwxrwxr-x 1 atharva0300 atharva0300  1583 Sep  6 21:12 1.a.symlink.c
-rwxrwxr-x 1 atharva0300 atharva0300    21 Sep  6 21:08 original.txt
lrwxrwxrwx 1 atharva0300 atharva0300    12 Sep  6 21:12 softlink-with-symlink.txt -> original.txt

*/