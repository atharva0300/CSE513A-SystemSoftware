/*
==============================
Name: 27.execl.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to execute ls -Rl by the following system calls
            a. execl   [X]
            b. execlp
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
    printf("Executing ls -Rl using execl\n");
    execl("/bin/ls", "ls", "-Rl", (char *)NULL);

    perror("execl failed");
    return EXIT_FAILURE;
}


/*
OUTPUT : 
==========================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ g++ 27.execl.c -o 27.execl
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ ./27.execl
Executing ls -Rl using execl
.:
total 20
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  7 22:27 27.execl
-rw-rw-r-- 1 atharva0300 atharva0300   558 Sep  7 22:26 27.execl.c


*/


