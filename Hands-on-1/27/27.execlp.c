/*
==============================
Name: 27.execlp.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to execute ls -Rl by the following system calls
            a. execl   
            b. execlp  [X]
            c. execle
            d. execv
            e. execvp
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Executing ls -Rl using execlp\n");
    execlp("ls", "ls", "-Rl", (char *)NULL);

    perror("execlp failed");
    return EXIT_FAILURE;
}


/*
OUTPUT : 
=======================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ g++ 27.execlp.c -o 27.execlp
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ ./27.execlp
Executing ls -Rl using execlp
.:
total 40
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  7 22:27 27.execl
-rw-rw-r-- 1 atharva0300 atharva0300   990 Sep  7 22:27 27.execl.c
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  7 22:28 27.execlp
-rw-rw-r-- 1 atharva0300 atharva0300   556 Sep  7 22:28 27.execlp.c


*/