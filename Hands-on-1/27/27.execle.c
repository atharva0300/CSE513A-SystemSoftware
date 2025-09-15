/*
==============================
Name: 27.execle.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to execute ls -Rl by the following system calls
            a. execl   
            b. execlp  
            c. execle   [X]
            d. execv
            e. execvp
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main() {
    printf("Executing ls -Rl using execle\n");
    execle("/bin/ls", "ls", "-Rl", (char *)NULL, environ);

    perror("execle failed");
    return EXIT_FAILURE;
}


/*
OUTPUT : 
==========================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ g++ 27.execle.c -o 27.execle
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ ./27.execle
Executing ls -Rl using execle
.:
total 60
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  7 22:27 27.execl
-rw-rw-r-- 1 atharva0300 atharva0300   990 Sep  7 22:27 27.execl.c
-rwxrwxr-x 1 atharva0300 atharva0300 16120 Sep  7 22:29 27.execle
-rw-rw-r-- 1 atharva0300 atharva0300   599 Sep  7 22:29 27.execle.c
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  7 22:28 27.execlp
-rw-rw-r-- 1 atharva0300 atharva0300  1122 Sep  7 22:28 27.execlp.c

*/