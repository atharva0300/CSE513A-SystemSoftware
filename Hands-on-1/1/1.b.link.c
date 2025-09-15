/*
==============================
Name: 1.b.link.c
Author: Atharva Ratnadeep Pingale
Description: Create a hardlink using link syscall
Date: 6th Sept 2025
==============================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    const char *target = "original.txt";   // existing file
    const char *linkpath = "hardlink-with-link.txt"; // name of hard link

    if (link(target, linkpath) == -1) {
        perror("link failed");
        return 1;
    }

    printf("Hard link created: %s -> %s\n", linkpath, target);
    return 0;
}



// OUTPUT
/*
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
total 324
-rwxrwxr-x 1 atharva0300 atharva0300   592 Sep  6 21:25 1.b.link.c
-rwxrwxr-x 1 atharva0300 atharva0300   685 Sep  6 21:20 1.b.sh
-rw-rw-r-- 1 atharva0300 atharva0300    21 Sep  6 21:24 original.txt

AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ g++ 1.b.link.c -o 1.b.link
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ./1.b.link
Hard link created: hardlink-with-link.txt -> original.txt
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
total 344
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  6 21:26 1.b.link
-rwxrwxr-x 1 atharva0300 atharva0300   901 Sep  6 21:26 1.b.link.c
-rwxrwxr-x 1 atharva0300 atharva0300   685 Sep  6 21:20 1.b.sh
-rw-rw-r-- 2 atharva0300 atharva0300    21 Sep  6 21:24 hardlink-with-link.txt
-rw-rw-r-- 2 atharva0300 atharva0300    21 Sep  6 21:24 original.txt

*/



